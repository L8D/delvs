#include "brainfuck.h"
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
			brainfuck::parser p;
			ifstream is;
			//is.exceptions(ifstream::failbit | ifstream::badbit);
			is.open(argv[i], ios::binary);
		
			while (!is.eof())
			{
				char buf[4096];
				is.read(buf, 4096);
				if (is.gcount() > 0)
					brainfuck::lexer(buf, is.gcount(), p);
			}
			struct input { char operator()() { return getchar(); } };
			struct output { void operator()(char c) { putchar(c); } };
			brainfuck::unsafe_interpreter<input,output,char> visitor;
			p.program()->visit(visitor);
		}
		catch (const exception &e)
		{
			cerr << "Error running " << argv[i] << ": " << e.what() << endl;
		}
	}
}
