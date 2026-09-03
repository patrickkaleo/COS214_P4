## Task 1 — Design
**Patrick:**
- Finalize `Task` abstract class member list and confirm `begin()/end()` return fresh `Iterator*` instances each call
- Design the second traversal behavior (your diagram only shows `TGIterator` — needs one more that differs meaningfully in order/selection, e.g. only-incomplete-tasks or leaf-only traversal)
- Write up Composite + Iterator GoF participant mapping (already drafted, refine as design firms up)

**N'des:**
- Finalize invalid-transition rules for `Implementation → UnderReview → Deployed` (what happens on e.g. `Deployed → Implementation`?)
- Design what `PersonnelDecorator` and `PriorityDecorator` actually *change* behaviorally (not just cosmetic)
- Write up State + Decorator GoF participant mapping (already drafted)

**Joint:**
- Resolve the double-ownership/double-delete problem before anyone writes a destructor
- Finish the `docs/_task1_uml.png` diagram to reflect the second iterator once designed
- Write the domain description + rationale section (mostly done, needs the ownership fix reflected)

## Task 2 — Core Model
**Patrick:**
- `Task` base class (shared — coordinate signatures with you before locking)
- `UnitTask` (Leaf)
- `TaskGroup` (Composite) — `add(child)`, recursive destructor
- `Iterator` (abstract), `TGIterator` + second concrete iterator
- Standalone test: build a 3+-level nested tree, run both iterators independently over it at once

**N'des:**
- `TaskState` (abstract) + `Implementation`, `UnderReview`, `Deployed`
- `Task::updateState()`, `logState()` delegation logic
- `TaskDecorator` (abstract) + `PersonnelDecorator`, `PriorityDecorator`
- Standalone test: walk a task through valid/invalid transitions, stack both decorators on it, call through the chain

**Joint:**
- Once both standalone tests pass, integrate: put a decorated, stateful `Task` inside Patrick's `TaskGroup` and traverse it — this is where the ownership bug will actually surface if unresolved

## Task 3 — Dynamic Behaviour
**Patrick:**
- Contributes the traversal half of both joint scenarios (nested structure being walked)
- Drives the traversal-invalidation policy (live vs. snapshot) since it's his iterators

**N'des:**
- Contributes the state-change and decoration half of both scenarios
- Ensures at least one scenario shows a decorated object behaving correctly mid-flow, not just constructed

**Joint (this task is inherently joint, can't fully separate):**
- Design and script the two actual runtime scenarios together
- Pick and implement the one required "structural or behavioural change during execution" (e.g. an item moves `TaskGroup`, or gets decorated live)
- Document the traversal-invalidation policy as a defensible written decision

## Task 4 — UML Diagram Portfolio
**Patrick:**
- Object diagram: real runtime slice of nested `TaskGroup`/`UnitTask`
- One Activity Diagram: traversal made visible in a larger workflow (not hidden behind "process all")

**N'des:**
- State diagram: your three-state lifecycle
- One Activity Diagram: conditional behaviour tied to lifecycle/runtime config

**Joint:**
- Class diagram already exists, keep it in sync as code changes
- Third Activity Diagram (team's choice, distinctive workflow) — pick together
- Verify across all diagrams: fork/join, composite/called activity, and swimlanes are each used at least once total — divide who puts which technique where so you don't duplicate or miss one

## Task 5 — Debugging
**Patrick:**
- Own the GDB walkthrough of a traversal (breakpoint in `TGIterator::operator++`, inspect current node)
- Own Valgrind investigation of `TaskGroup` recursive destruction (classic leak spot)

**N'des:**
- Own the GDB walkthrough of a state transition or decorator stack (breakpoint on `updateState`, inspect active decorator chain)
- Write up whichever real bug either of you actually hits — symptom, cause, evidence, fix (doesn't have to be from your half specifically, just needs one documented)

**Joint:**
- Final full Valgrind pass on the integrated system (`--leak-check=full --show-leak-kinds=all`) — this is where the ownership fix gets proven or disproven

## Task 6 — Docker and GitHub
**Patrick or N'des (pick one, don't split):**
- Dockerfile + Makefile (`taskforge` binary, g++/make/gdb/valgrind available)

**The other:**
- README.md with reproducible build/run/GDB/Valgrind commands

**Joint, ongoing (not a one-time task):**
- Commit incrementally through the week on your respective files — this is graded as "genuine work by all team members across the development period," a single end-of-week dump won't satisfy it
- docs/ directory with all diagrams
- Reflection section in the PDF referencing actual commits/PRs

## Task 7 — Demo
**Joint:**
- Script a ~5 minute narrative in the domain (not a pattern-by-pattern menu)
- Each of you rehearse explaining not just your own half but the basics of the other's — a tutor can ask either of you anything
- Decide who narrates which segment and where the handoff between structure and behaviour happens on screen

---

One structural note: Tasks 3, 6, and 7 are unavoidably joint regardless of how you split 1/2/4/5 — budget real calendar time for that, not just "integration at the end."