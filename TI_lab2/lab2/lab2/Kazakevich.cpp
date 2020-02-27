#include "Kazakevich.h"
#include <algorithm>
#include <sstream>

//template <typename T>
//перевод int в string
string toString(int val)
{
	ostringstream oss;
	oss << val;
	return oss.str();
}
class Container
{
public:
	double probability = 0.0;
	string smb = "";
	string code = ""; 
	
};

class cmp {
public:
	bool operator() (const Container &a, const Container &b) {
		return a.probability < b.probability;
	}
} compare;

class cmpAlph
{
public:
	bool operator() (const Container &a, const Container &b) { return a.smb < b.smb; }
}compareAlph;

void Kaz::Read_File(vector<char> &alphabet, vector<double> &probs, ifstream &fin)
{
	int amount;
	char sb;
	double pr;
	fin >> amount;
	alphabet.resize(amount);
	for (int i = 0; i < amount; i++)
	{
		fin >> sb;
		alphabet[i] = sb;
	}
	for (int i = 0; i < amount; i++)
	{
		fin >> pr;
		probs.push_back(pr);
	}
	fin.close();
	return;
}

Kaz::output Kaz::Run(vector<char> const &alphabet, vector<double> const &probs, int const &arn)
{
	//сумма вероятностей должна быть равна 1 
	output out;
	double SumProbs = accumulate(probs.begin(), probs.end(), 0.0);
	if (abs(SumProbs - 1) >= numeric_limits<double>::epsilon())
	{
		cout << "Incorrect sum of probabilities!!! " << endl;
		return out;
	}

	//в этом массиве хранятся склеенные буквы "вгд" и сложенные вероятности
	vector<Container> cnt;
	for (int i = 0; i < alphabet.size(); i++)
	{
		//если вероятность символа равна 0 то просто его пропускаем
		if ((probs[i] - 0.0) > numeric_limits<double>::epsilon())
		{
			Container temp;
			temp.smb = alphabet[i];
			temp.probability = probs[i];
			cnt.push_back(temp);
		}
		
	}
	sort(cnt.begin(), cnt.end(), compare);
	//в этом массиве хранятся коды, но буквы без изменений "а" "б"
	vector<Container> cods = cnt;
	//массив тестовый, не будет работать без выхода за пределы

	//если сделать 1 символ 
	if (cnt.size() == 1)
	{
		cods[0].code = "0";
	}

	//а теперь реализовать код до 10 арностей 
	
	while(cnt.size()!=1)
	{
		for (int j = 0; j < cods.size(); j++)
		{

			//производим от 0 до arn-1 
			for (int a = 0; a < arn; a++)
			{
				if (a < cnt.size())
				{
					//элемент слева в массиве, дабавляем кодовый 0
					if (count(cnt[a].smb.begin(), cnt[a].smb.end(), cods[j].smb[0]))
					{
						cods[j].code = toString(a) + cods[j].code;
					}

				}


			}
		}
		if (arn <= cnt.size())
		{
			for (int a = arn-1; a >0; a--)
			{
				//скалыдваем вероятности и буквы и удаляем с конца
				cnt[0].probability += cnt[a].probability;
				cnt[0].smb += cnt[a].smb;
				cnt.erase(cnt.begin() + (a));

			}

		}
		else
		{
			//у нас осталось элементов меньше, чем арности
			for (int a = cnt.size()-1; a >0; a--)
			{
				//скалыдваем вероятности и буквы и удаляем с конца
				cnt[0].probability += cnt[a].probability;
				cnt[0].smb += cnt[a].smb;
				cnt.erase(cnt.begin() + (a));

			}

		}
		
		sort(cnt.begin(), cnt.end(), compare);
	}

	//сортируем по алфавиту для красоты 
	sort(cods.begin(), cods.end(), compareAlph);
	for (auto var : cods)
	{
		out.Average += var.probability*var.code.size();
		out.Codes.push_back(var.smb+" = "+var.code+" ");
	}

	return out;
	
}