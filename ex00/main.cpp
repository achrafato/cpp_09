#include "./BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	int ret;
	if (argc == 2)
	{
		BitcoinExchange btc(argv[1]);

		ret = btc.file_data();
		if (!ret || btc.get_data().empty())
			cout << "Empty Or Invalid Data" << endl;
		else
			btc.fill_input();
		return 0;
	}
	cout << "Error: could not open file." << endl;
	return 1;
}
