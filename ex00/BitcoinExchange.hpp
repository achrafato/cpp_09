#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

using std::ifstream;
using std::string;
using std::set;
using std::set;
using std::cout;
using std::endl;
using std::stringstream;
using std::ostream;

struct input
{
	string	date;
	string	res;

	size_t	year;
	size_t	month;
	size_t	day;
	
	float	val;
};

class  BitcoinExchange
{
	private :
		set<input>	db;
		ifstream		file;
		ifstream		file_1;
		string			file_name;
	public :
		BitcoinExchange();
		BitcoinExchange(string file_name);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &obj);
		BitcoinExchange &operator=(const BitcoinExchange &obj);

		int		check_date(string date, input *dt);
		void	fill_input();
		int		file_data();
		void	get_price_at_time(input &dt);
		set<input>	&get_data(void);

};

bool	operator==(const input& data, const input& db);
bool	operator<(const input& data, const input& db);

ostream &operator << (ostream &output, const input &f);

#endif
