use actix_web::{Responder, web};

pub fn config(cfg: &mut web::ServiceConfig) {
    cfg.service(
        web::resource("/").route(web::get().to(auth_path))
        // .service(
        //     // web::resource("/register").route(web::post().to(register))
        // )
        // .service(web::resource("/register").route(web::post().to(register)))
        // .service(web::resource("/login").route(web::post().to(login)))
        // .service(web::resource("/logout").route(web::post().to(logout)))
        // .service(web::resource("/email").route(web::post().to(request_email)))
        // .service(web::resource("/password").route(web::post().to(reset_password)))
        // .app_data(web::PayloadConfig::new(500_000)), // 500 KB max payload,
    );
    // cfg.service(
    //     web::resource("/")
    //         .app_data(web::PayloadConfig::new(500_000)) // 500 KB max payload
    //         .route(web::get().to()),
    // );
}

async fn auth_path(name: web::Path<String>) -> impl Responder {
    format!("Hello {}!", name)
}

async fn register(name: web::Path<String>) -> impl Responder {
    format!("Hello {}!", name)
}

async fn login(name: web::Path<String>) -> impl Responder {
    format!("Hello {}!", name)
}

async fn logout(name: web::Path<String>) -> impl Responder {
    format!("Hello {}!", name)
}

async fn request_email(name: web::Path<String>) -> impl Responder {
    format!("Hello {}!", name)
}

async fn reset_password(name: web::Path<String>) -> impl Responder {
    format!("Hello {}!", name)
}
