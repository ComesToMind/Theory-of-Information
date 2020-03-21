#include "mpir.h"
#include "Kazakevich.h"
#include <string>
#include <vector>
#include <map>
using namespace Kaz;
int main()
{
	mpz_t a, b, c;
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
	while (fin >> smb)
	{
		first_data.push_back(smb);
	}
	//calculate probabilities

	map<char, double> mp; 

	for (int i = 0; i < first_data.size(); i++)
	{
		//symbol with frequency 
		mp[first_data[i]]++;
	}

	for (map<char, double>::iterator p = mp.begin(); p != mp.end(); ++p)
	{
		p->second = p->second / first_data.size();
		
	}
	vector<pair<char, double>> probs(mp.begin(), mp.end());

	/*for (map<char, double>::iterator p = mp.begin(); p != mp.end(); ++p)
	{
		p->second += prev;
		prev = p->second;
	}*/
	//vector of innitial probabilities 
	

	for (size_t i = 1; i < probs.size(); i++)
	{
		probs[i].second += probs[i-1].second;
	}

	for (auto d : probs)
		cout << d.first<<':'<<d.second<<endl;

	//coding begin
	double low = 0.0;
	double high = 1.0;

	for(auto& smb : first_data)
	{
		for (size_t i = 0; i < probs.size(); i++)
		{
			if (probs[i].first == smb)
			{
				if (i == 0)
				{
					low = low + (high - low)*low;
					high = low + (high - low)*probs[i].second;
				}
				else
				{
					low = low + (high - low)*probs[i - 1].second;
					high = low + (high - low)*probs[i].second;
				}
				

			}
		}
	}
	double result = (low + high) / 2;
	cout << result <<endl;
	ofstream fout("output.txt");




	system("pause");
	return 0;
}