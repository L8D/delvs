#include "delvs.h"
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	for (int i = 1 ; i < argc ; i++)
	{
		try
		{
			delvs::parser p;
			ifstream is;
			is.open(argv[i], ios::binary);
		
			while (!is.eof())
			{
				char buf[4096];
				is.read(buf, 4096);
				if (is.gcount() > 0)
					delvs::lexer(buf, is.gcount(), p);
			}
			delvs::cout_visitor visitor;
			p.program()->visit(visitor);
		}
		catch (const exception &e)
		{
			cerr << "Error running " << argv[i] << ": " << e.what() << endl;
		}
	}
}
