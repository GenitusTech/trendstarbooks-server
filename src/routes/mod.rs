use actix_web::web;

mod api;
mod auth;

pub fn config(cfg: &mut web::ServiceConfig) {
    cfg
    .service(
        web::scope("/api").configure(api::config)
    )
    .service(
        web::scope("/auth").configure(auth::config)
    );
}
