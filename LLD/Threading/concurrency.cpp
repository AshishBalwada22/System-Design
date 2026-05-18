1) concurency
2) thread
3) join_detach
4) pass_by_value_and_reference
5) concurrency_pitfall
6) race
7) mutex_and_lock_guard
8) unique_lock
9) deadlock
10) condition_variable_and_production
11) thread_safe_queue
12) atomic
13) call_once
14) promise_future_async

1) concurrency v/s parallelism

// Not concurrent, Not parallel
1 core 
Task1 -> Task2 (perform task sequentially)

// Concurrent, Not parallel
1 core
Task1 -> Task2 -> Task1 -> Task2 (switching in between the task)

// Not concurrent, parallel (multiple core/server)
multiple core
core 1
Task1 -> Task2 (perform task sequentially)
core 2
Task3 -> Task4

// concurrent, parallel
multiple core
core1
Task1 -> Task2 -> Task1 ->Task2 
core2
Task3 -> Task4 -> Task3 -> Task4

// 1 core is equivalent to 1 thread, thread is a light weight process task.

2) Pitfall of concurrency

- Race condition
- Deadlock
- Memory visibility

concurrency - interleaving tasks
parallelism - simultaneous tasks
Thread share memory, process are isloated.

Avoid dangling reference - concurrency_pitfall.cpp

3) Mutual exclusion with Mutexes and Locks

Race condition - that's why we need mutual exclusion
Critical section - code must run by one thread at a time

RAII - Resource Acquisition Is Initialization

prefer lock_guard, guard the exact shared state you mutate(change)
