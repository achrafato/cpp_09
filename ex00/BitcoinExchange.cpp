#include "./BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(string file_name):file(file_name), file_1("data.csv")
{
	this->file_name = file_name;
	if (!file.is_open() || !file_1.is_open())
	{
		std::cerr << "Error: could not open file."<< std::endl;
		exit(1);
	}
}

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange()
{
	file.close();
	file_1.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
	db = obj.db;
	file_name = obj.file_name;

	if (obj.file.is_open())
	{
		file.open(obj.file_name);
		if (!file.is_open())
			std::cerr << "Error: could not open file."<< std::endl;
	}

	if (obj.file_1.is_open())
	{
		file_1.open(obj.file_name);
		if (!file_1.is_open())
			std::cerr << "Error: could not open file." << std::endl;
	}
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	if (this != &obj)
	{
		db = obj.db;
		file_name = obj.file_name;
		if (file.is_open())
			file.close();
		if (file_1.is_open())
			file_1.close();

		if (obj.file.is_open())
		{
			file.open(obj.file_name);
			if (!file.is_open())
				std::cerr << "Error: could not open file."<< std::endl;
		}

		if (obj.file_1.is_open())
		{
			file_1.open(obj.file_name);
			if (!file_1.is_open())
				std::cerr << "Error: could not open file." << std::endl;
		}
	}
	return *this;
}

set<input> &BitcoinExchange::get_data(void)
{
	return this->db;
}

int d_digit(string n)
{
	int i = 0;
	while (n[i])
	{
		if (!isdigit(n[i++]))
			return 0;
	}
	return 1;
}

void	reset_data(input *dt)
{
	dt->date = "";
	dt->res = "";
}

int	BitcoinExchange::check_date(string date, input *dt)
{
	float	year;
	float	month;
	float	day;
	char *end = NULL;
	string p1;
	string p2;
	string p3;
	string hyphen_1;
	string hyphen_2;

	int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (date.length() != 11)
		return (0);
	hyphen_1 = date.substr(4, 1);
	hyphen_2 = date.substr(7, 1);
	if (hyphen_2 != "-" || hyphen_1 != "-")
		return 0;

	p1 = date.substr(0, 4);
	p2 = date.substr(5, 2);
	p3 = date.substr(8, 2);

	if (p1.length() != 4 || p2.length() != 2 || p3.length() != 2)
		return (0);
	if (!d_digit(p1) || !d_digit(p2) || !d_digit(p3))
		return (0);
	year = strtod(p1.c_str(), &end);
	if (*end)
		return 0;
	month = strtod(p2.c_str(), &end);
	if (*end)
		return 0;
	day = strtod(p3.c_str(), &end);
	if (*end)
		return 0;
	if (year < 2009 || (month < 1 || month > 12) || (day < 1 || day > 31))
		return 0;
	if (!((int)year % 4) && (month == 2) && day > 29)
		return 0;
	else if (((int)year % 4) && months[(int)month - 1] < day)
		return 0;
	dt->year = year;
	dt->month = month;
	dt->day = day;
	return 1;
}

int	parse_db_line(string line, input *db)
{
	float	year;
	float	month;
	float	day;
	char *end = NULL;
	size_t	pos;
	string part1;
	string part2;
	string p1;
	string p2;
	string p3;
	string hyphen_1;
	string hyphen_2;

	int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	pos =  line.find_first_of(',');
	part1 = line.substr(0, pos);
	part2 = line.substr(pos + 1, line.length());
	if (part1.length() != 10)
		return 0;
	hyphen_1 = part1.substr(4, 1);
	hyphen_2 = part1.substr(7, 1);
	if (hyphen_2 != "-" || hyphen_1 != "-")
		return 0;

	p1 = part1.substr(0, 4);
	p2 = part1.substr(5, 2);
	p3 = part1.substr(8, 2);

	if (p1.length() != 4 || p2.length() != 2 || p3.length() != 2)
		return (0);
	if (!d_digit(p1) || !d_digit(p2) || !d_digit(p3))
		return (0);
	year = strtod(p1.c_str(), &end);
	if (*end)
		return 0;
	month = strtod(p2.c_str(), &end);
	if (*end)
		return 0;
	day = strtod(p3.c_str(), &end);
	if (*end)
		return 0;
	if (year < 2009 || (month < 1 || month > 12) || (day < 1 || day > 31))
		return 0;
	if (!((int)year % 4) && (month == 2) && day > 29)
		return 0;
	else if (((int)year % 4) && months[(int)month - 1] < day)
		return 0;
	db->year = year;
	db->month = month;
	db->day = day;
	db->val = strtod(part2.c_str(), NULL);
	return 1;
}

int	check_value(string value, input *dt)
{
	char	*end = NULL;
	float	val;

	// remove space from begining
	value = value.substr(1, value.length());
	if (!value.length())
		return 0;
	if (isspace(value[0]))
		return 0;
	val = strtod(value.c_str(), &end);
	if (*end)
		return 0;
	if (val > 1000)
	{
		dt->res = "Error: too large a number.";
		return 0;
	}
	if (val < 0)
	{
		dt->res = "Error: not a positive number.";
		return 0;
	}
	dt->val = val;
	return 1;
}

void	BitcoinExchange::get_price_at_time(input &dt)
{
	set<input>::iterator it;

	it = db.lower_bound(dt);

	if (it != db.end() && *it == dt)
	{
		cout << dt.date << " => " << dt.val << " = " << it->val * dt.val << endl;
	}
	else if (it == db.begin())
		cout << dt.date << " => " << dt.val << " = Invalid" << endl;
	else if (it == db.end())
	{
		it--;
		cout << dt.date << " => " << dt.val << " = " << it->val * dt.val << endl;
	}
	else
	{
		it--;
		cout << dt.date << " => " << dt.val << " = " << it->val * dt.val << endl;
	}
}

void	BitcoinExchange::fill_input()
{
	int		i;
	input	dt;
	string	line = "";
	size_t	pos;
	string value;

	i = 0;
	if (getline(file, line))
	{
		if (line != "date | value")
		{
			cout << "Error: Header not found" << endl;
			return ;
		}
	}
	while (getline(file, line))
	{
		pos = line.find_first_of('|');
		if (pos != std::string::npos)
		{
			dt.date = line.substr(0, pos);
			if (dt.date.empty() || !check_date(dt.date, &dt))
				dt.res = "Error: bad input => " + line;
			value = line.substr(pos + 1, line.length() - pos);
			if (value.empty() || value.find_first_of(' ') != 0 || !check_value(value, &dt))
			{
				if (dt.res.empty())
					dt.res = "Error: bad input => " + line;
			}
		}
		else
			dt.res = "Error: bad input => " + line;
		if (!dt.res.empty())
			cout << dt.res << endl;
		else
			get_price_at_time(dt);
		reset_data(&dt);
		i++;
	}
	if (!i)
	{
		cout << "Error: Empty Data" << endl;
		return ;
	}
}

int	BitcoinExchange::file_data()
{
	string	line;
	input	db_dt;
	int 	i = 0;

	while (getline(file_1, line))
	{
		if (!i)
		{
			if (line != "date,exchange_rate")
				return 0;
			i = 1;
			continue;
		}
		if (line.empty())
			continue;
		if (!parse_db_line(line, &db_dt))
			return 0;
		db.insert(db_dt);
	}
	return 1;
}

bool	operator==(const input& data, const input& db)
{
	return data.year == db.year && data.month == db.month && data.day == db.day;
}

bool	operator<(const input& db, const input& data)
{
	if (db.year != data.year)
		return db.year < data.year;
	if (db.month != data.month)
		return db.month < data.month;
	return db.day < data.day;
}

ostream &operator << (ostream &output, const input &f)
{
	output << f.year << "-" << f.month << "-" << f.day << std::endl;
	return output;
}
