#include <iostream>
#include <cstdlib>
#include "Parser.h"
#include "Tree.h"

using namespace std;

static void check_input(int argc)
{
    if (argc != 2)
    {
        cerr << "Incorrect input format\n";
        exit(1);
    }
}

static void check_file(ifstream& is)
{
    if (!is.is_open())
    {
        cerr << "Could not open file\n";
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    check_input(argc);
    ifstream is(argv[1]);
    check_file(is);
    Parser p(is);

    Tree *t = NULL;
    try {
        t = p.parse();
    } catch (const ParserException &e) {
        cerr << "Error in position: " << e.get_pos() << "\n";
    }
    is.close();

    cout << t->to_string() << "\n";

    return 0;
}
