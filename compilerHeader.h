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
			}
			bool Compile()
			{
				if (size < 3)//check to see if the code has 3 or more lines to include begin statement list and end statements
				{
					error[errorcount] = "incomplete source code";
					errorcount = errorcount + 1;// add to the error count once an error is made

				}
				else if (code[size - 1] != "end")// check to see if the program ends with an end statement
				{
					error[errorcount] = "last line should be [end]";
					errorcount = errorcount + 1;// add to the error count once an error is made

				}
				if (code[0] != "begin")// check to see if the program begins with an begin statement
				{
					error[errorcount] = "first line should be [begin]";
					errorcount = errorcount + 1;// add to the error count once an error is made

				}
				if (size >= 3)
					statementcompile();
				if (errorcount == 0)
					return true;
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
		private:
			std::string code[50]; //need an array to hold the string values, array you always need size
			int size; // code array size
			std::string error[50];// create and error array
			int errorcount;// error array size
			
			
			void statementcompile()
			{
				int i;
				for (i = 1; i < size - 1; i = i + 1)
				{
					if (code[i].substr(0, 7) == "display")//check if the display statement has keyword display there
					{
						if (code[i].length() < 11) // check whether there is actually something to display based on the length
						{
							error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement";
							errorcount = errorcount + 1;// add to the error count once an error is made

						}
						if (code[i].substr(code[i].length() - 1, 1) != ";")
							//if (code[i].back() != ';') // check whether it ends correctly
							//if (code[i].substr(code[i].;ength(),1) != ';')
						{
							error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement, ';' missing";
							errorcount = errorcount + 1;// add to the error count once an error is made

						}
						if (code[i].substr(code[i].length() - 2, 1) != "\"")
						{
							error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement, ';' missing";
							errorcount = errorcount + 1;// add to the error count once an error is made

						}
						if (code[i].substr(8, 1) != "\"") {
							error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement, \" missing";
							errorcount = errorcount + 1;// add to the error count once an error is made

						}
					}
				}
			}
	};
	class Parse : public Compiler
	{
	public:

		void escape_space() {
			while (programC[i] == ' ') {
				i++;
			}
		}

		int get_value(char v, int value) {

			if (v == 'A') {
				return A;
			}
			else if (v == 'B') {
				return B;
			}
			else if (v == 'C') {
				return C;
			}
			else if (v == '1') {
				return value;
			}
		}

		void get_line() {
			program[i] = readL.get_line(i);
			strcpy_s(programC, program[i].c_str());
		}

		int get_exp_value(char left, char right, char operator1) {

			int left_val = get_value(left, '0');
			int right_value = get_value(right, '0');
			if (operator1 == '+') {
				return left_val + right_value;
			}
			else if (operator1 == '-') {
				return left_val - right_value;
			}
			else if (operator1 == '*') {
				return left_val * right_value;
			}
			else if (operator1 == '/') {
				return left_val / right_value;
			}
			return 0;
		}

		bool check_for(char st[]) {
			for (int j = 0; st[j] != 0; j++) {
				if (st[j] != programC[i]) {
					return false;
				}
				i++;
			}
			escape_space();
			return true;
		}
		int read_value() {
			int val = 0;
			while (programC[i] >= '0'&&programC[i] <= '9') {
				val = val * 10 + (programC[i] - '0');
				i++;
			}
			return val;
		}
		bool check_digit() {
			if (programC[i] >= '0'&&programC[i] <= '9') {
				return true;
			}
			return false;
		}
		bool check_valid_variable() {
			escape_space();
			if (programC[i] == 'A' || programC[i] == 'B' || programC[i] == 'C') {
				return true;
			}
			else {
				return false;
			}
		}

		bool check_operator() {
			escape_space();
			if (programC[i] == '-' || programC[i] == '+' || programC[i] == '*' || programC[i] == '\\') {
				return true;
			}
			else {
				return false;
			}
		}

		bool statement() {
			char result;
			if (check_valid_variable()) {
				result = programC[i];
				i++;

			}

		}

	private:
		std::string program[10000];
		char programC[10000];
		int i = 0;
		int A, B, C;
		Compiler readL;
		bool end1 = false;
	};

}
#endif

