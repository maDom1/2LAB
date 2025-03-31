#include "Queap.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace my_project;
using namespace std;

void testEnqueueDequeue() {
    Queap q;
    q.enqueue(10);
    q.enqueue(20);
    assert(q.size() == 2);
    assert(q[0] == 10);
    q.dequeue();
    assert(q.size() == 1);
    assert(q[0] == 20);
    cout << "testEnqueueDequeue passed.\n";
}

void testFindMin() {
    Queap q;
    q.enqueue(30);
    q.enqueue(10);
    q.enqueue(20);
    assert(q.findMin() == 10);
    cout << "testFindMin passed.\n";
}

void testDuplicateException() {
    Queap q;
    q.enqueue(5);
    bool caught = false;
    try {
        q.enqueue(5);
    } catch (const DuplicateValueException&) {
        caught = true;
    }
    assert(caught);
    cout << "testDuplicateException passed.\n";
}

void testOperators() {
    Queap a, b;
    a.enqueue(1); a.enqueue(2); a.enqueue(3);
    b.enqueue(1); b.enqueue(2); b.enqueue(3);

    assert(a == b);
    assert(!(a != b));
    assert(!(a < b));
    assert(!(a > b));
    assert(a <= b);
    assert(a >= b);

    Queap c;
    c.enqueue(4);
    c += a;
    assert(c.size() == 4);

    c -= b;
    assert(c.size() == 1);
    assert(c[0] == 4);

    !c;
    assert(c.isEmpty());
    cout << "testOperators passed.\n";
}

void testCopyAndAssign() {
    Queap q1;
    q1.enqueue(100);
    q1.enqueue(200);

    Queap q2 = q1;
    assert(q2.size() == 2);
    assert(q2[1] == 200);

    Queap q3;
    q3 = q1;
    assert(q3.size() == 2);
    assert(q3[0] == 100);
    cout << "testCopyAndAssign passed.\n";
}


int main() {
    testEnqueueDequeue();
    testFindMin();
    testDuplicateException();
    testOperators();
    testCopyAndAssign();
    cout << "All tests passed successfully.\n";
    return 0;
}