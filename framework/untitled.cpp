#include <iostream>
#include <fstream>
#include <string>

int main () {
	std::string line;
	std::ifstream file ("example.txt");
	auto status = "";
	auto order = "";

	if(file.is_open()){
		cin >> line;
		cout << line;
	}


}