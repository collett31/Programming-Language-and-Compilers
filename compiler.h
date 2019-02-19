#pragma once
#ifndef COMPILERCODE
#define COMPILERCODE
#include <string>
namespace compilerNamespace
{

	class compiler
	{
	public:
		compiler()
		{
			size = 0; // initialize the size before the progrm runs each time
			errorcount = 0; //initialize the size or your error count before you begin
		}
		bool compile()
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
					if (code[i].substr(code[i].length()-1,1) != ";")
					//if (code[i].back() != ';') // check whether it ends correctly
					//if (code[i].substr(code[i].;ength(),1) != ';')
					{
						error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement, ';' missing";
						errorcount = errorcount + 1;// add to the error count once an error is made

					}
					if (code[i].substr(code[i].length()-2,1) != "\"")
					{
						error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement, ';' missing";
						errorcount = errorcount + 1;// add to the error count once an error is made

					}
					if(code[i].substr(8,1) != "\""){
						error[errorcount] = "Line # " + std::to_string(i + 1) + ": Incomplete display statement, \" missing";
						errorcount = errorcount + 1;// add to the error count once an error is made
	
					}
				}
			}
		}
	};

}
#endif
