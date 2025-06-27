use actix_web::{dev::ServiceRequest, middleware::Next, web, HttpResponse};

use crate::config::protection::AppState;

async fn rate_limiter_middleware(
    req: ServiceRequest,
    next: Next,
    data: web::Data<AppState>,
) -> Result<HttpResponse, actix_web::Error> {
    // Get client IP (consider using X-Forwarded-For if behind proxy)
    let ip = req.connection_info().peer_addr().unwrap().parse().unwrap();

    // Check blacklist first
    {
        let blacklist = data.ip_blacklist.lock().unwrap();
        if blacklist.is_blocked(ip) {
            return Ok(HttpResponse::TooManyRequests().finish());
        }
    }

    // Check rate limit
    let is_allowed = {
        let mut limiter = data.rate_limiter.lock().unwrap();
        limiter.check(ip)
    };

    if !is_allowed {
        // Block IP if rate limit exceeded
        let mut blacklist = data.ip_blacklist.lock().unwrap();
        blacklist.block_ip(ip);
        return Ok(HttpResponse::TooManyRequests().finish());
    }

    // Continue processing if all checks pass
    next.call(req).await
}
