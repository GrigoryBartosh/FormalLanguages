#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Parser.h"
#include "Tree.h"

using namespace std;

static void read(ifstream& is)
{
    is.open("in.txt");
    if (!is.is_open())
    {
        cerr << "Could not open file \n";
        exit(1);
    }
}

int main()
{
    ifstream is;
    read(is);
    Parser p(is);

    Tree *t = NULL;
    try {
        t = p.parse();
    } catch (ParserException e) {
        cerr << "Error in position: " << e.get_pos();
    }
    is.close();

    cout << t->to_string();

    return 0;
}
