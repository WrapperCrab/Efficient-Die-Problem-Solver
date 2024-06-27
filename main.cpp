//main.cpp
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <numeric>

//function prototypes
void do_efficiency_problem();
int find_most_efficient_method(int,int);
void do_expected_rolls_problem();

int get_user_num_sides();
int get_user_numerator();
int get_user_denominator(int);
int get_user_scale_factor();

int num_rolls(int,int,int v=1);
float prob_retry(int,int,int v=1);
float expected_num_rolls(int,int,int v=1);

int main(){
	bool keepgoing = true;
	while (keepgoing){
		std::cout << "What would you like to do?\n";
		std::cout << "1) Given a die and a probability, find most efficient method\n";
		std::cout << "2) Given a die, a probability, and a scale factor, find expected number of rolls\n";
		std::cout << "0) no\n";
		std::string response = "0";
		std::cin >> response;

		if (response.compare("0")==0){
			std::cout << "goodbye";
			keepgoing = false;
		}else if (response.compare("1")==0){
			do_efficiency_problem();
		}else if (response.compare("2")==0){
			do_expected_rolls_problem();
		}else{
			std::cout << "Error: You must type the number for one of the options.\n\n";
		}
	}
}

void do_efficiency_problem(){
	//get user input
	int n = get_user_num_sides();
	if (n==-1){return;}
	int a = get_user_numerator();
	if (a==-1){return;}
	int b = get_user_denominator(a);
	if (b==-1){return;}
	//reduce the fraction
	int gcd = std::gcd(a,b);
	a = a/gcd;
	b = b/gcd;
	//find the solution
	int v = find_most_efficient_method(n,b);
	int r = num_rolls(n,b,v);
	float q = prob_retry(n,b,v);
	float Ex = expected_num_rolls(n,b,v);
	//output answer to user
	std::cout<<"\nThe best method to simulate a probability of "<<a<<"/"<<b<<
		" with a die of "<<n<<" sides is to roll the die "<<r<<" times to generate a "<<
		r<<"-digit result in base "<<n<<".\n\n";
	std::cout<<"If 1<=result<="<<a*v<<" then it is a success!\n";
	std::cout<<"If "<<a*v<<"<result<="<<b*v<<" then it is a failure.\n";
	if (b*v!=pow(n,r)){
		std::cout<<"If "<<b*v<<"<result<="<<pow(n,r)<<" you must retry the simulation.\n";
	}
	std::cout<<"\n";
	std::cout<<"With this method, the Expected number of rolls is "<<Ex<<
		" and the probability to retry in a single attempt is "<<q<<"\n\n";
}
int find_most_efficient_method(int n,int b){
	//returns a value v which represents the most efficient scaling factor for simulating with the given values
	//calculate initial try
	int r1 = num_rolls(n,b);
	int v1 = floor(pow(n,r1)/b);
	float Ex1 = expected_num_rolls(n,b,v1);
	float q1 = prob_retry(n,b,v1);
	//initialize values to store best strategy
	int bestV = v1;
	float bestEx = Ex1;
	float bestQ = q1;
	int rUpperBound = floor(bestEx);
	int r=r1;//this is the r we are testing at each step of the while loop
	while (true){
		//this while loop is just a fancy for loop with dynamic bound, so update r and check bound
		r++;
		if (r>rUpperBound){
			break;
		}
		//calculate values for this r
		int v = floor(pow(n,r)/b);
		float Ex = expected_num_rolls(n,b,v);
		float q = prob_retry(n,b,v);
		//update the saved values if this one is better
		if (Ex<bestEx || (Ex==bestEx && q<bestQ)){
			bestV = v;
			bestEx = Ex;
			bestQ = q;
			rUpperBound = floor(bestEx);
		}
	}
	return bestV;
}
void do_expected_rolls_problem(){
	//get user input
	int n = get_user_num_sides();
	if (n==-1){return;}
	int a = get_user_numerator();
	if (a==-1){return;}
	int b = get_user_denominator(a);
	if (b==-1){return;}
	int v = get_user_scale_factor();
	if (v==-1){return;}
	//reduce the fraction
	int gcd = std::gcd(a,b);
	a = a/gcd;
	b = b/gcd;
	//find the solution
	int r = num_rolls(n,b,v);
	float q = prob_retry(n,b,v);
	float Ex = expected_num_rolls(n,b,v);
	//output answer to user
	std::cout<<"\nIn a simulation of "<<a<<"/"<<b<<" with a die of "<<n<<" sides and a scale factor of "<<v<<
		" you roll the die "<<r<<" times to generate a "<<
		r<<"-digit result in base "<<n<<".\n\n";
	std::cout<<"If 1<=result<="<<a*v<<" then it is a success!\n";
	std::cout<<"If "<<a*v<<"<result<="<<b*v<<" then it is a failure.\n";
	if (b*v!=pow(n,r)){
		std::cout<<"If "<<b*v<<"<result<="<<pow(n,r)<<" you must retry the simulation.\n";
	}
	std::cout<<"\n";
	std::cout<<"With this method, the Expected number of rolls is "<<Ex<<
		" and the probability to retry in a single attempt is "<<q<<"\n\n";
}

//user input functions
int get_user_num_sides(){
	//ask user for number of sides on die
	int n;
	std::cout << "Enter the number of sides on your die: ";
	std::cin >> n;
	if (std::cin.fail()){
		std::cout<<"Error: Your die must have an integer number of sides.\n\n";
		std::cin.clear();
		std::cin.ignore(100,'\n');
		return -1;
	}
	if (n<2){
		std::cout << "Error: Your die must have at least 2 sides\n\n";
		return -1;
	}
	return n;
}
int get_user_numerator(){
	//ask user for numerator of wanted probability (integer)
	int a;
	std::cout << "Enter the numerator of your wanted probability: ";
	std::cin >> a;
	if (std::cin.fail()){
		std::cout<<"Error: Your numerator must be an integer.\n\n";
		std::cin.clear();
		std::cin.ignore(100,'\n');
		return -1;
	}
	if (a<0){
		std::cout << "Error: Your numerator must be at least 0.\n\n";
		return -1;
	}
	return a;
}
int get_user_denominator(int a){
	//ask user for denominator of wanted probability (integer)
	int b;
	std::cout << "Enter the denominator of your wanted probability: ";
	std::cin >> b;
	if (std::cin.fail()){
		std::cout<<"Error: Your denominator must be an integer.\n\n";
		std::cin.clear();
		std::cin.ignore(100,'\n');
		return -1;
	}
	if (b==0){
		std::cout << "Error: Your denominator cannot be 0.\n\n";
		return -1;
	}
	if (b<a){
		std::cout << "Error: Your denominator must be at least as big as your numerator.\n\n";
		return -1;
	}
	return b;
}
int get_user_scale_factor(){
	//ask user for scale factor
	int v;
	std::cout << "Enter the scale factor you'd like to use: ";
	std::cin >> v;
	if (std::cin.fail()){
		std::cout<<"Error: Your scale factor must be an integer.\n\n";
		std::cin.clear();
		std::cin.ignore(100,'\n');
		return -1;
	}
	if (v<1){
		std::cout << "Error: Your die must be at least 1.\n\n";
		return -1;
	}
	return v;
}

//calculation funcs
int num_rolls(int n,int b,int v){
	//calculates the number of rolls for a single simulation attempt with the given values
	int r = ceil(log(v*b)/log(n));
	return r;
}
float prob_retry(int n,int b,int v){
	//calculates the probability of needing to retry after a single simulation attempt with the given values
	int r = num_rolls(n,b,v);
	float q = 1-(b*v/pow(n,r));
	return q;
}
float expected_num_rolls(int n,int b,int v){
	//calculates the expected number of rolls when completing a simulation with the given values
	int r = num_rolls(n,b,v);
	float Ex = r*pow(n,r)/(v*b);
	return Ex;
}
