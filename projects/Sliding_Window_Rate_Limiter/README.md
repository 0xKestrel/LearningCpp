# Sliding Window Log Rate Limiter (C++20)

A small, memory-efficient rate limiter built on the **sliding window log** algorithm.
It answers one question: *"may this request go through right now?"*

## Problem statement

Design a class `RateLimiter` for API middleware.

- Constructor: `RateLimiter(int max_requests, int window_size_ms)`
  - `max_requests`: maximum allowed requests inside one window.
  - `window_size_ms`: window length in milliseconds.
- `bool allow_request(long long timestamp_ms)`
  - `true` if the request is allowed, `false` if it must be dropped.
- Old timestamps must be pruned so memory does not grow forever, and each call should be fast.

## Approach

Keep a log (a FIFO queue) of the timestamps of **allowed** requests only.

On every call to `allow_request(t)`:

1. **Clean up:** while the oldest timestamp has expired, pop it.
2. **Check:** if fewer than `max_requests` timestamps remain, push `t` and return `true`.
3. **Otherwise:** return `false` (nothing is stored).

### Why `std::queue`

- Timestamps arrive in increasing order, so the log is always sorted oldest to newest.
- I only ever push at the back (newest) and look at or pop the front (oldest). That is exactly FIFO.
- `std::queue` is an adaptor over `std::deque` by default, so both ends are O(1). A `vector` would have to shift every element on each front removal.
- `std::queue` deliberately exposes only the operations I need, which makes misuse harder.

### Why cleanup is lazy

Nothing runs on a timer. Expired entries are removed only when a request arrives. That is enough, because an old entry can only affect an answer when a new request is being decided, and it is cheaper than running a background clock.

Because the log is sorted, cleanup only ever inspects the **front**. If the oldest entry is still inside the window, all the others are too, so the loop stops.

## Design decisions

| Decision | Choice | Why |
|----------|--------|-----|
| Window boundary | Half-open window `(t - W, t]`. An entry exactly `W` ms old has **expired** (`>=`). | "N requests per W ms" should mean exactly W milliseconds. |
| Rejected requests | **Not logged.** | Otherwise a client that keeps spamming would keep refilling the log and stay blocked forever, even though none of its requests were allowed. |
| Signed/unsigned comparison | `std::cmp_less(log_.size(), max_requests_)` | `size()` is unsigned and `max_requests_` is a signed `int`. A plain `<` would silently convert a negative `int` to a huge unsigned value. `cmp_less` compares true mathematical values. Needs C++20. |
| `max_requests <= 0` | Every request is rejected. | `cmp_less(size, 0)` and `cmp_less(size, -5)` are always false. Behavior is implicit, so it is covered by tests. |
| `window_size_ms <= 0` | Limiting is effectively disabled. | With `>=`, an entry of age 0 is already expired, so the log is emptied on every call. Documented, not endorsed: a real system should probably reject such input. |
| Timestamps | Must be **non-decreasing**. | The queue is only sorted if time never goes backwards. Out-of-order input is outside the problem and is not handled. |
| Which user? | Not this class's job. | One `RateLimiter` represents one stream. The middleware picks the right limiter (e.g. a map from user ID or API key to limiter). |
| `logged_count()` | A read-only `const` accessor, public only so tests can observe memory use. | Widens the interface slightly in exchange for being able to verify the memory bound directly. |

### A correction I made along the way: `>` vs `>=`

My first version used `>` (an entry exactly `W` ms old still counted). That makes the window `[t - W, t]`, which spans **W + 1** milliseconds.
I noticed when working out the expected count for the large-scale test: the allowed pattern repeated every **1001** ms instead of 1000.
I changed it to `>=` and updated the boundary, burst and zero-window tests together.

**Why `>=` is the right reading:** the problem says "N requests per W ms". That is a statement about a window that is exactly W milliseconds long, so a request made exactly W ms after an earlier one should be allowed, because the earlier one has just left the window. With `>` the earlier request lingered for one extra millisecond.

This was not really a misunderstanding of the assignment. It was an ambiguity (is "W ms ago" inside the window or not?). I first picked the inclusive reading, then checked it against my own large-scale test, saw it contradicted the wording, and switched to the interpretation that matches it. Takeaway: boundaries are decisions, and a test that works out the expected count independently is what exposes a wrong one.

## Complexity

Let `K = max_requests`.

- **Time per call:** amortized **O(1)**. Every timestamp is pushed at most once and popped at most once, so across `N` calls the total number of pops is at most `N`.
- **Worst case for a single call:** **O(K)**, when the whole log expires at once (for example after a long idle gap).
- **Space:** **O(K)**. A push only happens when the log has fewer than `K` entries, so the log can never exceed `K`, whether 1 million or 1 trillion requests arrive.

## Build and run

Requires a compiler with C++20 (for `std::cmp_less`), e.g. GCC 10 or newer.

```bash
g++ -std=c++20 -Wall -Wextra main.cpp -o test
./test          # on Windows PowerShell: .\test.exe
```

Expected output: `Passed` and no compiler warnings.

## Project layout

```
Sliding_Window_Rate_Limiter/
├── rate_limiter.hpp   # the RateLimiter class (header-only)
├── main.cpp           # tests (plain assert)
└── README.md
```

## Tests

Tests live in `main.cpp` and use plain `assert`. Each scenario uses a fresh limiter. Expected values were worked out by hand first, not copied from the program's output.

| Test | What it proves |
|------|----------------|
| `test_trace` | A hand-traced sequence (`max=2, window=1000`) matches, including several entries expiring in one call. |
| `test_boundary` | The exact edge: at `W - 1` ms a request is rejected, at exactly `W` ms the old entry has expired. |
| `test_burst` | Requests at the same timestamp each count separately. |
| `test_zero_max` / `test_negative_max` | `max_requests <= 0` rejects everything (and proves why `cmp_less` is used). |
| `test_zero_window` / `test_negative_window` | A non-positive window disables limiting. |
| `test_scale` | One million requests at 1 ms spacing. Expects 2 allowed per 1000 ms cycle (2000 total), and asserts after every call that the log never holds more than `max_requests` entries. |

To check that the tests can actually fail, I temporarily changed the code (for example `>=` to `>`) and confirmed that the relevant tests failed, then restored it.

## What I learned

- **Choosing a container by operations:** list the operations first (push back, peek front, pop front), then pick the structure that makes those O(1).
- **Short-circuit evaluation:** `!log_.empty() && log_.front() ...` is safe only because the emptiness check comes first.
- **Signed vs unsigned:** mixing them silently converts negatives into huge numbers. `std::cmp_less` and friends exist for this.
- **Boundaries are decisions:** `>` vs `>=` changes the meaning of the window. Tests at the exact edge (and one step either side) are the most valuable ones.
- **Tests can be wrong too:** hand-trace expected values, and never copy them from the code's output.
- **Equivalent mutants:** replacing `while` with `if` returns the same true/false answers. Only the stored size differs, so return values alone can't catch it.
- **`const` correctness:** member functions that only read should be `const`.

## Things to explore next

Things I haven't learned yet, noted so I can come back to them:

- **Thread safety:** a real server calls the limiter from many threads at once, and two threads modifying the queue together is a data race. A `std::mutex` lock around `allow_request` should fix that. I haven't used one yet.
- **Input validation:** right now bad settings (a zero or negative window) silently disable limiting. Throwing `std::invalid_argument` from the constructor would make that fail loudly instead.
- **One limiter per user:** a map from user ID to `RateLimiter`, e.g. `std::unordered_map<std::string, RateLimiter>`. It would also need to evict users who have gone idle, or the map itself would grow forever.
- **Real test framework:** move from plain `assert` to GoogleTest or Catch2, which report every failure with a clear message.
- **Other algorithms:** compare against a fixed-window counter and a token bucket (less memory, different trade-offs).
