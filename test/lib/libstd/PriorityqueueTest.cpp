
#include <TestCase.h>
#include <TestRunner.h>
#include <TestInt.h>
#include <TestMain.h>
#include <Priorityqueue.h>
#include <String.h>

TestCase(PriorityqueueConstruct)
{
    Priorityqueue<int, 64> q;

    // Check the Queue has the correct size and count
    testAssert(q.size() == 64);
    testAssert(q.count() == 0);
    return OK;
}

TestCase(PriorityqueuePushPopDouble)
{
    Priorityqueue<double, 64> q;

    // Append a string
    q.push(2.11);
    testAssert(q.count() == 1);
    testAssert(q.size() == 64);

    // Remove the string
    double s = q.pop();
    testAssert(q.count() == 0);
    testAssert(q.size() == 64);
    testAssert(s=2.11);

    return OK;
}

TestCase(PriorityqueuePushPopInt)
{
    Priorityqueue<int, 64> q;

    // Append a number
    q.push(1);
    testAssert(q.count() == 1);
    testAssert(q.size() == 64);

    // Remove the number
    int n = q.pop();
    testAssert(q.count() == 0);
    testAssert(q.size() == 64);
    testAssert(n == 1);

    return OK;
}

TestCase(PriorityqueuePriority)
{
    Priorityqueue<int, 64> q;
    
    //Push the unsorted numbers
    q.push(5);
    q.push(3);
    q.push(7);
    q.push(2);
    q.push(10);

    // Pop the sorted numbers
    int t;
    t=q.pop();
    testAssert(t==2);
    testAssert(q.count()==4);
    
    t=q.pop();
    testAssert(t==3);
    testAssert(q.count()==3);
    
    t=q.pop();
    testAssert(t==5);
    testAssert(q.count()==2);
    
    t=q.pop();
    testAssert(t==7);
    testAssert(q.count()==1);
    
    t=q.pop();
    testAssert(t==10);
    testAssert(q.count()==0);
    

    // Queue is empty again
    testAssert(q.count() == 0);
    testAssert(q.size() == 64);

    return OK;
}


TestCase(PriorityqueueFull)
{
    Priorityqueue<int, 64> q;
    TestInt<int> ints(INT_MIN, INT_MAX);

    // Fill the queue
    for (Size i = 0; i < 64; i++)
    {
        q.push(ints.random());
        testAssert(q.count() == (i + 1));
        testAssert(q.size() == 64);
    }

    // Now the queue is full, so a push must fail
    testAssert(!q.push(ints.random()));

    // Empty the queue
    for (Size i = 0; i < 64; i++)
    {
        q.pop();

        testAssert(q.count() == (64 - i - 1));
        testAssert(q.size() == 64);
    }

    // Queue is empty again
    testAssert(q.count() == 0);
    testAssert(q.size() == 64);
    testAssert(q.empty());

    return OK;
}

TestCase(PriorityqueueClear)
{
    Priorityqueue<int, 64> q;
    TestInt<int> ints(INT_MIN, INT_MAX);

    // Fill the queue
    for (Size i = 0; i < 64; i++)
    {
        q.push(ints.random());
        testAssert(q.count() == (i + 1));
        testAssert(q.size() == 64);
    }

    // Clear it
    q.clear();
    testAssert(q.count() == 0);
    testAssert(q.size() == 64);

    return OK;
}

TestCase(PriorityqueueContains)
{
    Priorityqueue<int, 64> q;
    TestInt<int> ints(0, 1024);

    // Fill the queue
    for (Size i = 0; i < 64; i++)
    {
        q.push(ints.random());
        testAssert(q.count() == (i + 1));
        testAssert(q.size() == 64);
    }

    // Verify that all items exist
    for (Size i = 0; i < 64; i++)
        testAssert(q.contains(ints[i]));

    // Check that other integers do not exist
    testAssert(!q.contains(1025));
    testAssert(!q.contains(-1));

    // Clear the queue
    q.clear();
    testAssert(q.count() == 0);
    testAssert(q.size() == 64);

    // Verify that none of the items exist
    for (Size i = 0; i < 64; i++)
        testAssert(!q.contains(ints[i]));

    // Check that other integers also still do not exist
    testAssert(!q.contains(1025));
    testAssert(!q.contains(-1));

    return OK;
}
