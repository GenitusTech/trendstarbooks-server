use actix_cors::{Cors};
use actix_web::{cookie::Key, http::header, middleware::{Logger}, web, App, HttpServer};
use dotenv::{dotenv};
// use std::env;
use openssl::ssl::{SslAcceptor, SslFiletype, SslMethod};

mod config;
mod routes;
mod middleware;

use config::Config;
use routes::{api_routes};
// use middleware::security::SecurityHeaders;

#[actix_web::main]
async fn main() -> std::io::Result<()>
{
  dotenv().ok();
  env_logger::init();

  let config = Config::from_env().expect("Failed to load configuration");

  let mut ssl_builder = SslAcceptor::mozilla_intermediate(SslMethod::tls())
    .expect("Failed to create SSL acceptor");
  ssl_builder
    .set_private_key_file(config.ssl_key_path, SslFiletype::PEM)
    .expect("Failed to set private key");
  ssl_builder
    .set_certificate_chain_file(config.ssl_cert_path)
    .expect("Failed to set certificate chain");

  log::info!("Starting server on https://{}:{}", config.host, config.port);

  HttpServer::new(move || {

    // Configure CORS with focus on security
    let cors = Cors::default()
      .allowed_origin(&config.allowed_origin)
      .allowed_methods(vec!["GET", "POST", "PUT", "DELETE"])
      .allowed_headers(vec![
        header::AUTHORIZATION,
        header::ACCEPT,
        header::CONTENT_TYPE,
        header::ORIGIN,
        //
      ])
      .supports_credentials()
      .max_age(3600);

    App::new()
      .wrap(Logger::default())
      .wrap(cors)
      // .wrap(SecurityHeaders)
      .wrap(actix_identity::IdentityMiddleware::default())
      .wrap(
        actix_session::SessionMiddleware::builder(
          actix_session::storage::CookieSessionStore::default(),
          Key::derive_from(config.secret_key.as_bytes())
        )
        .cookie_secure(true)
        .cookie_http_only(true)
        .cookie_same_site(actix_web::cookie::SameSite::Strict)
        .build()
      )
      // .app_data(web::Data::new(config.clone()))
      .service(
        web::scope("/api")
          // .wrap(middleware::security::CsrfProtection)
          .service(api_routes::scope())
      )
  })
  .bind(format!("{}:{}", config.host, config.port))?
  .workers(4)
  .run()
  .await
}
