use serde::{Deserialize};
use std::{env};
use garde::{Validate};
use num::{Num};

#[derive(Clone, Debug, Deserialize, Validate)]
pub struct Config {
  #[garde(ipv4,length(min = 1))]
  pub host: String,
  #[garde(range(min = 1, max = 65535))]
  pub port: u16,
  #[garde(range(min = 1, max = 4))]
  pub worker_threads: Num,
  #[garde(ascii,length(min = 32))]
  pub secret_key: String,
  #[garde(url)]
  pub allowed_origin: String,
  #[garde(length(min = 1))]
  pub database_url: String,
  #[garde(length(min = 1))]
  pub ssl_cert_path: String,
  #[garde(length(min = 1))]
  pub ssl_key_path: String,
}

impl Config {
  pub fn from_env() -> Result<Self, env::VarError> {
    Ok(Config {
      host: env::var("HOST")
        .unwrap_or_else(|_| "127.0.0.1".to_string()),
      port: env::var("PORT")
        .unwrap_or_else(|_| "8443".to_string())
        .parse()
        .unwrap_or(8443),
      worker_threads: env::var("WORKER_THREADS")
        .unwrap_or_else(|_| "4".to_string())
        .parse()
        .unwrap_or("4"),
      secret_key: env::var("SECRET_KEY")
        .expect("SECRET_KEY must be set"),
      allowed_origin: env::var("ALLOWED_ORIGIN")
        .expect("ALLOWED_ORIGIN must be set"),
      database_url: env::var("DATABASE_URL")
        .expect("DATABASE_URL must be set"),
      ssl_cert_path: env::var("SSL_CERT_PATH")
        .expect("CERT_PATH must be set"),
      ssl_key_path: env::var("SSL_KEY_PATH")
        .expect("KEY_PATH must be set")
    })
  }
}
