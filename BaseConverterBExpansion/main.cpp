#include<iostream>
#include<string>
#include<vector>

double Value(std::vector<double>* result, double radix)
{
	//TODO: fix error when input = DBL_MAX
	double res = 0;
	for (long int i = 0; i < result->size(); i++)
		res += result->at(i) * pow(radix, i);

	return res;
}

double Value(std::vector<double>* before, std::vector<double>* after, double radix)
{
	double res = Value(before, radix);
	for (long int i = 0; i < after->size(); i++)
		res += after->at(i) * pow(radix, -i - 1);

	return res;
}

void Invert(std::vector<double>* before, std::vector<double>* after)
{
	std::reverse(before->begin(), before->end());
	std::reverse(after->begin(), after->end());
	before->swap(*after);
	before->push_back(after->at(after->size() - 1));
	after->resize(after->size() - 1);
}

void Print(std::vector<double>* before, std::vector<double>* after, bool invert)
{
	for (long int i = before->size() - 1; i > -1; i--)
		std::cout << before->at(i) << std::endl;
	std::cout << "............................" << std::endl;
	for (long int i = after->size() - 1; i > -1; i--)
		std::cout << after->at(i) << std::endl;
}

int main()
{
	double input = DBL_MAX;
	const double constInput = input;
	double radix = 0.0001;

	bool invert = false;
	if (radix < 1)
	{
		radix = 1 / radix;
		invert = true;
	}

	std::vector<double>* before = new std::vector<double>;
	while (input != 0)
	{
		double q = round(input / radix);
		double res = input - q * radix;
		before->push_back(res);
		input = (double)q;
	}

	double diff = constInput - Value(before, radix);

	int index = -1;
	std::vector<double>* after = new std::vector<double>;
	while (diff != 0)
	{
		double q = round(diff / pow(radix, index));
		after->push_back(q);
		diff = diff - q * pow(radix, index);
		index--;
	}

	diff = constInput - Value(before, after, radix);
	if (diff == 0)
	{
		if (invert)
			Invert(before, after);
		Print(before, after, invert);
	}

	int a;
	std::cin >> a;

	return 0;
}