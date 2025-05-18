use actix_web::web;

pub fn scope() -> actix_web::Scope
{
  web::scope("/api")
}
