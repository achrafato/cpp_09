#include "./RPN.hpp"


RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN &obj)
{
	st = obj.st;
}

RPN &RPN::operator=(const RPN &obj)
{
	if (this != &obj)
	{
		st = obj.st;
	}
	return *this;
}

int	conclude_operator(char c, char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

void	RPN::recursive_read(char *str)
{
	int n;
	string curr;
	char op[5] = {'*', '-', '+', '/'};

	if (*str == ' ')
		str++;
	if ((!(*str) && st.size() != 1))
		throw std::invalid_argument("Error");
	if (!(*str))
		return ;
	n = conclude_operator(*str, op);
	if (!isnumber(*str) && n == -1)
		throw std::invalid_argument("Error");
	if ((strlen(str) == 1) && st.size() >= 3)
		throw std::invalid_argument("Error");
	if (n != -1 && st.size() <= 1)
		throw std::invalid_argument("Error");
	if (*str)
	{
		if (n != -1 && st.size() >= 2)
		{
			double val1, val2;
			val1 = st.top();
			st.pop();
			val2 = st.top();
			st.pop();

			if (!n)
				st.push(val1 * val2);
			else if (n == 1)
				st.push(val2 - val1);
			else if (n == 2)
				st.push(val1 + val2);
			else if (n == 3)
			{
				if (!val1)
					throw std::invalid_argument("Error");
				st.push(val2 / val1);
			}
		}
		else
		{
			curr = str;
			curr = curr.substr(0,1);
			n = atoi(curr.c_str());
			st.push(n);
		}
		str++;
		if (*str && *str != ' ')
				throw std::invalid_argument("Error");
		recursive_read(str);
	}
}
