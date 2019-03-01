#pragma once
#ifndef COMPILER
#define COMPILER

#include <string>
#include <iostream>


namespace COMPILERPROGRAM
{
class Compiler
{
	public:
		Compiler()
		{
			size = 0; // initialize the size before the progrm runs each time
			errorcount = 0; //initialize the size or your error count before you begin
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 4;j++){
					table[i][j] = "unassigned";
					std::cout << table[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
		
		bool Compile()
		{
			if (size < 3){//check to see if the code has 3 or more lines to include begin statement list and end statements
				error[errorcount] = "incomplete source code";
				errorcount = errorcount + 1;// add to the error count once an error is made

			}
			else if (code[size - 1] != "end"){// check to see if the program ends with an end statement
				error[errorcount] = "last line should be [end]";
				errorcount = errorcount + 1;// add to the error count once an error is made

			}
			if (code[0] != "begin"){// check to see if the program begins with an begin statement
				error[errorcount] = "first line should be [begin]";
				errorcount = errorcount + 1;// add to the error count once an error is made

			}
			if (size >= 3) {
				statementcompile();
			}
			if (errorcount == 0) {
				
				return true;
			}
			else
				return false;
		}
		void showerror()
		{
			int i;
			for (i = 0; i < errorcount; i = i + 1)
				std::cout << error[i] << std::endl;
		}
		void read(std::string v)// reads files that are put into the object
		{
			code[size] = v;
			size = size + 1;
		}

		std::string get_line(int i) {
			return code[i];
		}
		void run() {
			errorcount = 0;
			for (int i = 1; i < size - 1; i++) {
				if (code[i].substr(0, 7) == "display" && code[i].size() > 11) {
					display_string(code[i]);
				}
				if (code[i].substr(0, 7) == "display" && code[i].size() == 10) { 
					if (!display_int(code[i])) {
						showerror();
					}
				}
				if (code[i].substr(0, 5) == "input") { 
					if (!int_assign(code[i]))
						showerror();
				}
				if (code[i][0] == 'A' || code[i][0] == 'B' || code[i][0] == 'C') { 
					if(!calculate(code[i]))
						showerror(); 
				//	std::cout << tempVar << std::endl; 
				}
				//std::cout << " here1" << std::endl;;
			}
		}
	private:
		std::string code[50]; //need an array to hold the string values, array you always need size
		int size; // code array size
		std::string error[50];// create and error array
		int errorcount;// error array size
		char symbol; 
		std::string table[2][4];
		int total, tablecount=0;
		int temp=0, temp1=0, tempVar;
		bool updated=false;

		void statementcompile()
		{
			int i;
			for (i = 1; i < size - 1; i = i + 1)
			{
				if (code[i].substr(0, 7) == "display")//check if the display statement has keyword display there
				{
					if (code[i].length() < 10) // check whether there is actually something to display based on the length
					{
						error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement";
						errorcount = errorcount + 1;// add to the error count once an error is made
					}
					if (code[i][code[i].length() - 1] != ';'){
						error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement, ';' missing";
						errorcount = errorcount + 1;// add to the error count once an error is made
					}	
				}
				 if (code[i].substr(0, 5) == "input") {
					if (code[i].length() < 7) { // check whether there is actually something to input based on the length
						error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete input statement";
						errorcount = errorcount + 1;// add to the error count once an error is mad
					}
				}
				 if(code[i].substr(0, 1) == "A" || code[i].substr(0, 1) == "B" || code[i].substr(0, 1) == "C"){
					 if (code[i].length() < 3) { // check whether there is actually something to input based on the length
						 error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete assign statement";
						 errorcount = errorcount + 1;// add to the error count once an error is mad
					 }
				 }
			}
		}
		bool int_assign(std::string code) {
			errorcount = 0;
			if (code[6] == 'A') {
				table[0][tablecount] = "A";
				table[1][tablecount] = code.substr(8, code.size() - 9);
				++tablecount;
				return true;
			}
			else if (code[6] == 'B') {
				table[0][tablecount] = "B";
				table[1][tablecount] = code.substr(8, code.size() - 9);
				++tablecount;
				return true;
			}
			else if (code[6] == 'C') {
				table[0][tablecount] = "C";
					table[1][tablecount] = code.substr(8, code.size() - 9);
					++tablecount;
					return true;
			}
			else {
				error[errorcount] = "ASSIGNMENT ERROR OCCURED";
				errorcount++;
				return false;
			}
		}
		bool calculate(std::string code) {
			errorcount = 0; std::string keep;
			if (code[0] == 'A') {
			keep = "A";
				if (code[2] == 'B') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "B") {
							if (table[1][i] != "unassigned") {
								temp = std::stoi(table[1][i]);
							}
							else {
								error[errorcount] = "this value has not been assigned yet : 'B' ";
								errorcount++;
								return false;
							}
						}
					}

				}
				if (code[4] == 'B') {
					for (int i = 0; i < 3; i++) {
						if (table[0][i] == "B") {
							if (table[1][i] != "unassigned") {
								temp1 = std::stoi(table[1][i]);
							}
							else {
								error[errorcount] = "this value has not been assigned yet : 'B' ";
								errorcount++;
								return false;
							}
						}
					}
				}

				if (code[2] == 'C') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "C") {
							if (table[1][i] != "unassigned") {
								temp = std::stoi(table[1][i]);
							}
							else {
								error[errorcount] = "this value has not been assigned yet : 'C' ";
								errorcount++;
								return false;
							}
						}
					}
				}

				if (code[4] == 'C') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "C") {
							if (table[1][i] != "unassigned") {
								temp1 = std::stoi(table[1][i]);
							}
							else {
								error[errorcount] = "this value has not been assigned yet : 'C' ";
								errorcount++;
								return false;
							}
						}
					}
				}
			}//if A ends
			else if (code[0] == 'B') {
			 keep = "B";
				if (code[2] == 'A') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "A") {
							if (table[1][i] != "unassigned")
								temp = std::stoi(table[1][i]);
							else {
								error[errorcount] = "this value has not been assigned yet : 'A' ";
								errorcount++;
								return false;
							}
						}
					}
				}
				if (code[4] == 'A') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "A") {
							if (table[1][i] != "unassigned")
								temp1 = std::stoi(table[1][i]);
							else {
								error[errorcount] = "this value has not been assigned yet : 'A' ";
								errorcount++;
								return false;
							}
						}
					}
				}
				if (code[2] == 'C') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "C") {
							if (table[1][i] != "unassigned")
								temp = std::stoi(table[1][i]);
							else {
								error[errorcount] = "this value has not been assigned yet : 'C' ";
								errorcount++;
								return false;
							}
						}
					}
				}
				if (code[4] == 'C') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "C") {
							if (table[1][i] != "unassigned")
								temp1 = std::stoi(table[1][i]);
							else {
								error[errorcount] = "this value has not been assigned yet : 'C' ";
								errorcount++;
								return false;
							}
						}
					}
				}

			}//if B end
			else if (code[0] == 'C') {
			 keep = "C";
				if (code[2] == 'B') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "B") {
							if (table[1][i] != "unassigned")
								temp = std::stoi(table[1][i]);
							else {
								error[errorcount] = "this value has not been assigned yet : 'B' ";
								errorcount++;
								return false;
							}
						}
					}
				}
				if (code[4] == 'B') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "B") {
							if (table[1][i] != "unassigned")
								temp1 = std::stoi(table[1][i]);
							else {
								error[errorcount] = "this value has not been assigned yet : 'B' ";
								errorcount++;
								return false;
							}
						}
					}
				}
				 if (code[2] == 'A') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "A") {
							if (table[1][i] != "unassigned")
								temp = std::stoi(table[1][i]);
							else {
								error[errorcount] = "this value has not been assigned yet : 'A' ";
								errorcount++;
								return false;
							}
						}
					}
				}
				if (code[4] == 'A') {
					for (int i = 0; i < 3; i++)
					{
						if (table[0][i] == "A") {
							if (table[1][i] != "unassigned")
								temp1 = std::stoi(table[1][i]);
							else {
								error[errorcount] = "this value has not been assigned yet : 'A' ";
								errorcount++;
								return false;
							}
						}
					}
				}

			}//if c end
			if (code[3] == '*')
				tempVar = temp * temp1;
			if (code[3] == '/')
				tempVar = temp * temp1;
			if (code[3] == '+')
				tempVar = temp + temp1;
			if (code[3] == '-')
				tempVar = temp - temp1;
			
			
			for (int i = 0; i < 3; i++) {
				if(table[0][i]==keep){
					table[1][i]=tempVar;
					updated = true;
					}
			}
			if(!updated){
			table[0][2]=keep;
			table[1][2]= std::to_string(tempVar);
			}
				

			return true;
		}
		bool display_int(std::string code) {
			errorcount = 0;
			if (code[8] == 'A') {
				for (int i = 0; i < 3; i++)
				{
					if (table[0][i] == "A") {
						if (table[1][i] != "unassigned") {
							std::cout << table[1][i] << std::endl;
							return true;
						}else {
						error[errorcount] = "uninitialized variable used";
						errorcount++;
						return false;
						}
					}
					else if (table[0][i] == "B");
					else if (table[0][i] == "C");
					else {
						error[errorcount] = "uninitialized variable used";
						errorcount++;
						return false;
					}
				}
				
			}
			else if (code[8] == 'B') {
				for (int i = 0; i < 3; i++)
				{
					if (table[0][i] == "B") {
						if (table[1][i] != "unassigned") {
							std::cout << table[1][i] << std::endl;
							return true;
						}
						else {
							error[errorcount] = "uninitialized variable used";
							errorcount++;
							return false;
						}
					}
					else if (table[0][i] == "A");
					else if (table[0][i] == "C");
					else{
						error[errorcount] = "uninitialized variable used";
						errorcount++;
						return false;
					}
				}
				
			}
			else if (code[8] == 'C') {
				//std::cout << std::stoi(table[1][3]) << std::endl;
				for (int i = 0; i < 3; i++)
				{
					if (table[0][i] == "C") {
						if (table[1][i] != "unassigned") {
							std::cout << table[1][i] << std::endl;
							return true;
						}
						else {
							error[errorcount] = "uninitialized variable used";
							errorcount++;
							return false;
						}
					}
					else if (table[0][i] == "A");
					else if (table[0][i] == "B");
					else {
						error[errorcount] = "uninitialized variable used";
						errorcount++;
						return false;
					}
					
				}
			
			}
			
			
		}
		void display_string(std::string code) {
			std::cout << code.substr(9, code.size() - 11)<<std::endl;
		}	
	};

}
#endif