#include "PmergeMe.hpp"

int	main(int argc, char *argv[])
{
	if (argc <= 2)
	{
		std::cerr << "Invalid Args" << std::endl;
		return 1;
	}
	try
	{
		PmergeMe<vector<int> > vc(argc);
		PmergeMe<deque<int> > deq(argc);

		PmergeMe<deque<int> > de;

		de = deq;
		vc.parsing_input(argv, argc);

		vc.start_sorting(argv, "vector", 1);
		deq.start_sorting(argv, "deque", 0);
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
