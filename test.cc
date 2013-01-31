#include "brainfuck.h"
#include <cstring>
#include <cstdio>

int main(int argc, char *argv[])
{
	const char *code = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	brainfuck::parser p;
	brainfuck::lexer(code, strlen(code), p);
	//brainfuck::cout_visitor visitor;
	struct input { int operator()() { return getchar(); } };
	struct output { int operator()(int c) { putchar(c); } };
	brainfuck::unsafe_interpreter<input,output,int> visitor;
	p.program()->visit(visitor);
}
