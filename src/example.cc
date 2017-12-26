#include "cpput.hpp"

TEST(G1, T1) {
    EQ_(1, 1);
    OK_(1 == 1);
}

TEST(G1, T2) {
    NO_(2 == 1);
    OK_(2 == 1); // this will fail
}

TEST(G2, T1) {
    EQ_(1, 2) << " Add More Info there!";
}

TEST(G3, BINARY_OP) {
    EQ_(1, 1);
    NE_(1, 2);
    LE_(1, 2);
    LT_(1, 2);
    GE_(2, 1);
    GT_(2, 1);
    FAIL_ << "fail here";
}

// an other example
class MyTest : public cpput::Test {
public:
    int x;
    void set() {
        x = 1;
    }
    void clear() {
    }
};

TEST_F(MyTest, CheckX) {
    EQ_(x, 1);
    EQ_(x, 2);// << " You get this for x != 2";
}

int main() {
    cpput::run();
    return 0;
}
