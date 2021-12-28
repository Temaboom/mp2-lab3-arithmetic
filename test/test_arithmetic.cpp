// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <string>
#include "arithmetic.h"

TEST(Arithmetic, polish_correct_string_1) {
    string S;
    S = "2*4";
    Arithmetic Arr(S);
    Arr.Polish();
    string a = "24*";

    EXPECT_EQ(a, Arr.print_polish_1());
}

TEST(Arithmetic, polish_correct_string_2) {
    string S;
    S = "((4/2)+(5*2))";
    Arithmetic Arr(S);
    Arr.Polish();
    string a = "42/52*+";

    EXPECT_EQ(a, Arr.print_polish_1());
}

class TestStr_1 : public ::testing::TestWithParam<string>
{
protected:
    string S;

public:
    TestStr_1() : S(GetParam()) {}
    ~TestStr_1() {}
};

TEST_P(TestStr_1, check_errors_1)
{
    Arithmetic Arr(S);

    EXPECT_EQ(1, Arr.check());
}

string arr_1[] = { "2+5","10.8+2.1","8+x","-1/(8-2)","a[i]*(10-16)","(-1)*16" };

INSTANTIATE_TEST_CASE_P(Instantiation, TestStr_1, ::testing::ValuesIn(arr_1));

class TestStr_2 : public ::testing::TestWithParam<string>
{
protected:
    string S;

public:
    TestStr_2() : S(GetParam()) {}
    ~TestStr_2() {}
};

TEST_P(TestStr_2, check_errors_2)
{
    Arithmetic Arr(S);

    ASSERT_ANY_THROW(Arr.check());
}

string arr_2[] = { ")(", "(*","(+-)","(+5)", ")3(", ")/"};

INSTANTIATE_TEST_CASE_P(Instantiation1, TestStr_2, ::testing::ValuesIn(arr_2));

struct Test_str
{
    string s;
    bool correct;
    double res;

    Test_str(string mys = "", bool f = true, double v = 0.0)
    {
        s = mys;
        correct = f;
        res = v;
    }
};

class TestStr2 : public ::testing::TestWithParam<Test_str>
{
protected:
    Test_str testcase;
public:
    TestStr2() : testcase(GetParam()) {}
    ~TestStr2() {}
};

TEST_P(TestStr2, expression_validation)
{
    Arithmetic Res(GetParam().s);

    EXPECT_EQ(GetParam().correct, Res.check());
}

Test_str arr_3[] = { /*Test_str(")-2+6*6/9",false),*/Test_str("4+2*(8.8-5.8)", true, 10) }; // второй - верный, в первом выводит фразу - "Нельзя перед открытием поставить закрывающуюся скобку"

INSTANTIATE_TEST_CASE_P(Instantiation2, TestStr2, ::testing::ValuesIn(arr_3));