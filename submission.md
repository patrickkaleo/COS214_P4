---
geometry:
  - top=1in
  - bottom=1in
  - left=1in
  - right=1in
header-includes:
  - \usepackage{float}
  - \makeatletter\def\fps@figure{H}\makeatletter
---


# COS214 Practical 4

__Courtesy of__

- Patrick Simuyemba : `u25632354`
- N'des Junior Lungwangu : `u25069366`
- member3 : `never showed up`

__Task 1: Design the System__

_Domain:_ __`Software delivery workflow`__

_Problem_

- A software-delivery workflow is not a flat list of jobs. Work is nested (epics, stories, and unit tasks), each item moves through a lifecycle, the same tree must be walkable in more than one order, and extra concerns such as priority or extra personnel must be stacked onto a task without rewriting the task types. The demo tree we actually built is `Website Relaunch` with `Backend Work` / `Frontend Work` and the unit tasks under them.

_Complete UML diagram_

![Complete UML Diagram of the design of our System](docs/_task1_uml.png)

_GoF Participants in [Iterator, Composite, decorator, State]_

_Iterator_

- Iterator: `Iterator`
- ConcreteIterator: `TGIterator, StateIterator`
- Aggregate: `Task`
- ConcreteAggregate: `TaskDecorator, UnitTask, TaskGroup`

_Composite_

- Component: `Task`
- Leaf: `UnitTask`
- Composite: `TaskGroup`

_Decorator_

- Component: `Task`
- ConcreteComponent: `UnitTask`
- Decorator: `TaskDecorator`
- ConcreteDecorator: `PersonnelDecorator, PriorityDecorator`

_State_

- State: `TaskState`
- context: `Task`
- ConcreteState: `Design, Implementation, UnderReview, Deployed`


 _Rationale for important design and ownership decisions_

- A `Task` starts in `Design` (the constructor does `state = new Design(this)`). Over it's lifetime it can move `Design -> Implementation -> Under Review -> Deployed`. `UnderReview` can send work back to `Implementation` (reject). `Deployed` is absorbing, it just says the task is already deployed. `updateState(requested, testPassed)` is the event. The current concrete state decides if the request is legal. Illegal requests print `Invalid Request` and `delete requested` so we dont leak the object that nobody adopted. A task owns it's `TaskState` and deletes it in the destructor / `setState`.

- A `TaskGroup` contains sub tasks and naturally owns these sub tasks. When the TaskGroup goes out of scope, it must delete it's sub tasks appropriately. `add` ignores null and duplicates. `remove` takes a child out of the vector but does not delete it (so we can wrap it and add it back, like in the sprint fast-track scenario).

- Features can be added to a task dynamically. For example, you can raise the priority of a task throught the `PriorityDecorator` and add personnel to work on a task through the `PersonnelDecorator`. The decorator owns the Task which it is decorating and must delete it when it goes out of scope. `updateState` and `logState` just forward into `wrappedTask`.

- Two iterators: `TGIterator` walks the children vector of a group (order as stored). `StateIterator` is meant to pick children matching a lifecycle. `begin()` / `end()` return fresh `Iterator*` each time so two clients can walk the same group independently. Client has to `delete` those pointers.


__Task 2: Implement the core model__


__Task 3: Dynamic Behaviour and Design Decisions__


__Task 4: UML Diagram Portfolio__

_Object diagram_

![Object diagram of nested task objects](docs/_task4_object.png)

_State diagram_

- Snapshot of `Task` lifecycle through Design and Implementation (This idea applies to other states)

![State diagram of a Task lifecycle](docs/_task4_state.png)

_Activity diagram 1 - status walk of Website Relaunch_

- Assemble the epic then walk it with `TGIterator`

![Activity diagram 1: traverse a work group](docs/_task4_AD1.png)

_Activity diagram 2 - lifecycle requests_

- `updateState` through `UnitTask` / `Design` / `Implementation` swimlanes.

![Activity diagram 2: updateState through Design then Implementation](docs/_task4_AD2.png)

_Activity diagram 3 - decorator stack then update_

- Personnel and Priority forward `updateState` into `UnitTask` / `Design`.

![Activity diagram 3: decorator forwarding](docs/_task4_AD3.png)

__Task 5: Debugging and Memory Investigation__

_GDB: traversal_

```
gdb ./taskforge
(gdb) break TGIterator::operator++
(gdb) run
(gdb) print (*current)->getDescription()
(gdb) continue
```

First hit after `project->begin()` is `Backend Work`, next is `Frontend Work`. That is what I expected: `TGIterator` only walks the top-level children vector of `Website Relaunch`, it does not by itself walk into `Design DB schema`. `logState` on a group still dumps the nested leaves because `TaskGroup::logState` recurses.

_GDB: decorator / state_

```
(gdb) break TaskDecorator::updateState
(gdb) break Design::updateState
(gdb) run
(gdb) backtrace
```

On the stacked task (`PersonnelDecorator` wrapping `PriorityDecorator` wrapping the unit task) the stack is `main` -> decorator `updateState` -> `Task::updateState` -> `Design::updateState`. `print testPassed` and `print requested->state()`.

_Valgrind_

```
make mem
```

_Bug_

Symptom: Design -> Implementation prints the new status, but Valgrind still complains about the state object.

Cause: `Design::updateState` calls `context->setState(requested)`. `Task::setState` does `delete this->state`, and that pointer is the same `Design` whose `updateState` has not hit `}` yet. `setState` does not call `updateState`; `updateState` called `setState`, then C++ returns into a destroyed object. Decorator `updateState` only forwards, so the delete still happens on the inner `UnitTask`'s `Design`.


__Task 6: Docker and GitHub Workflow__

Dockerfile is Ubuntu 22.04 with `g++`, `make`, `gdb`, `valgrind`. It copies `makefile`, `include/`, `src/` and `make`s `taskforge`. Default cmd is `./taskforge`.

```
docker build -t taskforge .
docker run --rm taskforge
docker run --rm --entrypoint make taskforge mem
```

GDB inside docker needs ptrace:

```
docker run --rm -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --entrypoint gdb taskforge ./taskforge
```

_Reflection_

- Work was split along the four patterns and kept on two branches, `dev` and `ndes`. We integrated by merge and pull rather than a single end-of-week dump. There are no GitHub pull requests; collaboration shows up in those branches and in merge commit `4f84853`.

- Patrick Simuyemba (`u25632354`) owned the repo setup, Task 1 design, most of the Composite and Iterator core (Task 2), the UML activity and object diagrams (Task 4), and Tasks 5-6 (GDB/Valgrind, Dockerfile, `taskforge` Makefile, README). N'des Junior Lungwangu (`u25069366`) owned State and Decorator and the demo `main`.

- Patrick's line starts at `ed53f64` and `f638ecc` (1 Sep): initial repo, `submission.md`, and the PDF/zip scripts. `329dd78` (2 Sep) is Task 1 - domain, class diagram, and GoF mapping. `77bd118`, `7bbe88a`, and `eeaff87` (3-5 Sep) are the Task 2 iterator slice: `begin()`/`end()`, iterator interfaces, and `TGIterator`. `dee0338` (5 Sep) is the overlapping Decorator and Iterator work. `cea6a01` (6 Sep) updates the Task 4 figures.

- N'des appears on `dev` from `d45ebe6` (3 Sep, names and delegation). `b13f6c6` (4 Sep) adds constructors and `setState`. `4f84853` (6 Sep, *Decorator fixes*) is a merge with two parents: N'des's decorator branch and Patrick's iterator line. That is the integration point. `a58bb04` (6 Sep, on `ndes`) is the Task 2 demo, brought onto `dev` with `git pull origin ndes`.

- `dev` was the integration branch; `ndes` was N'des's feature line. The two histories met in `4f84853` and in the later fast-forward of `ndes` onto `dev`.


__Task 7: Integration and Demonstration__


