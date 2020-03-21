#pragma once
#include <fstream>
#include <vector>
#include <iterator>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

namespace Kaz
{
	struct output
	{
		
		double Code = 0.0;
	};
	output Run(vector<char> const &alphabet, vector<double> const &probs, int const &arn);

}

