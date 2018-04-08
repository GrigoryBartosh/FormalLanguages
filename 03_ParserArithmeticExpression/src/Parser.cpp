#include "Parser.h"

using std::ifstream;

bool Parser::finished()
{
    return _position < (int)_str.size();
}

char Parser::next_symbol()
{
    if (finished()) return 0;
    return _str[_position];
}

char Parser::get_next_symbol()
{
    while (!finished() && next_symbol() == ' ') _position++;
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
        throw new ParserException(_position);
}

Tree* Parser::parse_3(Tree* b)
{
    Tree* a = NULL;
    char op1 = 0;
    while (is_operator(next_symbol()))
    {
        char op2 = next_symbol();

        if (is_priority_3(op2))
        {
            a = makeOperator(a, op1, b);
            op1 = get_next_symbol();
            b = parse_element();
        } else {
            break;
        }
    }

    return makeOperator(a, op1, b);
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
            if (is_priority_3(op2)) b = parse_3(b);
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
            else                    b = parse_3(b);
        }
    }

    return makeOperator(a, op1, b);
}

Tree* Parser::parse_block()
{
    if (get_next_symbol() != '(')
        throw new ParserException(_position);

    Tree* t = parse_1();

    if (get_next_symbol() != ')')
        throw new ParserException(_position);

    return t;
}

Parser::Parser(ifstream &is)
{
    char c;
    while (is >> c) _str.push_back(c);
    _str = "(" + _str + ")";
    _position = 0;
}

Tree* Parser::parse()
{
    return parse_block();
}
