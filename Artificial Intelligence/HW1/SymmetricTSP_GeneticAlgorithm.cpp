#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <ctime>
#include <set>
#include <functional>
#include <bits/stdc++.h>
using namespace std;

#define Generation_Num  100

struct Person{
	vector <int> State;
	double Fitness;
};

inline bool operator<(const Person& lhs, const Person& rhs)
{
  return lhs.Fitness < rhs.Fitness;
}

int Population_Size;
double** DistancesMap;
vector <int> Permutations;
vector <int> No;
vector <double> x;
vector <double> y;
vector <Person> Saved;

void Display(){
	
	cout << "\n--> OptimalDistance = " << Saved[0].Fitness << "\n";
	for(int j=0; j<Saved[0].State.size(); j++){
		cout << Saved[0].State[j] << " ";
	}
	cout << endl;
	
}

bool CompareTwoPersons(Person a, Person b){ 
    return (a.Fitness < b.Fitness); 
} 


void SelectNextGeneration(){
	
	set<Person> s;
	for (int i=0; i<Saved.size(); i++)
    	s.insert(Saved[i]);
	Saved.assign( s.begin(), s.end() );

	sort(Saved.begin(), Saved.end(), CompareTwoPersons);	
	Saved.resize(Population_Size);
	
}

void SavePerson(double Fitness, vector <int> State){ 
	Person p;
	p.State = State;
	p.Fitness = Fitness;
	Saved.push_back(p);
} 

void RandomPermutations(vector <int> a){ 
	Permutations.clear();
	int size, index, num;
	
    while(a.size()){
    	size = a.size();
    	index = rand() % size;
    	num = a[index];
    	swap(a[index], a[size - 1]);
    	a.pop_back();
    	Permutations.push_back(num);
	}

} 

double FindFitness(vector <int> State){
	
	double Fit = 0;
	int Src, Dst;
	int Size = State.size() - 1;
	for(int i=0; i<Size; i++){

		Dst = State[i+1];
		Src = State[i];
		
		Fit += DistancesMap[Src-1][Dst-1];
	}
	Fit += DistancesMap[State[0]-1][State[Size]-1];
	return Fit;
}
void Mutation(vector<int> &State){
	
	float Random;
	int Position1, Position2;
	
	Random = float(rand() % 100)/100; 
	
	if(Random < 0.1){

		Position1 = rand() % State.size();
		Position2 = rand() % State.size();
		iter_swap(State.begin() + Position1, State.begin() + Position2);
	}
	
}
void CrossOver(Person parent1, Person parent2){
	
	int StateSize = parent1.State.size();
	int index = rand() % StateSize;

	Person child;
	
	for(int i=0; i<index; i++){
		
		child.State.push_back(parent1.State[i]);
	}
	vector<int>::iterator it;
	for(int i=0; i<StateSize; i++){
		
		it = find(child.State.begin(), child.State.end(), parent2.State[i]);
		if(it == child.State.end()){
			child.State.push_back(parent2.State[i]);
		}
	}
	Mutation(child.State);
	child.Fitness = FindFitness(child.State);
	SavePerson(child.Fitness, child.State);	
}


int main(int argc, char* argv[]){
	
	srand(time(0));
	
	int n;
	fstream file(argv[1], ios::in);
	
	file >> n;
	
	int city_No;
	double city_X, city_Y;
	
	for(int i=0; i<n; i++){
		
		file >> city_No >> city_X >> city_Y;
		
		No.push_back(city_No);
		x.push_back(city_X);
		y.push_back(city_Y);
	}

	DistancesMap = new double* [n];
	for(int i=0; i<n; i++){
		DistancesMap[i] = new double[n];
	}


	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){

			double k = sqrt(pow((y[j] - y[i]), 2) + pow((x[j] - x[i]), 2));
			DistancesMap[i][j] = DistancesMap[j][i] = k;
		}	 
	}
	//Genetic algorithm

	//set population_size based on the number of cities
	if(n < 70)
		Population_Size = 500;
	else
		Population_Size = 280;
	
	int Fitness;
	vector <int> No_cpy;
	cout << "please wait ...\n";
	//generate initial population
	for(int i=0; i<Population_Size; i++){
		
		No_cpy = No;
		RandomPermutations(No_cpy);
		Fitness = FindFitness(Permutations);
		SavePerson(Fitness, Permutations);

	}
	//sort initial population based on fitness
	sort(Saved.begin(), Saved.end(), CompareTwoPersons);
		
	double BestFitOfPrev1 = 999999, BestFitOfPrev2 = 999999;
	int RandomNum;

	for(int i=0; i<Generation_Num; i++){
	
		for(int k=0; k<Population_Size; k++){
			
			RandomNum = rand() % Population_Size;
			if(RandomNum < Population_Size - k){ //The more fit a person is, the more likely he is to become a parent
				
				for(int j=0; j<Population_Size && k!=j; j++){
					
					RandomNum = rand() % Population_Size;
					if(RandomNum < Population_Size - j){ //The more fit a person is, the more likely he is to become a parent
						CrossOver(Saved[k], Saved[j]);
					}
				}
			}
		}
		
		SelectNextGeneration(); //select the best 400 persons based on their fitness for next generation
		
		if(BestFitOfPrev1 == BestFitOfPrev2 && BestFitOfPrev1 == Saved[0].Fitness)
			break; //Check if the best fit of the population has not changed 3 times, then it may have stopped in global or local optimum
		
		BestFitOfPrev2 = BestFitOfPrev1;
		BestFitOfPrev1 = Saved[0].Fitness;
		
	}
	Display();
	return 0;
	
}

