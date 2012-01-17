#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {

	string str;
	ifstream f1("fil.txt");
	while (f1 >> str) {
		cout << str << endl;
	}

}
