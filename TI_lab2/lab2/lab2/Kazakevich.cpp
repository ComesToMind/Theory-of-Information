#include "Kazakevich.h"
#include <algorithm>
#include <map>

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
		return a.probability > b.probability;
	}
} compare;
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

Kaz::output Kaz::Run(vector<char> const &alphabet, vector<double> const &probs)
{
	output out;
	//в этом массиве хранятся склеенные буквы "вгд" и сложенные вероятности
	vector<Container> cnt;
	for (int i = 0; i < alphabet.size(); i++)
	{
		Container temp;
		temp.smb = alphabet[i];
		temp.probability = probs[i];
		cnt.push_back(temp);
	}
	sort(cnt.begin(), cnt.end(), compare);
	//в этом массиве хранятся коды, но буквы без изменений "а" "б"
	vector<Container> cods = cnt;
	//массив тестовый, не будет работать без выхода за пределы
	for (int i = 0; i < cnt.size(); i++)
	{
		for (int j = 0; j < cods.size(); j++)
		{
			//элемент слева в массиве, дабавляем кодовый 0 
			if (count(cnt[i].smb.begin(), cnt[i].smb.end(), cods[j].smb))
			{
				cods[j].code = "0" + cods[j].code;
			}
			//элемент справа в массиве, дабавляем кодовый 1 
			//возможен выход за пределы массива
			if (count(cnt[i + 1].smb.begin(), cnt[i].smb.end(), cods[j].smb))
			{
				cods[j].code = "1" + cods[j].code;
			}
		}
		//складываем наименьшие вероятности
		cnt[i].probability += cnt[i+1].probability;
		//склеиваем их буквы
		cnt[i].smb += cnt[i + 1].smb;
		//удаляем элемент 
		cnt.erase(cnt.begin() + 1);
		//опять сортируем 
		sort(cnt.begin(), cnt.end(), compare);

	}
	return out;
	
}