#include <cassert>
#include <cstdlib>
#include <vector>
#include <stack>
#include <iostream>

namespace brainfuck
{
	namespace ast
	{
		struct increment_ptr;
		struct decrement_ptr;
		struct increment;
		struct decrement;
		struct output;
		struct input;
		struct branch;
		struct program;

		struct node_visitor
		{
			virtual void visit(increment_ptr*)=0;
			virtual void visit(decrement_ptr*)=0;
			virtual void visit(increment*)=0;
			virtual void visit(decrement*)=0;
			virtual void visit(output*)=0;
			virtual void visit(input*)=0;
			virtual bool visit(branch*)=0;
			virtual void post_visit(branch*)=0;
			virtual void visit(program*)=0;
			virtual void post_visit(program*)=0;
		};

		class node
		{
			public:
				virtual ~node() { }
				virtual void visit(node_visitor &visitor)=0;
		};

		class container_node: public node
		{
			protected:
					std::vector<node*> _nodes;
					container_node() { } // no public constructor
			public:
					~container_node()
					{
						for (auto i = _nodes.begin() ; i != _nodes.end() ; i++)
							delete *i;
					}
					void push_back(node *n)
					{
						_nodes.push_back(n);
					}
		};

		struct increment_ptr: public node 
		{ 
			void visit(node_visitor &visitor) { visitor.visit(this); }
		};

		struct decrement_ptr: public node
		{ 
			void visit(node_visitor &visitor) { visitor.visit(this); }
		};

		struct increment: public node 
		{ 
			void visit(node_visitor &visitor) { visitor.visit(this); }
		};

		struct decrement: public node 
		{
			void visit(node_visitor &visitor) { visitor.visit(this); }
		};

		struct output: public node 
		{
			void visit(node_visitor &visitor) { visitor.visit(this); }
		};

		struct input: public node 
		{
			void visit(node_visitor &visitor) { visitor.visit(this); }
		};

		struct branch: public container_node
		{
			branch() { }
			void visit_nodes(node_visitor &visitor)
			{
				for (auto i = _nodes.begin() ; i != _nodes.end() ; i++)
					(*i)->visit(visitor);
			}
			virtual void visit(node_visitor &visitor)
			{
				if (visitor.visit(this))
				{
					visit_nodes(visitor);
					visitor.post_visit(this);
				}
			}
		};

		struct program: public container_node
		{
			virtual void visit(node_visitor &visitor)
			{
				visitor.visit(this);
				for (auto i = _nodes.begin() ; i != _nodes.end() ; i++)
					(*i)->visit(visitor);
				visitor.post_visit(this);
			}
		};
	};

	template <typename Parser> void lexer(const char *data, size_t len, Parser &parser)
	{
		for (const char *p = data ; p != data + len ; p++)
			switch (*p)
			{
				case '>':
					parser.increment_ptr();
					break;

				case '<':
					parser.decrement_ptr();
					break;

				case '+':
					parser.increment();
					break;

				case '-':
					parser.decrement();
					break;

				case '.':
					parser.output();
					break;

				case ',':
					parser.input();
					break;

				case '[':
					parser.branch_begin();
					break;

				case ']':
					parser.branch_end();
					break;

				default:
					// everything else is comments
					break;
			}
	};

	template <typename Input, typename Output, typename Cell> class unsafe_interpreter: public ast::node_visitor
	{
			const static int ARRAY_SIZE = 32768;
			Cell _array[ARRAY_SIZE];
			Cell *_ptr;
			Input _input;
			Output _output;
			std::stack<ast::branch*> _stack;
		public:
			virtual void visit(ast::increment_ptr*)
			{
				++_ptr;
			}
			virtual void visit(ast::decrement_ptr*)
			{
				--_ptr;
			}
			virtual void visit(ast::increment*)
			{
				++*_ptr;
			}
			virtual void visit(ast::decrement*)
			{
				--*_ptr;
			}
			virtual void visit(ast::output*)
			{
				_output(*_ptr);
			}
			virtual void visit(ast::input*)
			{
				*_ptr = _input();
			}
			virtual bool visit(ast::branch *branch)
			{
				return *_ptr != 0;
			}
			virtual void post_visit(ast::branch *branch)
			{
				while (*_ptr)
				{
					branch->visit_nodes(*this);
				}
			}
			virtual void visit(ast::program*)
			{
				assert(_stack.empty());
				std::fill(_array, _array + ARRAY_SIZE, 0);
				_ptr = _array;
			}
			virtual void post_visit(ast::program*)
			{
			}
	};

	class cout_visitor: public ast::node_visitor
	{
			
			virtual void visit(ast::increment_ptr*)
			{
				std::cout << "++ptr;" << std::endl;
			}
			virtual void visit(ast::decrement_ptr*)
			{
				std::cout << "--ptr;" << std::endl;
			}
			virtual void visit(ast::increment*)
			{
				std::cout << "++*ptr;" << std::endl;
			}
			virtual void visit(ast::decrement*)
			{
				std::cout << "--*ptr;" << std::endl;
			}
			virtual void visit(ast::output*)
			{
				std::cout << "putchar(*ptr);" << std::endl;
			}
			virtual void visit(ast::input*)
			{
				std::cout << "*ptr = getchar();" << std::endl;
			}
			virtual bool visit(ast::branch*)
			{
				std::cout << "while (*ptr){" << std::endl;
				return true;
			}
			virtual void post_visit(ast::branch*)
			{
				std::cout << "}" << std::endl;
			}
			virtual void visit(ast::program*)
			{
				std::cout << "#include <stdio.h>" << std::endl << "void main(int argc, char *argv[]){" << std::endl << "char array[32768];char *ptr=array;" << std::endl;
			}
			virtual void post_visit(ast::program*)
			{
				std::cout << "fflush(stdout);" << std::endl << "}" << std::endl;
			}
	};

	class parser
	{
			ast::program *_program;
			std::stack<ast::container_node*> _scope;
		public:
			parser()
			{
				_program = new ast::program();
				_scope.push(_program);
			}
			ast::program *program() const { return _program; }

			void increment_ptr()
			{
				_scope.top()->push_back(new ast::increment_ptr());
			}
			void decrement_ptr()
			{
				_scope.top()->push_back(new ast::decrement_ptr());
			}
			void increment()
			{
				_scope.top()->push_back(new ast::increment());
			}
			void decrement()
			{
				_scope.top()->push_back(new ast::decrement());
			}
			void output()
			{
				_scope.top()->push_back(new ast::output());
			}
			void input()
			{
				_scope.top()->push_back(new ast::input());
			}
			void branch_begin()
			{
				ast::branch *new_branch = new ast::branch();
				_scope.top()->push_back(new_branch);
				_scope.push(new_branch);
			}
			void branch_end()
			{
				_scope.pop();
			}
	};
};
