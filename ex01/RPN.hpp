#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>

#include <stack>
using std::string;
using std::stack;
using std::cout;
using std::endl;

class RPN
{
	public :
		stack<double> st;
		RPN();
		~RPN();
		RPN(const RPN &obj);
		RPN &operator=(const RPN &obj);
		void	recursive_read(char *str);
};

#endif
