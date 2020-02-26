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
	//� ���� ������� �������� ��������� ����� "���" � ��������� �����������
	vector<Container> cnt;
	for (int i = 0; i < alphabet.size(); i++)
	{
		Container temp;
		temp.smb = alphabet[i];
		temp.probability = probs[i];
		cnt.push_back(temp);
	}
	sort(cnt.begin(), cnt.end(), compare);
	//� ���� ������� �������� ����, �� ����� ��� ��������� "�" "�"
	vector<Container> cods = cnt;
	//������ ��������, �� ����� �������� ��� ������ �� �������
	for (int i = 0; i < cnt.size(); i++)
	{
		for (int j = 0; j < cods.size(); j++)
		{
			//������� ����� � �������, ��������� ������� 0 
			if (count(cnt[i].smb.begin(), cnt[i].smb.end(), cods[j].smb))
			{
				cods[j].code = "0" + cods[j].code;
			}
			//������� ������ � �������, ��������� ������� 1 
			//�������� ����� �� ������� �������
			if (count(cnt[i + 1].smb.begin(), cnt[i].smb.end(), cods[j].smb))
			{
				cods[j].code = "1" + cods[j].code;
			}
		}
		//���������� ���������� �����������
		cnt[i].probability += cnt[i+1].probability;
		//��������� �� �����
		cnt[i].smb += cnt[i + 1].smb;
		//������� ������� 
		cnt.erase(cnt.begin() + 1);
		//����� ��������� 
		sort(cnt.begin(), cnt.end(), compare);

	}
	return out;
	
}