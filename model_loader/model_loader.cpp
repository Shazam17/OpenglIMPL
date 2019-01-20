#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

#define Log(x) cout << x << endl

struct vec3 {
	float x;
	float y;
	float z;

	void log() {
		cout << x << "|" << y << "|" << z << endl;
	}
};
struct vec2 {
	float x;
	float y;
};
void loadOBJ(const char * path) {
	float ** fileArr;
	ifstream file("cube.obj");

	vector<vec3> cords;
	vector<vec2> textCords;
	vector<vec3> norm;

	int mode = -1;
	string str;
	while (getline(file, str)) {

		if (str[0] == 'v' && str[1] == ' ') {
			istringstream ss(str);
			string fWord;
			ss >> fWord;
			float x, y, z;
			ss >> x >> y >> z;
			cords.push_back({ x , y , z });

		}
		else if (str[0] == 'v' && str[1] == 't') {
			istringstream ss(str);
			string fWord;
			float x, y;
			ss >> fWord;
			ss >> x >> y;
			textCords.push_back({ x , y });
		}
		else if (str[0] == 'v' && str[1] == 'n') {
			istringstream ss(str);
			string fWord;
			ss >> fWord;
			float x, y, z;
			ss >> x >> y >> z;
			norm.push_back({ x , y , z });
		}
	}
}

int main(){

	loadOBJ("cube.obj");

    std::cout << "Hello World!\n"; 
}
