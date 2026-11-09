# System-Design

Low-level design (LLD) in C++ — the same problems that get asked in interviews, written out as code I can compile, run, and explain line by line.

Most LLD material is diagrams. This repo is the part after the diagram: real classes, real ownership, real locks.

## What's inside

```
LLD/
├── SOLID_PRINCIPLE.cpp              one file per principle: the violation, then the fix
├── UML.cpp                          reading and writing the diagrams
├── creational_design_pattern/       factory, abstract factory, builder, singleton
├── structural_design_pattern/       adapter, decorator
├── behavioral_design_pattern/       strategy, observer, command, template method
├── Threading/                       14 programs, basics → thread-safe queue
└── LLD Questions/
    └── parking_lot.cpp              a full problem walked through a 10-step framework
LLD_Questions/
└── 1_Google_Doc/                    bad_design.cpp → good_design.cpp, same problem twice
OOPS/                                fundamentals
consistency.txt, database_deep_dive.txt
```

Each design pattern has a UML image sitting next to its `.cpp` file, so the diagram and the implementation stay in sync.

## The concurrency track

The part of LLD that most write-ups skip and most interviews probe:

`thread` · `join_detach` · `mutex_and_lock_guard` · `unique_lock` · `condition_variable_and_producer_consumer` · `promise_future_async` · `atomic` · `call_once` · `race` · `deadlock` · `concurrency_pitfall` · `thread_safe_queue`

`thread_safe_queue.cpp` is the one to read if you only read one: a bounded producer-consumer queue built on `mutex` + `condition_variable`, with the predicate-based `wait` that makes it correct rather than lucky.

## The LLD problems

`parking_lot.cpp` opens with the framework it was designed against, not just the answer:

1. Clarify and scope requirements — functional vs non-functional
2. Use cases and APIs
3. Data model — entities and relationships
4. Core class design
5. Identify and apply patterns
6. Sequence for the main flow
7. Concurrency and consistency
8. Edge cases and error handling
9. Implementation
10. Extension and scaling

`LLD_Questions/1_Google_Doc/` takes the opposite approach: one problem designed badly, then designed well, so the cost of each violation is visible in the diff.

## Building

```bash
g++ -std=c++17 -Wall -pthread "LLD/LLD Questions/parking_lot.cpp" -o parking_lot && ./parking_lot
```

`-pthread` is required for everything under `Threading/`.
