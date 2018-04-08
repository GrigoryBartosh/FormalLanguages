#pragma once

#include <iostream>
#include <sstream>
#include <cstring>

class Tree
{
public:
    Tree();

    virtual std::string to_string() const = 0;
};

class Number : protected Tree
{
private:
    double _num;

public:
    Number(double num);

    std::string to_string() const override;
};

class Operator : protected Tree
{
private:
    char _op;
    Tree *l, *r;

public:
    Operator(Tree* a, char op, Tree* b);

    std::string to_string() const override;
};
