#include <iostream>
#include "rate_limiter.hpp"
#include <cassert>

void test_trace(){
    RateLimiter trace_test(2, 1000);
    assert (    trace_test.allow_request(0) );
    assert (  trace_test.allow_request(100) );
    assert ( !trace_test.allow_request(200) );
    assert ( !trace_test.allow_request(300) );
    assert ( !trace_test.allow_request(400) );
    assert ( !trace_test.allow_request(500) );
    assert ( trace_test.allow_request(1150) );
    assert ( trace_test.allow_request(1250) );
    assert (!trace_test.allow_request(1500) );
}

void test_boundary(){
    RateLimiter boundary_test(1, 1000);
    assert (     boundary_test.allow_request(0) );
    assert ( !boundary_test.allow_request(1000) );
    assert (  boundary_test.allow_request(1001) );
    assert ( !boundary_test.allow_request(2000) );
    assert ( !boundary_test.allow_request(2001) );
    assert (  boundary_test.allow_request(2002) );
    assert ( !boundary_test.allow_request(3000) );
    assert ( !boundary_test.allow_request(3001) );
    assert ( !boundary_test.allow_request(3002) );
    assert (  boundary_test.allow_request(3003) );
}

void test_burst(){
    RateLimiter burst_test(3, 1000);
    assert (     burst_test.allow_request(500) );
    assert (     burst_test.allow_request(500) );
    assert (     burst_test.allow_request(500) );
    assert (    !burst_test.allow_request(500) );
    assert (    !burst_test.allow_request(500) );
    assert (   !burst_test.allow_request(1500) );
    assert (   !burst_test.allow_request(1500) );
    assert (    burst_test.allow_request(1501) );
    assert (    burst_test.allow_request(1501) );
    assert (    burst_test.allow_request(1501) );
    assert (   !burst_test.allow_request(1501) );
    assert (   !burst_test.allow_request(1501) );
}

void test_zero_max(){
    RateLimiter zero_max_test(0, 1000);
    assert (   !zero_max_test.allow_request(0) );
    assert ( !zero_max_test.allow_request(100) );
    assert ( !zero_max_test.allow_request(200) );
    assert ( !zero_max_test.allow_request(400) );
    assert ( !zero_max_test.allow_request(500) );
    assert (!zero_max_test.allow_request(1650) );
    assert (!zero_max_test.allow_request(2950) );
    assert (!zero_max_test.allow_request(4500) );
}

void test_negative_max(){
    RateLimiter negative_max_test(-5, 100);
    assert (   !negative_max_test.allow_request(0) );
    assert ( !negative_max_test.allow_request(100) );
    assert ( !negative_max_test.allow_request(200) );
    assert ( !negative_max_test.allow_request(400) );
    assert ( !negative_max_test.allow_request(500) );
    assert (!negative_max_test.allow_request(1650) );
    assert (!negative_max_test.allow_request(2950) );
    assert (!negative_max_test.allow_request(4500) );
}

void test_zero_window(){
    RateLimiter zero_window_test(1, 0);
    assert (   zero_window_test.allow_request(0) );
    assert ( zero_window_test.allow_request(100) );
    assert ( zero_window_test.allow_request(101) );
    assert ( zero_window_test.allow_request(102) );
    assert ( zero_window_test.allow_request(103) );
    assert ( zero_window_test.allow_request(200) );
    assert (!zero_window_test.allow_request(200) );
    assert ( zero_window_test.allow_request(201) );
    assert ( zero_window_test.allow_request(500) );
    assert (!zero_window_test.allow_request(500) );
    assert (!zero_window_test.allow_request(500) );
    assert (!zero_window_test.allow_request(500) );
    assert ( zero_window_test.allow_request(501) );
    assert (zero_window_test.allow_request(1650) );
    assert (zero_window_test.allow_request(2950) );
    assert (zero_window_test.allow_request(4500) );
}

void test_negative_window(){
    RateLimiter negative_window_test(1, -1);
    assert (   negative_window_test.allow_request(0) );
    assert ( negative_window_test.allow_request(100) );
    assert ( negative_window_test.allow_request(101) );
    assert ( negative_window_test.allow_request(102) );
    assert ( negative_window_test.allow_request(103) );
    assert ( negative_window_test.allow_request(200) );
    assert ( negative_window_test.allow_request(200) );
    assert ( negative_window_test.allow_request(201) );
    assert ( negative_window_test.allow_request(500) );
    assert ( negative_window_test.allow_request(500) );
    assert ( negative_window_test.allow_request(500) );
    assert ( negative_window_test.allow_request(500) );
    assert (negative_window_test.allow_request(4500) );
}

int main(){
    test_trace();
    test_boundary();
    test_burst();
    test_zero_max();
    test_negative_max();
    test_zero_window();
    test_negative_window();
    std::cout << "Passed\n";
    return 0;
}
 