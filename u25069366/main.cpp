#include <iostream>
#include "Task.h"
#include "TaskGroup.h"
#include "UnitTask.h"
#include "TaskState.h"
#include "Design.h"
#include "Implementation.h"
#include "UnderReview.h"
#include "Deployed.h"
#include "PriorityDecorator.h"
#include "PersonnelDecorator.h"
#include "TGIterator.h"
#include "StateIterator.h"

void section(const std::string& title) {
    std::cout << "\n========== " << title << " ==========\n";
}

// Placeholder for where a real test suite would run against a task and
// report whether it passed. A real implementation would check actual
// test results, code review approval, or whatever "passing" means in
// your domain. Swap this out once real test-running logic exists.
bool runTests(Task* task) {
    return true;
}

int main() {

    // ---------------------------------------------------------------
    section("1. COMPOSITE: build a 3-level nested hierarchy");
    // ---------------------------------------------------------------
    TaskGroup* project      = new TaskGroup("Website Relaunch");
    TaskGroup* backendWork  = new TaskGroup("Backend Work");
    TaskGroup* frontendWork = new TaskGroup("Frontend Work");

    UnitTask* dbSchema = new UnitTask("Design DB schema");
    UnitTask* authApi  = new UnitTask("Build auth API");
    UnitTask* homepage = new UnitTask("Build homepage UI");
    UnitTask* navbar   = new UnitTask("Build navbar component");

    backendWork->add(dbSchema);
    backendWork->add(authApi);

    frontendWork->add(homepage);
    frontendWork->add(navbar);

    project->add(backendWork);
    project->add(frontendWork);

    std::cout << "Full hierarchy state dump (Composite: leaf and group treated uniformly):\n";
    project->logState();

    std::cout << "\nAttempting add() on a leaf (UnitTask) - testing invalid Composite usage:\n";
    UnitTask* rejectedChild = new UnitTask("should not be allowed");
    try {
        dbSchema->add(rejectedChild);
        std::cout << "  No exception thrown (add() was silently ignored or allowed)\n";
    } catch (const std::exception& e) {
        std::cout << "  Caught expected exception: " << e.what() << "\n";
        delete rejectedChild; // add() threw before storing it, so it's still ours to free
    }

    // ---------------------------------------------------------------
    section("2. ITERATOR: full traversal without exposing internals");
    // ---------------------------------------------------------------
    std::cout << "Traversing top-level children of 'project' via TGIterator:\n";
    Iterator* it = project->begin();
    Iterator* endIt = project->end();
    while (!(*it == *endIt)) {
        Task& t = **it;
        std::cout << "  - " << t.getDescription() << "\n";
        ++(*it);
    }
    delete it;
    delete endIt;

    // ---------------------------------------------------------------
    section("3. ITERATOR: two independent traversals over the same structure");
    // ---------------------------------------------------------------
    Iterator* itA = project->begin();
    Iterator* itB = project->begin();
    ++(*itB);
    std::cout << "Iterator A is at: " << (**itA).getDescription() << "\n";
    std::cout << "Iterator B is at: " << (**itB).getDescription() << " (independently advanced)\n";
    delete itA;
    delete itB;

    // ---------------------------------------------------------------
    section("4. STATE: valid transitions through the full lifecycle");
    // ---------------------------------------------------------------
    UnitTask* feature = new UnitTask("Implement search feature");
    std::cout << "Initial state:\n";
    feature->logState();

    std::cout << "\nTransition: Design -> Implementation\n";
    feature->updateState(new Implementation(feature), runTests(feature));
    feature->logState();

    std::cout << "\nTransition: Implementation -> UnderReview\n";
    feature->updateState(new UnderReview(feature), runTests(feature));
    feature->logState();

    // ---------------------------------------------------------------
    section("5. STATE: invalid transition is rejected");
    // ---------------------------------------------------------------
    std::cout << "Attempting invalid transition: UnderReview -> Design (illegal skip)\n";
    feature->updateState(new Design(feature), runTests(feature));
    std::cout << "\nState after invalid attempt (should be unchanged, still UnderReview):\n";
    feature->logState();

    // ---------------------------------------------------------------
    section("6. STATE: reject path sends task back to Implementation");
    // ---------------------------------------------------------------
    std::cout << "Transition: UnderReview -> Implementation (reject)\n";
    feature->updateState(new Implementation(feature), runTests(feature));
    feature->logState();

    std::cout << "\nRe-submitting: Implementation -> UnderReview -> Deployed\n";
    feature->updateState(new UnderReview(feature), runTests(feature));
    feature->updateState(new Deployed(feature), runTests(feature));
    feature->logState();

    std::cout << "\nAttempting transition after Deployed (should be rejected/no-op):\n";
    feature->updateState(new Implementation(feature), runTests(feature));
    feature->logState();

    // ---------------------------------------------------------------
    section("7. DECORATOR: single decorator adds behaviour, forwards the rest");
    // ---------------------------------------------------------------
    UnitTask* bugfix = new UnitTask("Fix login bug");
    Task* prioritized = new PriorityDecorator(bugfix, "High");
    std::cout << "Decorated task logState() output:\n";
    prioritized->logState();
    std::cout << "Decorated task getDescription() still forwards to wrapped task: "
              << prioritized->getDescription() << "\n";

    // ---------------------------------------------------------------
    section("8. DECORATOR: stacked decorators");
    // ---------------------------------------------------------------
    UnitTask* deployTask = new UnitTask("Deploy to production");
    Task* withPriority = new PriorityDecorator(deployTask, "Critical");
    Task* withBoth      = new PersonnelDecorator(withPriority, "Junior (DevOps)");
    std::cout << "Stacked decorator logState() output (Personnel wraps Priority wraps UnitTask):\n";
    withBoth->logState();

    // ---------------------------------------------------------------
    section("9. DECORATOR interacting with COMPOSITE and STATE");
    // ---------------------------------------------------------------
    TaskGroup* sprint = new TaskGroup("Sprint 12");
    sprint->add(withBoth);
    std::cout << "Sprint group containing a decorated task:\n";
    sprint->logState();

    std::cout << "\nAdvancing decorated task's state through the group:\n";
    withBoth->updateState(new Implementation(deployTask), runTests(withBoth));
    sprint->logState();

    // ---------------------------------------------------------------
    section("10. STATE ITERATOR: filtering children by current state");
    // ---------------------------------------------------------------
    TaskGroup* filterGroup = new TaskGroup("Mixed States");
    UnitTask* t1 = new UnitTask("Task A");
    UnitTask* t2 = new UnitTask("Task B");
    UnitTask* t3 = new UnitTask("Task C");
    t2->updateState(new Implementation(t2), runTests(t2));
    filterGroup->add(t1);
    filterGroup->add(t2);
    filterGroup->add(t3);

    std::cout << "All tasks before filtering:\n";
    filterGroup->logState();

    std::cout << "\nFiltering for tasks currently in 'Design' state:\n";
    for (Task* child : filterGroup->getChildren()) {
        if (child->getState()->state() == "Design") {
            std::cout << "  - " << child->getDescription() << " is in Design\n";
        }
    }

    // ---------------------------------------------------------------
    section("11. Runtime structural change during traversal - open design question");
    // ---------------------------------------------------------------
    std::cout << "Rubric requires a documented policy for structural change during traversal.\n";
    std::cout << "This system does not yet enforce iterator invalidation on structural change -\n";
    std::cout << "flagging this as something the team still needs to design (Task 3 requirement).\n";

    // ---------------------------------------------------------------
    section("CLEANUP: ownership / destruction");
    // ---------------------------------------------------------------
    std::cout << "Deleting 'project' should cascade-delete backendWork, frontendWork, and all leaves.\n";
    delete project;
    delete feature;
    delete prioritized;
    delete sprint;
    delete filterGroup;

    std::cout << "\nAll done. If AddressSanitizer reports no leaks or errors below, cleanup is correct.\n";

    return 0;
}