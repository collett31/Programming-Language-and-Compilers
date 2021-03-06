
// CompilerProgram.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <fstream> // file library; access to open files and file explorer. ifstream ==> input! ofstream ==> output!
#include "Header.h" 
#include <string>
using namespace std;
using namespace COMPILERPROGRAM;


int main(){
	std::string oneline;
	string fname;
	Compiler p;
	int counter = 1;
	cout << "Please enter the source code file name: " << endl;
	getline(cin, fname);
	ifstream readln;
	readln.open(fname, ios::in);// can only read, not write to the file.

	if (readln.is_open())
		while (!readln.eof()){
			getline(readln, oneline);
			p.read(oneline); // read function puts each line into a string array
			counter = counter + 1;
		}

	else
		cout << " The file could not be opened" << endl;
	readln.close();
	// it is time to compile!
	if (p.Compile()) {
		cout << "Compile successful" << endl;
		p.run();
	}
	else{
		cout << "Errors were found" << endl;
		p.showerror();
	}
	system("pause");
	return 0;
}
