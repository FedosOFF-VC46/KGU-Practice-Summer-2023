#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	const size_t SCREEN_WIDTH = 80;
	const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 4;
	size_t number_count, bin_count, scaling_stars, scaling_stars_max = 0; 
	int number, count_minus_inBorder = 0;
	cerr << "Enter number count: ";
	cin >> number_count;

	vector<double> numbers(number_count);

	const int fixed_size = numbers.size();
	numbers.clear();

	cerr << "Enter numbers:";

	for (size_t i = 0; i < fixed_size; i++)
	{
		cin >> number;
		numbers.push_back(number);
	}

	cerr << "Enter number of baskets: ";
	cin >> bin_count;
	vector<size_t> bins(bin_count);

	sort(numbers.begin(), numbers.end());

	double min = numbers[0];
	double max = numbers[0];
	for (double x : numbers) 
	{
		if (x < min) {
			min = x;
		}
		else if (x > max) 
		{
			max = x;
		}
	};

	double bin_size = (max - min) / bin_count;

	for (size_t i = 0; i < number_count; i++) 
	{
		bool found = false;
		for (size_t j = 0; (j < bin_count - 1) && !found; j++) 
		{
			auto lo = min + j * bin_size;
			auto hi = min + (j + 1) * bin_size;
			if ((lo <= numbers[i]) && (numbers[i] < hi)) 
			{
				bins[j]++;
				found = true;
			}
		}
		if (!found) {
			bins[bin_count - 1]++;
		}
	}

	size_t max_count = 0;
	bool flag_overflow = false;
	for (size_t i = 0; i < bin_count; i++) 
	{

		if (bins[i] > max_count)
		{
			max_count = bins[i];
			if (bins[i] > MAX_ASTERISK)
				flag_overflow = true;
		}
	}

	if(flag_overflow == true)
	{ 
		for (size_t i = 0; i < bin_count; i++) 
		{ 
			{
				scaling_stars = (int)MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
				if (scaling_stars_max < scaling_stars)
				{
					scaling_stars_max = scaling_stars;
				}
			}
		}
	}
	else
	{
		scaling_stars_max = max_count;
	}


	cout << "+";
	while (count_minus_inBorder != (scaling_stars_max + 5))
	{
		cout << "-";
		count_minus_inBorder++;
	}
	count_minus_inBorder = 0;
	cout << "+" << endl;
	


	for (size_t i = 0; i < bin_count; i++) 
	{
		int count_stars_toBorder = 0;

		if (bins[i] < 100 && bins[i] >= 10)
			cout << "|" <<  " " << bins[i] << "|";
		else if (bins[i] < 10)
			cout << "|" << "  " << bins[i] << "|";
		else if (bins[i] >= 100)
			cout << "|" << bins[i] << "|";

		if (flag_overflow) 
		{
			bins[i] = (int)MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
		}

		for (size_t j = 0; j < bins[i]; j++) 
		{
			cout << "*";
			count_stars_toBorder++;
		}

		while (count_stars_toBorder != scaling_stars_max)
		{
			cout << " ";
			count_stars_toBorder++;
		}

		cout << " " << "|" << endl;
	}

	cout << "+";
	while (count_minus_inBorder != (scaling_stars_max + 5))
	{
		cout << "-";
		count_minus_inBorder++;
	}
	cout << "+" << endl;

	return 0;
}