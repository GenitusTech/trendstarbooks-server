use std::collections::{HashMap, HashSet};
use std::net::IpAddr;
use std::sync::{Arc, Mutex};
use std::time::{Duration, Instant};

#[derive(Clone)]
pub struct AppState {
    pub rate_limiter: Arc<Mutex<RateLimiter>>,
    pub ip_blacklist: Arc<Mutex<IPBlacklist>>,
}

pub struct RateLimiter {
    requests: HashMap<IpAddr, (Instant, u32)>,
    limit: u32,
    window: Duration,
}

impl RateLimiter {
    // INIT
    pub fn new(limit: u32, window: Duration) -> Self {
        RateLimiter {
            requests: HashMap::new(),
            limit,
            window,
        }
    }

    // CHECK FUNCTION
    pub fn check(&mut self, ip: IpAddr) -> bool {
        let now = Instant::now();

        if let Some((last_time, count)) = self.requests.get_mut(&ip) {
            if now.duration_since(*last_time) < self.window {
                *count += 1;
                *count <= self.limit
            } else {
                *last_time = now;
                *count = 1;
                true
            }
        } else {
            self.requests.insert(ip, (now, 1));
            true
        }
    }
}

pub struct IPBlacklist {
    ips: HashSet<IpAddr>,
}

impl IPBlacklist {
    // INIT
    pub fn new() -> Self {
        IPBlacklist {
            ips: HashSet::new(),
        }
    }

    // IS BLOCKED FUNCTION
    pub fn is_blocked(&self, ip: IpAddr) -> bool {
        self.ips.contains(&ip)
    }

    // BLOCK IP FUNCTION
    pub fn block_ip(&mut self, ip: IpAddr) {
        self.ips.insert(ip);
    }
}
