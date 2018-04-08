#include "Parser.h"

using std::string;
using std::ifstream;

void Parser::do_throw()
{
    string s;

    _str[0] = '"';
    _str[_str.size()-1] = '"';
    s = _str + '\n';

    for (int i = 0; i < _position; i++) s += ' ';
    s += "^\n";

    throw ParserException(_position-1, s);
}

bool Parser::finished()
{
    return !(_position < (int)_str.size());
}

char Parser::next_symbol()
{
    if (finished()) return 0;
    return _str[_position];
}

char Parser::get_next_symbol()
{
    char ans = next_symbol();
    _position++;

    return ans;
}

bool Parser::is_num(char c)
{
    return ('0' <= c) && (c <= '9');
}

bool Parser::is_operator(char c)
{
    return  c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '^';
}

bool Parser::is_priority_3(char c)
{
    return c == '^';
}

bool Parser::is_priority_2(char c)
{
    return c == '*' || c == '/';
}

bool Parser::is_priority_1(char c)
{
    return c == '+' || c == '-';
}

Tree* Parser::makeOperator(Tree* a, char c, Tree* b)
{
    if (a == NULL) return b;
    return (Tree*)(new Operator(a, c, b));
}

Tree* Parser::parse_number()
{
    int x = 0;
    while (is_num(next_symbol()))
        x = 10 * x + get_next_symbol() - '0';
    return (Tree*)(new Number(x));
}

Tree* Parser::parse_element()
{
    if (next_symbol() == '(')
    {
        return parse_block();
    }
    else if (is_num(next_symbol()))
    {
        return parse_number();
    }
    else
    {
        do_throw();
        return NULL;
    }
}

Tree* Parser::parse_3()
{
    char op1 = get_next_symbol();
    Tree* a = parse_element();
    if (is_priority_3(next_symbol()))
    {
        return makeOperator(a, op1, parse_3());
    } else {
        return a;
    }
}

Tree* Parser::parse_2(Tree* b)
{
    Tree* a = NULL;
    char op1 = 0;
    while (is_operator(next_symbol()))
    {
        char op2 = next_symbol();

        if (is_priority_2(op2))
        {
            a = makeOperator(a, op1, b);
            op1 = get_next_symbol();
            b = parse_element();
        } else {
            if (is_priority_3(op2)) b = makeOperator(b, op2, parse_3());
            else                    break;
        }
    }

    return makeOperator(a, op1, b);
}

Tree* Parser::parse_1()
{
    Tree* a = NULL;
    char op1 = 0;
    Tree* b = parse_element();
    while (is_operator(next_symbol()))
    {
        char op2 = next_symbol();

        if (is_priority_1(op2))
        {
            a = makeOperator(a, op1, b);
            op1 = get_next_symbol();
            b = parse_element();
        } else {
            if (is_priority_2(op2)) b = parse_2(b);
            else                    b = makeOperator(b, op2, parse_3());
        }
    }

    return makeOperator(a, op1, b);
}

Tree* Parser::parse_block()
{
    if (get_next_symbol() != '(') do_throw();

    Tree* t = parse_1();

    if (get_next_symbol() != ')') do_throw();

    return t;
}

Parser::Parser(ifstream &is)
{
    _str.clear();
    char c;
    while (is >> c) _str.push_back(c);
    _str = "(" + _str + ")";
    _position = 0;
}

Tree* Parser::parse()
{
    Tree* t = parse_block();

    if (!finished()) do_throw();

    return t;
}
