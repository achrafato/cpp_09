#include "./RPN.hpp"

int	main(int argc, char *argv[])
{
	try
	{
		RPN	rpn;
		if (argc != 2)
		{
			std::cerr << "Invalid Args" << endl;
			return 1;
		}
		rpn.recursive_read(argv[1]);
		cout << rpn.st.top() << endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << endl;
	}

	return 0;
}
