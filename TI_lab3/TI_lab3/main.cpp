#include "mpir.h"
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

	
	mpf_t* mpir_probs = new mpf_t[probs.size()];
	mpf_init2(mpir_probs[0], 9999);
	mpf_set_d(mpir_probs[0], probs[0].second);
	for (size_t i = 1; i < probs.size(); i++)
	{
		probs[i].second += probs[i-1].second;
		mpf_init2(mpir_probs[i], 9999);
		mpf_set_d(mpir_probs[i], probs[i].second);
		


	}

	for (auto d : probs)
		cout << d.first<<':'<<d.second<<endl;

	//coding begin

	mpf_t low,lowOld, high, tempD, temp, temp_two;
	mpf_init2(low, 9999);
	mpf_init2(lowOld, 9999);
	mpf_init2(high, 9999);
	mpf_set_d(high,1.0);
	mpf_init2(temp, 9999);
	mpf_init2(tempD, 9999);

	/*double low = 0.0, lowOld = 0.0;
	double high = 1.0;*/


	for(auto& smb : first_data)
	{
		for (size_t i = 0; i < probs.size(); i++)
		{
			if (probs[i].first == smb)
			{
				if (i == 0)
				{
					//low = lowOld + (high - lowOld)*low;
					
					/*high = lowOld + (high - lowOld)*probs[i].second;
					lowOld = low;*/

					mpf_sub(tempD,high, lowOld); //sub in parenthesis (high - lowOld)
					mpf_mul(temp, tempD, mpir_probs[i]); //(high - lowOld)*probs[i].second;
					mpf_add(high, temp, lowOld);//lowOld + ...
					mpf_set(lowOld,low); //lowOld = low

					/*mpf_out_str(stdout, 10, 0, low);
					cout <<" ";
					mpf_out_str(stdout, 10, 0, high);
					cout << endl;
*/
				}
				else
				{
					/*low = lowOld + (high - lowOld)*probs[i - 1].second;
					high = lowOld + (high - lowOld)*probs[i].second;
					lowOld = low;*/
					mpf_sub(tempD, high, lowOld);
					mpf_mul(temp, tempD, mpir_probs[i-1]);
					mpf_add(low, temp, lowOld);
					

					mpf_mul(temp, tempD, mpir_probs[i]);
					mpf_add(high, temp, lowOld);
					mpf_set(lowOld, low);

					/*mpf_out_str(stdout, 10, 0, low);
					cout << " ";
					mpf_out_str(stdout, 10, 0, high);
					cout << endl;*/

				}
				

			}
		}
	}

	//double result = (low + high) / 2;
	mpf_init2(temp_two, 9999);
	mpf_set_d(temp_two, 2.0);
	mpf_add(temp,low,high);
	mpf_div(temp,temp,temp_two);
	FILE * fo;
	fopen_s(&fo,"output.txt" , "w");
	mpf_out_str(fo, 10, 0,temp);
	fclose(fo);

	//cout << result <<endl;


	ofstream fout("output.txt", std::ios_base::app);
	int flag = first_data.size();
	mpf_t tempDifDown;
	mpf_init2(tempDifDown, 9999);
	fout << endl;

	while(--flag)
	{
		for (size_t i = 0; i < probs.size(); i++)
		{
			if (i == 0)
			{
				/*if (result >= 0 && result < probs[i].second)
				{
					fout << probs[i].first;
					result = (result - 0) / (probs[i].second);
		
				}*/
				if (mpf_cmp_d(temp,0.0) >=0 && mpf_cmp(temp,mpir_probs[i])<0)
				{
					fout << probs[i].first;
					mpf_div(temp,temp, mpir_probs[i]);

				}

			}
			else
			{
				/*if (result >= probs[i-1].second && result < probs[i].second)
				{
					fout << probs[i].first;
					result = (result - probs[i - 1].second) / (probs[i].second - probs[i - 1].second);
				}*/
				if (mpf_cmp(temp, mpir_probs[i - 1]) >= 0 && mpf_cmp(temp, mpir_probs[i]) < 0)
				{
					fout << probs[i].first;
					//(result - probs[i - 1].second)
					mpf_sub(temp,temp, mpir_probs[i - 1]);
					//(probs[i].second - probs[i - 1].second);
					mpf_sub(tempDifDown, mpir_probs[i], mpir_probs[i - 1]);
					mpf_div(temp, temp, tempDifDown);
				}
			}
		}
	} 

	fout.close();

	mpf_clear(low);
	mpf_clear(lowOld);
	mpf_clear(high);
	mpf_clear(temp);
	mpf_clear(temp_two);
	mpf_clear(tempD);
	mpf_clear(tempDifDown);
	system("pause");
	return 0;
}