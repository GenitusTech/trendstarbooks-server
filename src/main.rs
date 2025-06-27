use actix_cors::Cors;
// use actix_csrf::CsrfMiddleware;
use actix_web::{
    App, HttpServer,
    http::{
        Method,
        header::{ACCEPT, AUTHORIZATION, CONTENT_TYPE},
    },
    middleware::{DefaultHeaders, Logger},
};
use openssl::ssl::{SslAcceptor, SslFiletype, SslMethod};
// use rand::rngs::StdRng;

mod routes;

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    // #TODO: Implement IP blacklisting
    // #TODO: Implement request rate limiting
    // #TODO: Implement request size limiting
    // let app_state = web::Data::new(AppState {
    //     rate_limiter: Arc::new(Mutex::new(RateLimiter::new(100, Duration::from_secs(1)))),
    //     ip_blacklist: Arc::new(Mutex::new(IPBlacklist::new())),
    // });

    // SSL Builder -> initialization
    let mut ssl_builder = SslAcceptor::mozilla_intermediate(SslMethod::tls())
        .expect("Could not initiate 'ssl_builder'");
    ssl_builder
        .set_private_key_file("./ssl/key.pem", SslFiletype::PEM)
        .expect("Could not load 'private key'");
    ssl_builder
        .set_certificate_chain_file("./ssl/cert.pem")
        .expect("Could not load 'certificate chain file'");

    // SERVER
    HttpServer::new(move || {
        // DEFAULT SECURITY HEADERS
        let default_headers = DefaultHeaders::new()
            .add(("X-Content-Type-Options", "nosniff"))
            .add(("X-Frame-Options", "DENY"))
            .add(("X-XSS-Protection", "1; mode=block"));
        // CORS [Cross-Origin Resource Sharing]
        let cors = Cors::default()
            .allowed_methods(vec!["GET", "POST", "PUT", "DELETE"])
            .allowed_headers(vec![AUTHORIZATION, ACCEPT, CONTENT_TYPE])
            .supports_credentials()
            .max_age(3600);

        // let csrf = CsrfMiddleware::<StdRng>::new().set_cookie(Method::GET, "/auth/login");

        // SERVICES: middlewares + routes + controllers
        App::new()
            // .app_data(app_state.clone())
            .wrap(Logger::default())
            // .wrap(csrf)
            .wrap(default_headers)
            .wrap(cors)
            .configure(routes::config)

        // .service(greet)
    })
    .workers(4)
    .backlog(1024)
    .max_connection_rate(512)
    .bind_openssl(format!("{}:{}", "127.0.0.1", 8080), ssl_builder)?
    .run()
    .await
}
