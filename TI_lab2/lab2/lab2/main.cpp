#include "Kazakevich.h"
#include <Windows.h>
#include <string>
using namespace std;
using namespace Kaz;
#define ARITY 4


int main(int argc, char* argv[])
{
	/*if (argc != 2)
	{
		cout << "incorrect command line! "
			"Waited: command infile outfile" << endl;
		exit(1);
	}*/

	
	//ofstream fout(argv[2]);

	vector<char> Alphabet;
	vector<double> Probs;
	vector<double> VecInQuintity;

	cout << "Start" << endl;
	char filename[10];
	cout << "Enter filename: ";
	cin >> filename;
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Incorrect filename: ";
		exit(1);
	}
	Read_File(Alphabet, Probs, fin);
	output result = Run(Alphabet, Probs,ARITY);
	
	cout << "Codes ";
	for (auto var : result.Codes)
		cout << var;
	cout << endl;
	cout << "Average: " << result.Average << endl;

	cout << "Stop" << endl;
	system("pause");
	return 0;
}
