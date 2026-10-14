#pragma once
#include <queue>
#include <utility>
#include <cstddef>

class RateLimiter
{
public:
    RateLimiter(int max_requests, int window_size_ms)
        : max_requests_(max_requests), window_size_ms_(window_size_ms) {}

    bool allow_request(long long timestamp_ms)
    {
        while (!log_.empty() && timestamp_ms - log_.front() >= window_size_ms_)
        {
            log_.pop();
        }
        if (std::cmp_less(log_.size(), max_requests_))
        {
            log_.push(timestamp_ms);
            return true;
        }
        else
            return false;
    }

    std::size_t logged_count() const
    {
        return log_.size();
    }

private:
    int max_requests_;
    int window_size_ms_;
    std::queue<long long> log_;
};