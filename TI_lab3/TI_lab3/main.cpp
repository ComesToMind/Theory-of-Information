#include "Kazakevich.h"
#include <string>
#include <vector>
#include <map>
#include <stdio.h>

using namespace Kaz;
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
	while (!fin.eof())
	{
		smb = fin.get();
		first_data.push_back(smb);
	}
	//calculate probabilities
	Run(first_data,"input.txt");
	
	system("pause");
	return 0;
}