#include "Kazakevich.h"

class Container
{
public:
	double probability = 0.0;
	string smb = "";

};




Kaz::output Kaz::Run(vector<char> const &alphabet, vector<double> const &probs, int const &arn)
{
	output out;
	double SumProbs = accumulate(probs.begin(), probs.end(), 0.0);
	if (abs(SumProbs - 1) >= numeric_limits<double>::epsilon())
	{
		cout << "Incorrect sum of probabilities!!! " << endl;
		return out;
	}


	return out;

}



