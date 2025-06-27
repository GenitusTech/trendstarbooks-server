use actix_web::web;

pub fn config(cfg: &mut web::ServiceConfig) {
    cfg.service(
        web::resource("/")
            .app_data(web::PayloadConfig::new(3_000_000)) // 3 MB max payload
            .route(web::get().to()),
    );
}
