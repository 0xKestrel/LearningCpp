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

int main(){
    test_trace();
    test_boundary();
    test_burst();
    std::cout << "Passed\n";
    return 0;
}
 