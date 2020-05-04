#include "Kazakevich.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	cout << "Start" << endl;
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	if (filename == "1")
	{
		filename = "input.txt";
	}
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Incorrect filename: ";
		exit(1);
	}
	//read data from file 
	vector<char> first_data;
	char smb;
	while (fin.peek()!=EOF)
	{
		smb = fin.get();
		first_data.push_back(smb);
	}
	Kaz::RunCoder(first_data,"Kazakevich_output.txt");
	Kaz::RunDecoder("Kazakevich_output.txt", "Kazakevich_output_decode.txt");

	return 0;
}