#include<stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char program[10000];
int i=0;
int A,B,C;

bool end1 = false;

void escape_space(){
	while(program[i] == ' '){
		i++;
	}
}

bool check_for(char st[]){
	for(int j=0;st[j]!=0;j++){
		if(st[j] != program[i]){
			return false;
		}
		i++;
	}
	escape_space();
	return true;
}
int get_value(char v,int value){

	if(v =='A'){
		return A;
	}else if(v =='B'){
		return B;
	}else if(v =='C'){
		return C;
  }else if(v=='1'){
        return value;
  }
}

int get_exp_value(char left,char right,char operator1){

	int left_val = get_value(left,'0');
	int right_value = get_value(right,'0');
	if(operator1=='+'){
		return left_val+right_value;
	}else if(operator1=='-'){
		return left_val-right_value;
	}else if(operator1=='*'){
		return left_val*right_value;
	}else if(operator1=='/'){
		return left_val/right_value;
	}
	return 0;
}
int read_value(){
    int val=0;
    while(program[i] >= '0'&&program[i] <= '9'){
        val = val*10+(program[i]-'0');
        i++;
    }
    return val;
}
bool check_digit(){
    if(program[i]>='0'&&program[i]<='9'){
        return true;
    }
    return false;
}


bool check_valid_variable(){
	escape_space();
	if(program[i]=='A'||program[i]=='B'||program[i]=='C'){
		return true;
	}else{
		return false;
	}
}

bool check_operator(){
	escape_space();
	if(program[i]=='-'||program[i]=='+'||program[i]=='*'||program[i]=='\\'){
		return true;
	}else{
		return false;
	}
}


bool statement(){
	char result;
	if(check_valid_variable()){
		result=program[i];
		i++;
		escape_space();
	}else if(check_for("end")){
		end1=true;
		return true;
	}else if(check_for("input")){
		if(check_valid_variable()){
			int	v;
			scanf("%d",&v);
			if(program[i]=='A'){
				A=v;
			}else if(program[i]=='B'){
				B=v;
			}else{
				C=v;
			}
			i++;
			escape_space();
            	if(program[i]==';'){
                    i++;
                    return true;
                }else{
                    return false;
                }
		}else{
			return false;
		}
	}else if(check_for("display")){
		
		if(check_valid_variable()){
			int v=get_value(program[i],'0');
			printf("%d\n",v);
			i++;
		}else if(program[i]=='"'){
			i++;
			while(program[i]!='"'){
				printf("%c",program[i]);
				i++;
			}
            printf("\n");
			i++;
		}
        escape_space();
        if(program[i]==';'){
                    i++;
                    return true;
                }else{
                    return false;
                }        
	}else{
		return false;
	}
	if(program[i]=='='){
		i++;
	}else{
		return false;
	}
    int value;
    char left_var='0';
	if(!check_valid_variable()){
        if(check_digit()){
            value=read_value();
            left_var='1';
        }else{
            return false;
        }
	}
    if(left_var=='0'){
        left_var=program[i];
        i++;
    }
    escape_space();
	if(program[i]==';'){
		i++;
		escape_space();
		if(result=='A'){
			A=get_value(left_var,value);
		}else if(result=='B'){
			B=get_value(left_var,value);
		}else if(result=='C'){
			C=get_value(left_var,value);
		}
	}else{
		escape_space();
		if(check_operator()){
			char operator1=program[i];
			i++;
			escape_space();
			if(!check_valid_variable()){
				return	false; 
			}
			char right_var=program[i];
                i++;
			escape_space();
			if(program[i]==';'){
				i++;
				escape_space();
				if(result=='A'){
					A=get_exp_value(left_var,right_var,operator1);
				}else if(result=='B'){
					B=get_exp_value(left_var,right_var,operator1);
				}else if(result=='C'){
					C=get_exp_value(left_var,right_var,operator1);
				}
			}else{
				return false;
			}
		}else{
			return false;
		}
    }
		return true;
}


bool check_expressions(){
	while(true){
		escape_space();
		if(!statement()){
			return false;
		}
		if(end1==true){
			return true;
		}
	}
	return true;
}

void print_error(){
	printf("error\n");
}



int main(){
    string line;
    ifstream myfile ("example.txt");
    myfile.is_open();
    getline (myfile,line);
    strcpy(program, line.c_str()); 
    //program="begin display \"123\"; A=10; B=20; display B; C=A+B; display C; end";
	if(!check_for("begin")){
		print_error();
		return 0;
	}
	if(!check_expressions()){
        printf(" %d ",i);
		print_error();
		return 0;
	}
	return 0;

}
