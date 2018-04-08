#pragma once

#include <iostream>
#include <fstream>
#include "Tree.h"

struct ParserException
{
private:
    size_t _pos;

public:
    ParserException(size_t pos)
    : _pos(pos)
    { }

    size_t get_pos()
    {
        return _pos;
    }
};

class Parser
{
private:
    std::string _str;
    int _position;

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
    Tree* parse_3(Tree* b);
    Tree* parse_2(Tree* b);
    Tree* parse_1();
    Tree* parse_block();

public:
    Parser(std::ifstream &is);

    Tree* parse();
};
