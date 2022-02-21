#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

#define Random_Restart_Number 300

bool** Graph;
vector <int> Colors;
vector <int> CurrentState;
vector <int> OptimalState;
vector <int> InitialState;
map <int,int> VertexColor; 
int CurrentValue;
int VertexNum;
int EdgeNum;
int MinValue;

int ColorMaping(int key){
	
	map<int, int>::iterator itr;
	itr = VertexColor.find(key);
	if (itr == VertexColor.end()){
		
		VertexColor.insert(pair<int, int>(key, VertexColor.size()+1));
		return VertexColor.size();
	}
	else
		return itr->second;
		
}

void Display(){
	
	cout << "\n--> OptimalColorNumber = " << MinValue << "\n";
	int NewColor;
	for(int i=0; i<VertexNum; i++){
		
		NewColor = ColorMaping(OptimalState[i]);
		cout << "V" << i+1 << "  " << NewColor << endl;
	}
	

}

int CountColors(vector<int> State)
{
    set<int> Counter;
    for (int i = 0; i < State.size(); i++)
          Counter.insert(State[i]);
    return Counter.size();
}

void SetColors(vector<int> State){
	
	Colors.clear();
    set<int> Counter;
    for (int i = 0; i < State.size(); i++)
          Counter.insert(State[i]);	
          
	set<int, greater<int> >::iterator itr;
    
    for (itr = Counter.begin(); 
         itr != Counter.end(); ++itr) 
    {
        Colors.push_back(*itr);
    }
}

int FindValue(vector<int> State, int ChangedVertex){
	
	int k = State[ChangedVertex];
	for(int i=0; i<VertexNum; i++){
		
		if(Graph[ChangedVertex][i] == 1 && k == State[i]){
			return 99999;
		}
	}
	return CountColors(State);
}
void RandomPermutations(vector <int> &State){ 
	vector<int> tmp;
	int size, index, num;
	
    while(State.size()){
    	size = State.size();
    	index = rand() % size;
    	num = State[index];
    	swap(State[index], State[size - 1]);
    	State.pop_back();
    	tmp.push_back(num);
	}
	State = tmp;
} 

int main(int argc, char* argv[]){
	
	srand(time(0));
	
	char e;
	int v1, v2;
	MinValue = VertexNum;
	
	fstream file(argv[1], ios::in);
	
	file >> VertexNum >> EdgeNum;
	MinValue = VertexNum;
	
	Graph = new bool* [VertexNum];
	for(int i=0; i<VertexNum; i++){
		Graph[i] = new bool [VertexNum];
		memset(Graph[i], 0, VertexNum);
		InitialState.push_back(i+1);	
	}
	
	for(int i=0; i<EdgeNum; i++){
		file >> e >>  v1 >> v2;
		Graph[v1-1][v2-1] = 1;
		Graph[v2-1][v1-1] = 1;
	}
	
	int Value;
	
	OptimalState = InitialState;
	cout << "please wait ...\n";
	//Random Restart Hill Climbing algorithm
	for(int c=0; c<Random_Restart_Number; c++){
		
		CurrentState = InitialState;
		RandomPermutations(CurrentState);
		Colors = InitialState;
		CurrentValue = VertexNum;
			
		for(int p=0; p<300; p++){
			
			int RandomVertex = rand() % VertexNum;
		
			int k = CurrentState[RandomVertex];
			for(int i=0; i<Colors.size(); i++){
	
				if(Colors[i] != k){
		
					CurrentState[RandomVertex] = Colors[i];
					Value = FindValue(CurrentState, RandomVertex);
					if(Value < CurrentValue){
						CurrentValue = Value;
						SetColors(CurrentState);
						break;
					}
				}
				if(i == Colors.size() - 1){
					CurrentState[RandomVertex] = k;
				}
			}
		}
		if(CurrentValue < MinValue){
			OptimalState.clear();
			OptimalState = CurrentState;
			MinValue = CurrentValue;
		
		}
	}
	
	Display();	
	return 0;
}
