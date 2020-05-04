#pragma once
#include <string>
#include <vector>


using namespace std;

namespace Kaz
{

	void Run(vector<char> text, string filename);
	void RunCoder(vector<char> text, string filename);
	void RunDecoder(string filename_in, string filename_out);

}