#include <queue>

class RateLimiter {
public:
    RateLimiter(int max_requests, int window_size_ms)
        : max_requests_(max_requests), window_size_ms_(window_size_ms) {}

    bool allow_request(long long timestamp_ms) {
        // 1. remove old timestamps
        // 2. check the count
        // 3. if allowed, log it and return true
        // 4. otherwise return false
    }

private:
    int max_requests_;
    int window_size_ms_;
    std::queue<long long> log_;
};