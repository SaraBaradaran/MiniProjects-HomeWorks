#include<iostream>
#include<stack>
using namespace std;

string str;
int la = 0;

stack<char> ParsStack;

int Index(char symbol){
	
	switch(symbol){
		case 'a':
			return 0;
		case 'S':
			return 0;
		case 'b':
			return 1;
		case 'A':
			return 1;
		case 'c':
			return 2;
		case 'B':
			return 2;
		case '$':	
			return 3;
	}		
}

void StackPush(char no,string rules[]){
	
	string s = rules[no-'0'];
 
	for(int i = s.size()-1; i >= 0; i--)
		ParsStack.push(s[i]);
}

void NextChar(){
	
	if(la < str.size()-1){
		la++;
	}
}

bool IsTerminal(char symbol){
	
	if(symbol == '$' || symbol == 'a' || symbol == 'b' || symbol == 'c')
		return 1;
	return 0;	
}
int main(){
	
	
	string rules[6] = {"S$","AcB","aA","","bBS",""};
	char ParsTable[3][4];
	
	for(int i=0; i<3; i++)
		for(int j=0; j<4; j++)
			ParsTable[i][j] = ' ';	

	ParsTable[0][0] = ParsTable[0][2] = '1';
	ParsTable[1][0] = '2';
	ParsTable[1][2] = '3';
	ParsTable[2][1] = '4';
	ParsTable[2][0] = ParsTable[2][2] = ParsTable[2][3] = '5';
	
	
	char terminal[4] = {'a','b','c','$'};
	char noneterminal[3] = {'S','A','B'};
	cout << "parse table :\n\n  | ";
	for(int i=0; i<4; i++)
		cout << terminal[i] << " | ";
	cout << endl;	
		
	for(int i=0; i<3; i++){
		cout << noneterminal[i] << " | ";
		for(int j=0; j<4; j++){
			cout << ParsTable[i][j] << " | ";
		}
		cout << endl;	
	}

	cout << "\nEnter string : \n";
	cin >> str;
	str += '$';
	
	ParsStack.push('$');
	ParsStack.push('S');
	
	char no;
	
	while(1){
		
		
		cout << "LA = " << str[la] << "\tTOP = " << ParsStack.top() << "\t"; 
		if(str[la] == '$'&& ParsStack.top() == '$'){
			cout << "\naccept\n";
			break;
		}
		if(IsTerminal(ParsStack.top())){
			
			if(str[la] == ParsStack.top()){
				cout << "\tmatch\n";
				ParsStack.pop();
				NextChar();	
			}
			else{
				cout << "\nerror\n";
				break;
			}
		}	
		else if(IsTerminal(str[la])){
			
			no = ParsTable[Index(ParsStack.top())][Index(str[la])];
			cout << "\tParsTable [ " << ParsStack.top() << " , " << str[la] << " ] = " << no << endl;
			if(no == ' '){
				
				cout << "error\n";
				break;
			}
			else{
				
				ParsStack.pop();
				StackPush(no, rules);
			}			
		}
		else{
			cout << "\ninvalid character\n";
			break;
		}
	}
}
