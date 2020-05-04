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
		temp += first_data[position]; //for coding phrases

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
				//look for next matching characters (bigram, trigramm and e.t.c.)
				temp += first_data[position];
				if (vocabulary.find(temp) == string::npos)
				{
					if (temp.back() == '\0')
					{
						//first_data end
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
		//if single symbol
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

	void Kaz::RunCoder(vector<char> first_data, string filename)
	{
		first_data.push_back('\0');
		vector<Code> Codes;
		Code code;
		ofstream fout(filename);

		string vocabulary, temp;

		for (size_t position = 0; position < first_data.size(); position++)
		{
			temp += first_data[position]; //for coding phrases

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
					//look for next matching characters (bigram, trigramm and e.t.c.)
					temp += first_data[position];
					if (vocabulary.find(temp) == string::npos)
					{
						if (temp.back() == '\0')
						{
							//first_data end
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
			fout << i->offset << " " << i->length << " " << i->symbols << endl;
		}
	}

	void Kaz::RunDecoder(string filename_in, string filename_out)
	{
		ifstream fin(filename_in);
		ofstream fout(filename_out);
		int offset, length;
		char ch;
		string vocab,temp2;
		while (fin.peek() != EOF)
		{
			fin >> offset >> length;
			if (fin.fail())
			{
				break;
			}
			fin.get();
			fin.get(ch);
			
			if (length == 0)
			{
				fout << ch;
				vocab += ch;
			}
			else
			{
				for (size_t j = 0; j < length;j++)
				{

					fout << vocab[vocab.size() - offset + j];
					temp2 += vocab[vocab.size() - offset + j];
				}
				fout << ch;
				vocab += temp2 + ch;
				temp2.clear();
			}

		}
	}
