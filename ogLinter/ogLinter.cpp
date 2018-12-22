#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define Log(x) cout << x << endl

int main() {
	string projectPath;
	string catFile = "select.txt";
	ifstream file(catFile);
	vector<string> filepaths;
	string temp;
	string macro = "glCall";
	while (getline(file, temp)) {
		filepaths.push_back(temp);
	}
	file.close();
	ifstream of(filepaths[0]);
	vector<string> fStrings;
	while (getline(of, temp)) {
		fStrings.push_back(temp);
	}
	of.close();
	ofstream toFile(filepaths[0] , ofstream::trunc);
	for (auto & str : fStrings){
		if (str.find("gl") != string::npos) {
			str[str.length() - 1] = ')';
			toFile << macro << '(' << str << ';' << '\n';
		}
		else {
			toFile << str << '\n';
		}
	}


	system("pause");


}
	