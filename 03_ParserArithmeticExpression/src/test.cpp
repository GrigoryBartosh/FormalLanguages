#include "test.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::remove;
using std::cout;

static string TMP_FILE = "tmp.txt";

static size_t cnt = 0;
static size_t successful_cnt = 0;

static void write(string s)
{
    ofstream os(TMP_FILE);
    os << s;
    os.close();
}

static string get_ans()
{
    ifstream is(TMP_FILE);
    Parser p(is);
    is.close();   
    remove(TMP_FILE.c_str());

    Tree* t;
    try
    {
        t = p.parse();
        return t->to_string();
    } catch (const ParserException &e) {
        return "error";
    }
}

static void check_ans(string a, string b)
{
    cnt++;
    if (a == b)
        successful_cnt++;
}

static void test1()
{
    write("-3");
    check_ans(get_ans(), "error");
}

static void test2()
{
    write("0 + 13 * 42 - 7 / 0");
    check_ans(get_ans(), "((0+(13*42))-(7/0))");
}

static void test3()
{
    write("(0 + 13) * ((42 - 7) / 0)");
    check_ans(get_ans(), "((0+13)*((42-7)/0))");
}

static void test4()
{
    write("1 - 2 - 3 - (5 - 6)");
    check_ans(get_ans(), "(((1-2)-3)-(5-6))");
}

static void test5()
{
    write("13");
    check_ans(get_ans(), "13");
}

static void test6()
{
    write("(((((13)))))");
    check_ans(get_ans(), "13");
}

static void test7()
{
    write("42 ^ 24 - 156 * 123");
    check_ans(get_ans(), "((42^24)-(156*123))");
}

static void test8()
{
    write("(42 ^ (24 - 156) * 123)");
    check_ans(get_ans(), "((42^(24-156))*123)");
}

static void test9()
{
    write("1+-4");
    check_ans(get_ans(), "error");
}

static void test10()
{
    write("(0))");
    check_ans(get_ans(), "error");
}

void test::run()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();

    cout << successful_cnt << " successful of " << cnt << "\n";
}