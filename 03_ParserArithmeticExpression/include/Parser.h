#pragma once

#include <iostream>
#include <fstream>
#include "Tree.h"

struct ParserException
{
private:
    size_t _pos;
    std::string _str;

public:
    ParserException(size_t pos, std::string str)
    : _pos(pos), _str(str)
    { }

    size_t get_pos() const
    {
        return _pos;
    }

    std::string get_str() const
    {
        return _str;
    }
};

class Parser
{
private:
    std::string _str;
    int _position;

    void do_throw();

    bool finished();
    char next_symbol();
    char get_next_symbol();
    bool is_num(char c);
    bool is_operator(char c);
    bool is_priority_3(char c);
    bool is_priority_2(char c);
    bool is_priority_1(char c);

    Tree* makeOperator(Tree* a, char c, Tree* b);

    Tree* parse_number();
    Tree* parse_element();
    Tree* parse_3();
    Tree* parse_2(Tree* b);
    Tree* parse_1();
    Tree* parse_block();

public:
    Parser(std::ifstream &is);

    Tree* parse();
};
