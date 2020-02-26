#include "Kazakevich.h"
#include <Windows.h>
using namespace std;
using namespace Kaz;



int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "incorrect command line! "
			"Waited: command infile outfile" << endl;
		exit(1);
	}

	ifstream fin(argv[1]);
	//ofstream fout(argv[2]);

	vector<char> Alphabet;
	vector<double> Probs;
	vector<double> VecInQuintity;

	cout << "Start" << endl;


	Read_File(Alphabet, Probs, fin);
	output result = Run(Alphabet, Probs);
	/*
	cout << "Information content: ";
	for (auto var : result.infQuantity)
		cout << var << " ";
	cout << endl;
	cout << "Entropy: " << result.entropy << endl;*/

	cout << "Stop" << endl;
	system("pause");
	return 0;
}
