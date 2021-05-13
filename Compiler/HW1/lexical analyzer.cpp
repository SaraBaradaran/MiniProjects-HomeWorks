#include<iostream>
#include<fstream>
#include<string>

using namespace std;


bool ID(string token){
	
	char ch = token[0];
	if((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')){
		for(int i=1; i<token.size(); i++){
		
			ch = token[i];
			if(!((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch >= '0' && ch <= '9')))
				return 0;
		}
	}
	else
		return 0;	
	
	return 1;

}
bool INT(string token){
	
	char ch = token[0];
	if((ch == '+' || ch == '-')){
		
		ch = token[1];
		if((ch >= '0' && ch <= '9')){
			
			for(int i=2; i<token.size(); i++){
			
				ch = token[i];
				if(!(ch >= '0' && ch <= '9'))
					return 0;
			}
		}
		else
			return 0;
	}	
	else
		return 0;
		
	return 1;
}
bool FLOAT(string token){
	
	char ch = token[0];
	if(ch == '+' || ch == '-'){
		
		ch = token[1];
		if(ch >= '0' && ch <= '9'){
			
			int i= 2;
			for(i; token[i] >= '0' && token[i] <= '9'; i++);
			
			ch = token[i];
			if(ch == '.'){
				
				ch = token[++i];
				
				if(ch == 'e' || ch == 'E'){
					
					ch = token[++i];
					if(ch == '+' || ch == '-'){
						
						ch = token[++i];
						if(ch >= '0' && ch <= '9'){
							
							for(++i; token[i] >= '0' && token[i] <= '9'; i++);
							
								ch = token[i];
							if(ch == '\0')	
								return 1;
							else
								return 0;	
						}
						else
							return 0;
					}
					else
						return 0;	
				}
				else
					return 0;
			}
			else
				return 0;
		}
		else
			return 0;
	}	
	else
		return 0;
		
	return 1;
}

bool OPERATOR(string token){
	
	
	char ch = token[0];
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
		
		ch = token[1];
		if(ch == '\0')
			return 1;
		else
			return 0;	
	}	
	else if(ch == '>' || ch == '!' || ch == '<'){
		
		ch = token[1];
		if(ch == '\0')
			return 1;
			
		else if(ch == '='){
			ch = token[2];
			
			if(ch == '\0')
				return 1;
			else
				return 0;
		}
		else
			return 0;
			
	}
	else if(ch == '=' || ch == '&' || ch == '|'){
				
		if( ch == token[1] ){
			
			ch = token[2];
			if(ch == '\0')
				return 1;
			else
				return 0;
		}
		else
			return 0;	
	}
	else
		return 0;
	
}
bool KEYWORD(string token){
	string keywords[9] = {"int","char","return","read","write","break","if","else","while"};	
	for(int i=0; i<9 ; i++){
		if(token == keywords[i])
			return 1;
	}
	return 0;
}


int main(){
	fstream input;
	bool res;
	input.open("input.txt" , ios::in);
	string token;
	input >> token;
	
	while(!input.eof()){
		
		if(res = KEYWORD(token))
			cout << "< keyword , " << token << " >\n";
			
		else if(res = ID(token))
			cout << "< id , " << token << " >\n";
			
		else if(res = FLOAT(token))
			cout << "< float , " << token << " >\n";
		
		else if(res = INT(token))
			cout << "< int , " << token << " >\n";
		
		else if(res = OPERATOR(token))
			cout << "< operator , " << token << " >\n";
		else
			cout << "< invalid_token , " << token << " >\n";

		input >> token;	
	}
	
	
}


