#include "Tree.h"

using std::ofstream;
using std::string;

Tree::Tree()
{}

Number::Number(double num)
: _num(num)
{}

string Number::to_string() const
{
    std::ostringstream strs;
    strs << _num;
    return strs.str();
}

Operator::Operator(Tree* a, char op, Tree* b)
: _op(op)
{
    l = a;
    r = b;
}

string Operator::to_string() const
{
    string s;
    s = "(" + l->to_string() + _op + r->to_string() + ")";
    return s;
}
