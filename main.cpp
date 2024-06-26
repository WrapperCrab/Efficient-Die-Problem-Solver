//main.cpp
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <numeric>

//function prototypes
void do_efficiency_problem();
int find_most_efficient_method(int,int);
int num_rolls(int,int,int v=1);
float prob_retry(int,int,int v=1);
float expected_num_rolls(int,int,int v=1);

int main(){
	bool keepgoing = true;
	while (keepgoing){
		std::cout << "What would you like to do?\n";
		std::cout << "1) Given a die and a probability, find most efficient method\n";
		// std::cout << "2) Given a die and an unsimplified probability, find expected number of rolls\n";
		std::cout << "0) no\n";
		std::string response;
		std::cin >> response;

		if (response.compare("0")==0){
			std::cout << "goodbye";
			keepgoing = false;
		}else if (response.compare("1")==0){
			do_efficiency_problem();
		// }else if (response.compare("2")==0){
		// 	do_expected_rolls_problem();
		}else{
			std::cout << "try again\n";
		}
	}
}

void do_efficiency_problem(){
	//!!!Add some input sanitization and better error codes
	//ask user for number of sides on die
	int n;
	std::cout << "Enter the number of sides on your die: ";
	std::cin >> n;
	if (n<2){
		std::cout << "No\n";
		return;
	}
	//ask user for numerator of wanted probability (integer)
	int a;
	std::cout << "Enter the numerator of your wanted probability: ";
	std::cin >> a;
	if (a<0){
		std::cout << "No\n";
		return;
	}
	//ask user for denominator of wanted probability (integer)
	int b;
	std::cout << "Enter the denominator of your wanted probability: ";
	std::cin >> b;
	if (b<1 || a>b){
		std::cout << "No\n";
		return;
	}
	//reduce the fraction
	int gcd = std::gcd(a,b);
	a = a/gcd;
	b = b/gcd;

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
	std::cout<<"Otherwise, you must retry the simulation.\n\n";
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
		//this while loop is a fancy for loop, so update r and check bound
		r++;
		if (r>=rUpperBound){
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
// void do_expected_rolls_problem(){
// 	//ask user for number of sides on die
// 	int sides;
// 	std::cout << "Enter the number of sides on your die: ";
// 	std::cin >> sides;
// 	if (sides<2){
// 	std::cout << "no\n";
// 	break;
// 	}
// 	//ask user for denominator of wanted probability (integer)
// 	int b;
// 	std::cout << "Enter the denominator of your wanted probability: ";
// 	std::cin >> b;
// 	if (b<1){
// 	std::cout << "no\n";
// 	break;
// 	}
// 	//we have what we need. Let's calculate the expected number of rolls
// 	float expected = expectedRolls(sides,b,1);
// 	float prob = probReroll(sides,b,1);
// 	std::cout << "the expected number of rolls is "<< expected << "\n";
// 	std::cout << "the probability for reroll is "<< prob << "\n";
// }
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
