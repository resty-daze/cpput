#ifndef CPPUT_HPP_
#define CPPUT_HPP_

#include <string>
#include <ostream>
#include <sstream>

namespace cpput {
    class Failure {
    public:
        Failure(const char* fileName, int lineNumber, const char* test) {
            buf << test << " [" << fileName << ':' << lineNumber << "] " ; 
        }

        Failure(const Failure& b) { buf << b.buf.str(); }

        template <typename T>
        Failure& operator <<(const T& arg) { buf << arg; return *this; }
        
        std::string toString() const { return buf.str(); }
    private:
        std::ostringstream buf;
    };

    class TestRegistry;
    class Test {
    public:
        Test() : next_(NULL) {}
        virtual void set() {}
        virtual void run() {}
        virtual void clear() {}
        Test* next() const { return next_; }
        const char* name() const { return name_.c_str(); }
    private:
        std::string name_;
        Test* next_;
        friend class TestRegistry;
    };
    
    class TestRegistry {        
    public:
        ~TestRegistry();
        static TestRegistry& inst();
        void addTest(const char* group, const char* name, Test* test);
        void runAllTests();
        void notifyFail() { fail = true; }
    private:
        struct TestGroupNode {
            std::string groupName;
            TestGroupNode * nextGroup;
            Test* test;
        };
        TestGroupNode* head_;

        bool fail;
        
        TestRegistry() : head_(NULL) {}
        TestRegistry(const TestRegistry&);
        void operator=(const TestRegistry&);
    };

    class TestResult {
    public:
        ~TestResult();
        static TestResult& inst();
        void addFailure(const Failure& failure);
        void addPassTest() { ++numPassTest; }
        void addPassAssert() { ++numPassAssert; }
        void print();
        void setGroup(const char* group) { groupName = group; }
        void operator=(const Failure& f) { addFailure(f); }
    private:
        int numPassTest;
        int numPassAssert;
        int numFailure;
        std::string groupName;
        TestResult();
        TestResult(const TestResult&);
        void operator=(const TestResult&);
    };

    void run();
}

#define CPPUT_TEST_BASE(name, group, base)                              \
    class group##_##name##Test : public base {                          \
    public:                                                             \
    void run();                                                         \
    group##_##name##Test() {                                            \
        cpput::TestRegistry::inst().addTest(#group, #name, this); }     \
    } group##_##name##Test##Instance;                                   \
    void group##_##name##Test::run()

#define TEST(group, name) CPPUT_TEST_BASE(name, group, cpput::Test)
#define TEST_F(group, name) CPPUT_TEST_BASE(name, group, group)
#define CPPUT_SC cpput::TestResult::inst().addPassAssert(); else return cpput::TestResult::inst() = cpput::Failure(__FILE__, __LINE__, name())
#define OK_(exp) if (exp)  CPPUT_SC << "Should be True: " << #exp
#define NO_(exp) if (!(exp)) CPPUT_SC << "Should be False: " << #exp
#define EQ_(exp1, exp2) if ((exp1)==(exp2)) CPPUT_SC << "Should be Equal: " << #exp1 <<'(' <<(exp1) <<"), " << #exp2 << '(' << (exp2) <<") "

#endif