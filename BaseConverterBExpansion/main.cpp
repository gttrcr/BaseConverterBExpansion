#include <iostream>
#include <string>
#include <vector>

namespace StringUtils
{
	std::vector<std::string>* Split(std::string str, std::string del)
	{
		std::vector<std::string>* ret = new std::vector<std::string>();
		size_t pos = 0;
		std::string token;
		while ((pos = str.find(del)) != std::string::npos)
		{
			token = str.substr(0, pos);
			ret->push_back(token);
			str.erase(0, pos + del.length());
		}

		ret->push_back(str);

		return ret;
	}

	void Reverse(std::string& str)
	{
		int len = str.length();
		int n = len - 1;
		for (int i = 0;i < (len / 2);i++)
		{
			std::swap(str[i], str[n]);
			n = n - 1;
		}
	}

	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to)
	{
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos)
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
		return str;
	}
}

double ToBase10(std::string number, double fromBase)
{
	std::vector<std::string>* parts = StringUtils::Split(number, ".");
	std::string intPart = parts->at(0);
	StringUtils::Reverse(intPart);

	std::string decPart = "";
	if (parts->size() > 1)
		decPart = parts->at(1);

	double n = 0;
	unsigned int part = (unsigned int)log10(fromBase - 1) + 1;
	for (unsigned int i = 0; i < intPart.length(); i += part)
	{
		std::string current = intPart.substr(i, part);
		StringUtils::Reverse(current);
		n += std::stof(current) * pow(fromBase, (float)(i / part));
	}
	
	for (unsigned int i = 0; i < decPart.length(); i++)
		n += (decPart[i] - '0') * pow(fromBase, -((float)i + 1));

	return n;
}

std::string ToBase(double number, double toBase)
{
	std::string result = "";
	unsigned int part = (unsigned int)log10(toBase - 1) + 1;
	int exp = log10(number) / log10(toBase);
	for (; number > DBL_EPSILON; exp--)
	{
		unsigned int digit = number / pow(toBase, exp);
		number = number - digit * pow(toBase, exp);

		std::string comp = std::to_string(digit);
		comp.insert(comp.begin(), part - comp.length(), '0');
		result += comp;

		if (exp == 0)
			result += ".";
	}

	if (number < DBL_EPSILON && exp != 0)
	{
		std::string pad = "";
		pad.insert(pad.begin(), exp + 1, '0');
		result += pad;
	}

	return result;
}

std::string Convert(std::string number, double fromBase, double toBase, bool useChar = false)
{
	std::string newNumber = number;
	if (useChar)
	{
		newNumber = "";
		unsigned int part = (unsigned int)log10(fromBase - 1) + 1;
		for (unsigned int i = 0; i < number.length(); i++)
		{
			std::string comp = "";
			if (number[i] - '0' >= 0 && number[i] - '0' <= 9)
			{
				comp = number[i];
				comp.insert(comp.begin(), part - comp.length(), '0');
				newNumber += comp;
			}
			else if (number[i] - '0' > 16)
			{
				comp = std::to_string(number[i] - '7');
				newNumber += comp;
			}
		}
	}

	double base10Number = ToBase10(newNumber, fromBase);
	std::string result = ToBase(base10Number, toBase);

	std::string newResult = result;
	if (useChar)
	{
		newResult = "";
		unsigned int part = (unsigned int)log10(fromBase - 1) + 1;
		for (unsigned int i = 0; i < result.length() - 1; i += part)
		{
			std::string substr = result.substr(i, part);
			unsigned int digit = std::stoi(substr);
			char ch;
			if (digit >= 10)
				ch = (char)(digit + '7');
			else
				ch = (char)(digit + '0');
			newResult += ch;
		}
	}

	return newResult;
}

int main()
{
	std::cout << "Base converter from any base to any base" << std::endl;
	std::cout << "To avoid problem with base > 16, instead of using A for 10, B for 11, and so on," << std::endl;
	std::cout << "use extended values 10, 11, ... . For example the number AB5D (base 16) become 10110513." << std::endl;

	std::string start = "ABC";
	std::string result = Convert(start, 16, 17, true);
	std::cout << result << std::endl;
	result = Convert(result, 17, 16, true);
	std::cout << result << std::endl;

	int a;
	std::cin >> a;
}
