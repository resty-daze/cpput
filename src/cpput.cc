#include "cpput.hpp"
#include <cstdio>
using namespace cpput;

// Release all test
TestRegistry::~TestRegistry() {
    TestGroupNode* p = head_;
    while (p != NULL) {
        TestGroupNode* now = p;
        p = p->nextGroup;
        delete now;
    }
}

TestRegistry& TestRegistry::inst() {
    static TestRegistry t;
    return t;
}

void TestRegistry::addTest(const char* group, const char* name, Test* test) {
    TestGroupNode* p = head_;
    while (p != NULL) {
        if (p->groupName == group) break;
        p = p->nextGroup;
    }
    if (p == NULL) {
        p = new TestGroupNode;
        p->groupName = group;
        p->nextGroup = head_;
        p->test = NULL;
        head_ = p;
    }
    test->next_ = p->test;
    test->name_ = name;
    p->test = test;
}

void TestRegistry::runAllTests() {
    TestGroupNode* p = head_;
    while (p != NULL) {
        TestResult::inst().setGroup(p->groupName.c_str());
        Test* t = p->test;
        while (t != NULL) {
            fail = false;
            t->set();
            t->run();
            t->clear();
            if (!fail) TestResult::inst().addPassTest();
            t = t->next_;
        }
        p = p->nextGroup;
    }
    TestResult::inst().print();
}

TestResult::TestResult()
    : numPassTest(0), numPassAssert(0), numFailure(0) {
}

TestResult::~TestResult() {
}

TestResult& TestResult::inst() {
    static TestResult t;
    return t;
}

void TestResult::addFailure(const Failure& f) {
    fprintf(stderr, "[FAIL] %s.%s\n", groupName.c_str(), f.toString().c_str());
    ++numFailure;
    TestRegistry::inst().notifyFail();
}

void TestResult::print() {
    fprintf(stderr, "\nTotal: \n  PASS: %d tests, %d asserts\n  FAIL: %d tests\n", numPassTest, numPassAssert, numFailure);
    if (numFailure == 0) {
        fprintf(stderr, "All tests passed.\n");
    } else {
        fprintf(stderr, "Some tests failed.\n");
    }
}

void cpput::run() { TestRegistry::inst().runAllTests(); }

