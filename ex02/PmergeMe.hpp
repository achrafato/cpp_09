#ifndef DRR_HPP
#define DRR_HPP

#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>
#include <deque>

using std::deque;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::stringstream;

template<typename Container>
class PmergeMe
{
	private:
		Container list;
		Container arr_1;
		Container arr_2;
		Container jcp;
		Container f_jcp;
		Container tmp;

		clock_t start;
		clock_t end;
		double elapsed_time_ms;
		int to_wait;
		bool odds;
		int argc;
		stringstream  before;
		stringstream  after;

		void swap(int* a, int* b)
		{
			int temp = *a;
			*a = *b;
			*b = temp;
		}

	public:
		PmergeMe(int argc):odds(false)
		{
			this->argc = argc;
		}

		PmergeMe() : odds(false) {}

		~PmergeMe(){}

		PmergeMe(const PmergeMe& obj)
		{
			*this = obj;
		}

		PmergeMe& operator=(const PmergeMe& obj)
		{
			if (this != &obj)
			{
				list = obj.list;
				arr_1 = obj.arr_1;
				arr_2 = obj.arr_2;
				jcp = obj.jcp;
				f_jcp = obj.f_jcp;
				tmp = obj.tmp;
				start = obj.start;
				end = obj.end;
				elapsed_time_ms = obj.elapsed_time_ms;
				to_wait = obj.to_wait;
				odds = obj.odds;
				argc = obj.argc;
				before.str(obj.before.str());
				after.str(obj.after.str());
			}
			return *this;
		}

		void	check_redundance()
		{
			typename Container::iterator it = tmp.begin();
			typename Container::iterator itt;
			if (tmp.size() == 1)
				throw std::invalid_argument("");
			for (; it != tmp.end(); it++)
			{
				itt = it;
				itt++;
				for (; itt != tmp.end(); itt++)
				{
					if (*itt == *it)
						throw std::invalid_argument("Invalid Input");
				}
			}
		}

		void	parsing_input(char **arr, int argc)
		{
			int i = 1;
			double	n;
			char *end;
			string whitespace_chars = " \t\n\r\v\f";

			while (i < argc)
			{
				n = strtod(arr[i], &end);
				if ((n < 0) || (n > INT_MAX)|| *end || (string(arr[i]).find(".") != string::npos)
				|| (string(arr[i]).find_first_of(whitespace_chars) != string::npos) || !(*arr[i]))
					throw std::invalid_argument("Invalid Input");
				tmp.push_back(n);
				i++;
			}
			check_redundance();
		}

		void fill_list(char **argv)
		{
			int i = 1;
			while (i < argc)
			{
				before << atoi(argv[i]) << " ";
				list.push_back(atoi(argv[i++]));
			}

			if (list.size() % 2)
			{
				to_wait = list.back();
				list.pop_back();
				odds = true;
			}
		}

		void sort_two_pairs_in_desc()
		{
			for (size_t i = 0; i < list.size(); )
			{
				size_t a = i++;
				size_t b = i++;

				if (list[b] > list[a])
					swap(&list[b], &list[a]);
			}
		}

		void sort_in_asce_based_on_top_pair()
		{
			for (size_t i = 0; i < list.size(); )
			{
				for (size_t j = i + 2; j < list.size();)
				{
					if (list[i] > list[j])
					{
						swap(&list[i], &list[j]);
						swap(&list[i + 1], &list[j + 1]);
					}
					j += 2;
				}
				i += 2;
			}
		}

		void splitting_list()
		{
			for (size_t i = 0; i < list.size(); i++)
			{
				if (!(i % 2))
					arr_1.push_back(list[i]);
				else
					arr_2.push_back(list[i]);
			}
		}

		void generate_Jacobsthal_numbers()
		{
			jcp.push_back(0);
			jcp.push_back(1);
			for (size_t i = 2; i <= ((list.size() / 2) + 1); i++)
			{
				int n = jcp[i - 1] + (2 * jcp[i - 2]);
				jcp.push_back(n);
			}
			jcp.erase(jcp.begin() + 1);

			for (size_t i = 0; i < jcp.size(); i++)
			{
				if (f_jcp.size() && i != 0)
				{
					int diff = jcp[i] - jcp[i - 1];
					f_jcp.push_back(jcp[i]);
					for (int k = 1; f_jcp.size() < jcp.size() && k < diff; k++)
						f_jcp.push_back(jcp[i] - k);
				}
				else
					f_jcp.push_back(jcp[i]);
			}
		}
		
		size_t find_insert_index(int value)
		{
			typename Container::iterator it = std::upper_bound(arr_1.begin(), arr_1.end(), value);
			return std::distance(arr_1.begin(), it);
		}

		void move_back_to_main_chain()
		{
			size_t pos;
			for (size_t i = 0; i < f_jcp.size(); i++)
			{
				size_t ind = f_jcp[i];

				if (ind >= arr_2.size())
				{
					continue;
				}
				pos = find_insert_index(arr_2[ind]);
				arr_1.insert(arr_1.begin() + pos, arr_2[ind]);
			}

			if (odds)
			{
				pos = find_insert_index(to_wait);
				arr_1.insert(arr_1.begin() + pos, to_wait);
			}

			for (int i = 0; i < (int)arr_1.size(); i++)
			{
				after << arr_1[i] << " ";
			}
		}

		void	start_sorting(char **argv, string type, int n)
		{
			start = clock();
			fill_list(argv);
			sort_two_pairs_in_desc();
			sort_in_asce_based_on_top_pair();
			splitting_list();
			generate_Jacobsthal_numbers();
			move_back_to_main_chain();
			end = clock();
			
			elapsed_time_ms = double(end - start);
			if (n)
			{
				cout << "Before: "<< before.str() << endl;
				cout << "After: "<< after.str() << endl;
			}
			cout << "Time to process a range of " << argc - 1 << " elements with std::"<<type<<": "
				<< elapsed_time_ms << " us" << endl;
		}
};

#endif
