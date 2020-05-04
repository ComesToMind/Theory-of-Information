#include "Kazakevich.h"
#include <bitset>
#include <iostream>
#include <fstream>

void Kaz::RunCoder(vector<char> first_data, string filename)
{
	ofstream fout(filename);

	vector<bitset<12>> Codes;
	//
	//form codes  **+*+++*++++ ,when " * "- 0 parity bit 
	//
	int counter,place;
	for (size_t i = 0; i < first_data.size(); i++)
	{
		bitset<12> code_Parity_is_NULL;
		unsigned char infTemp = first_data[i];
		bitset<8> bitset_Temp_Inf(infTemp);
		counter = 1, place = 0;
		while (counter <=12)
		{
			if (counter && !(counter & (counter - 1))) // check if the power if 2
			{
				code_Parity_is_NULL[counter - 1] = 0;
				
			}
			else
			{
				code_Parity_is_NULL[counter - 1] = bitset_Temp_Inf[place];
				place++;
				
			}
			counter++;

		}

		Codes.push_back(code_Parity_is_NULL);

	}

	//
	//form codes  **+*+++*++++ ,when " * "-  parity bit is UP
	//
	//computing parity bits 
	
	bool r1 = 0, r2 =0, r3=0, r4=0;

	for (auto & var : Codes)
	{
		r1 = 0, r2 = 0, r3 = 0, r4 = 0;
		r1 = var[2] ^ var[4] ^ var[6] ^ var[8] ^ var[10];
		r2 = var[2] ^ var[5] ^ var[6] ^ var[9] ^ var[10];
		r3 = var[3] ^ var[4] ^ var[5] ^ var[6] ^ var[11];
		r4 = var[7] ^ var[8] ^ var[9] ^ var[10] ^ var[11];
		var[0] = r1;
		var[1] = r2;
		var[3] = r3;
		var[7] = r4;
		fout << var.to_string()<<endl;
	}

};
void Kaz::RunDecoder(string filename)
{
	ifstream fin(filename);

	vector<bitset<12>> Codes;
	string row;
	while (fin.peek() != EOF)
	{
		getline(fin, row);
		Codes.push_back(bitset<12>(row));
	} 
	///////////////////
	//
	//error correction
	//
	///////////////////
	
	for (auto & var : Codes)
	{
		bitset<4> errors;
		errors[0] = var[0] ^ var[2] ^ var[4] ^ var[6] ^ var[8] ^ var[10];
		errors[1] = var[1] ^ var[2] ^ var[5] ^ var[6] ^ var[9] ^ var[10];
		errors[2] = var[3] ^ var[4] ^ var[5] ^ var[6] ^ var[11];
		errors[3] = var[7] ^ var[8] ^ var[9] ^ var[10] ^ var[11];

		//erros (decimal-1) is addres of error in data
		unsigned long eror = errors.to_ulong();
		if (eror)
		{
			var[eror - 1].flip();
		}
	}
	ofstream fout("output.txt");

	int counter, place;
	//output symbols 
	for (auto & var : Codes)
	{
		counter = 1;
		place = 0;
		bitset<8> temp;
		while (counter <= 12)
		{
			if (!(counter && !(counter & (counter - 1)))) // check if the power != 2
			{
				temp[place] = var[counter - 1];
				place++;
			}
			counter++;
		}
		fout << (char)temp.to_ulong();

	}

};