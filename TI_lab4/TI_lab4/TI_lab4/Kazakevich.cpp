#include "Kazakevich.h"
#include <vector>
#include <iostream>
#include <fstream>

struct Code
{
	size_t offset;
	size_t length;
	//string symbols;
	char symbols;
};
void Kaz::Run(vector<char> first_data, string filename)
{
	first_data.push_back('\0');
	vector<Code> Codes;
	Code code;
	ofstream fout(filename);

	string vocabulary, temp;

	for (size_t position = 0; position < first_data.size(); position++)
	{
		temp += first_data[position];

		if (vocabulary.find(temp) == string::npos)
		{
			//symbol is found for the first time
			code.offset = 0;
			code.length = 0;
			code.symbols = temp[0];
		}
		else
		{
			code.length = 1;//
			while (true)
			{
				//r.find - for minimal offset (characters)
				code.offset = vocabulary.length() - vocabulary.rfind(temp);
				position++;
				//look for next matching characters
				temp += first_data[position];
				if (vocabulary.find(temp) == string::npos)
				{
					if (temp.back() == '\0')
					{
						temp.pop_back();
						code.length--;
					}
					code.symbols = temp.back();
					break;
				}
				else
				{
					code.length++;
				}
			}
		}

		vocabulary += temp;
		Codes.push_back(code);
		temp.clear();
	}

	for (auto i = Codes.begin(); i != Codes.end(); ++i)
	{
		fout << "<" << i->offset << "," << i->length << "," << i->symbols << ">" << endl;
	}
	fout << endl;


	///////////////
	//
	//decode
	//
	///////////////
	string temp2;
	for (size_t i = 0; i < Codes.size(); i++)
	{
		//if(i==)
		if (Codes[i].length == 0)
		{
			fout << Codes[i].symbols;
			temp += Codes[i].symbols;
		}
		else
		{
			for (size_t j = 0; j < Codes[i].length; j++)
			{

				fout << temp[temp.size() - Codes[i].offset + j];
				temp2 += temp[temp.size() - Codes[i].offset + j];
			}
			fout << Codes[i].symbols;
			temp += temp2 + Codes[i].symbols;
			temp2.clear();
		}
	}
}