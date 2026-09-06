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

void section(const std::string &title)
{
    std::cout << "\n========== " << title << " ==========\n";
}

// Placeholder for where a real test suite would run against a task and
// report whether it passed. A real implementation would check actual
// test results, code review approval, or whatever "passing" means in
// your domain. Swap this out once real test-running logic exists.
bool runTests(Task *task)
{
    return true;
}

// =====================================================================
// TASK 3 - SCENARIO 1: "A feature gets fast-tracked mid-sprint"
//
// Demonstrates, together: traversal of nested objects (TGIterator),
// a decorated object participating in normal system behaviour, a
// runtime structural change (a plain task is replaced in-place by
// its decorated version), and state-dependent behaviour (the task
// then progresses through its lifecycle while inside the group).
// =====================================================================
void scenarioFastTrackFeature()
{
    section("TASK 3 - SCENARIO 1: Fast-tracking a feature mid-sprint");

    TaskGroup *sprint = new TaskGroup("Sprint 12");
    UnitTask *loginBug = new UnitTask("Fix login bug");
    sprint->add(loginBug);
    sprint->add(new UnitTask("Update changelog"));

    std::cout << "Sprint before any changes (traversed via TGIterator):\n";
    Iterator *it = sprint->begin();
    Iterator *end = sprint->end();
    while (!(*it == *end))
    {
        std::cout << "  - " << (**it).getDescription()
                  << " [" << (**it).getState()->state() << "]\n";
        ++(*it);
    }
    delete it;
    delete end;

    std::cout << "\n'Fix login bug' gets flagged urgent mid-sprint.\n";
    std::cout << "Runtime change: removing the plain task and replacing it with a decorated version.\n";
    sprint->remove(loginBug); // structural change: item removed
    Task *urgentBug = new PriorityDecorator(loginBug, "Critical");
    sprint->add(urgentBug); // structural change: decorated version added back

    std::cout << "\nThe decorated task now progresses through its lifecycle while inside the group:\n";
    urgentBug->updateState(new Implementation(loginBug), runTests(urgentBug));

    std::cout << "\nSprint after the change (decoration visible, state updated):\n";
    sprint->logState();

    delete sprint; // cascades: deletes urgentBug -> deletes loginBug, and the other UnitTask
}

// =====================================================================
// TASK 3 - SCENARIO 2: "A task fails review and gets kicked back"
//
// Demonstrates, together: a second, different traversal purpose
// (StateIterator, filtering by state rather than visiting everything),
// state-dependent behaviour via the reject path, and a runtime change
// in the form of a state regression rather than a forward transition.
//
// NOTE: StateIterator::operator++ currently only advances to the
// first match starting from its current position - it does not skip
// past a match it is already sitting on. So this scenario uses it to
// find "a" task in a given state, not to enumerate every match. That
// limitation is worth raising with Patrick since it affects how
// StateIterator can safely be used elsewhere.
// =====================================================================
void scenarioReviewRejection()
{
    section("TASK 3 - SCENARIO 2: A task fails review and gets kicked back");

    TaskGroup *sprint = new TaskGroup("Sprint 13");
    UnitTask *deployTask = new UnitTask("Deploy to production");
    sprint->add(deployTask);
    sprint->add(new UnitTask("Write release notes"));

    // Move deployTask to UnderReview first so there's something to find.
    deployTask->updateState(new Implementation(deployTask), runTests(deployTask));
    deployTask->updateState(new UnderReview(deployTask), runTests(deployTask));

    std::cout << "Finding a task currently 'Under Review' via StateIterator:\n";
    TaskState *underReviewFilter = new UnderReview(nullptr);
    StateIterator *sit = sprint->createStateIterator(underReviewFilter);
    ++(*sit); // advances to the first match, or to end() if none found
    Task &found = **sit;
    std::cout << "  Found: " << found.getDescription()
              << " [" << found.getState()->state() << "]\n";
    delete sit;
    delete underReviewFilter; // this comparison object is ours, StateIterator never adopts it

    std::cout << "\nReviewer rejects it. Runtime change: state regresses backward, not forward.\n";
    deployTask->updateState(new Implementation(deployTask), runTests(deployTask));

    std::cout << "\nFinding a task currently 'Implementation' via StateIterator (should now find it):\n";
    TaskState *implementationFilter = new Implementation(nullptr);
    StateIterator *sit2 = sprint->createStateIterator(implementationFilter);
    ++(*sit2);
    Task &foundAgain = **sit2;
    std::cout << "  Found: " << foundAgain.getDescription()
              << " [" << foundAgain.getState()->state() << "]\n";
    delete sit2;
    delete implementationFilter; // same reasoning: ours to free

    delete sprint;
}

int main()
{

    // ---------------------------------------------------------------
    section("1. COMPOSITE: build a 3-level nested hierarchy");
    // ---------------------------------------------------------------
    TaskGroup *project = new TaskGroup("Website Relaunch");
    TaskGroup *backendWork = new TaskGroup("Backend Work");
    TaskGroup *frontendWork = new TaskGroup("Frontend Work");

    UnitTask *dbSchema = new UnitTask("Design DB schema");
    UnitTask *authApi = new UnitTask("Build auth API");
    UnitTask *homepage = new UnitTask("Build homepage UI");
    UnitTask *navbar = new UnitTask("Build navbar component");

    backendWork->add(dbSchema);
    backendWork->add(authApi);

    frontendWork->add(homepage);
    frontendWork->add(navbar);

    project->add(backendWork);
    project->add(frontendWork);

    std::cout << "Full hierarchy state dump (Composite: leaf and group treated uniformly):\n";
    project->logState();

    std::cout << "\nAttempting add() on a leaf (UnitTask) - testing invalid Composite usage:\n";
    UnitTask *rejectedChild = new UnitTask("should not be allowed");
    dbSchema->add(rejectedChild); //add does nothing for UnitTasks
    delete rejectedChild; // still ours to free

    // ---------------------------------------------------------------
    section("2. ITERATOR: full traversal without exposing internals");
    // ---------------------------------------------------------------
    std::cout << "Traversing top-level children of 'project' via TGIterator:\n";
    Iterator *it = project->begin();
    Iterator *endIt = project->end();
    while (!(*it == *endIt))
    {
        Task &t = **it;
        std::cout << "  - " << t.getDescription() << "\n";
        ++(*it);
    }
    delete it;
    delete endIt;

    // ---------------------------------------------------------------
    section("3. ITERATOR: two independent traversals over the same structure");
    // ---------------------------------------------------------------
    Iterator *itA = project->begin();
    Iterator *itB = project->begin();
    ++(*itB);
    std::cout << "Iterator A is at: " << (**itA).getDescription() << "\n";
    std::cout << "Iterator B is at: " << (**itB).getDescription() << " (independently advanced)\n";
    delete itA;
    delete itB;

    // ---------------------------------------------------------------
    section("4. STATE: valid transitions through the full lifecycle");
    // ---------------------------------------------------------------
    UnitTask *feature = new UnitTask("Implement search feature");
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
    UnitTask *bugfix = new UnitTask("Fix login bug");
    Task *prioritized = new PriorityDecorator(bugfix, "High");
    std::cout << "Decorated task logState() output:\n";
    prioritized->logState();
    std::cout << "Decorated task getDescription() still forwards to wrapped task: "
              << prioritized->getDescription() << "\n";

    // ---------------------------------------------------------------
    section("8. DECORATOR: stacked decorators");
    // ---------------------------------------------------------------
    UnitTask *deployTask = new UnitTask("Deploy to production");
    Task *withPriority = new PriorityDecorator(deployTask, "Critical");
    Task *withBoth = new PersonnelDecorator(withPriority, "Junior (DevOps)");
    std::cout << "Stacked decorator logState() output (Personnel wraps Priority wraps UnitTask):\n";
    withBoth->logState();

    // ---------------------------------------------------------------
    section("9. DECORATOR interacting with COMPOSITE and STATE");
    // ---------------------------------------------------------------
    TaskGroup *sprint = new TaskGroup("Sprint 12");
    sprint->add(withBoth);
    std::cout << "Sprint group containing a decorated task:\n";
    sprint->logState();

    std::cout << "\nAdvancing decorated task's state through the group:\n";
    withBoth->updateState(new Implementation(deployTask), runTests(withBoth));
    sprint->logState();

    // ---------------------------------------------------------------
    section("10. STATE ITERATOR: filtering children by current state");
    // ---------------------------------------------------------------
    TaskGroup *filterGroup = new TaskGroup("Mixed States");
    UnitTask *t1 = new UnitTask("Task A");
    UnitTask *t2 = new UnitTask("Task B");
    UnitTask *t3 = new UnitTask("Task C");
    t2->updateState(new Implementation(t2), runTests(t2));
    filterGroup->add(t1);
    filterGroup->add(t2);
    filterGroup->add(t3);

    std::cout << "All tasks before filtering:\n";
    filterGroup->logState();

    std::cout << "\nFiltering for tasks currently in 'Design' state:\n";
    for (Task *child : filterGroup->getChildren())
    {
        if (child->getState()->state() == "Design")
        {
            std::cout << "  - " << child->getDescription() << " is in Design\n";
        }
    }

    // ---------------------------------------------------------------
    section("11. Runtime structural change during traversal - open design question");
    // ---------------------------------------------------------------
    std::cout << "Rubric requires a documented policy for structural change during traversal.\n";
    std::cout << "This system does not yet enforce iterator invalidation on structural change -\n";
    std::cout << "flagging this as something the team still needs to design (Task 3 requirement).\n";

    scenarioFastTrackFeature();
    scenarioReviewRejection();

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