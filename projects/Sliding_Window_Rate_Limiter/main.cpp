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

int main(){
    test_trace();
    std::cout << "Passed\n";
    return 0;
}
