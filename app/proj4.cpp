#include "proj4.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}


// You probably want to change this function.
std::string convert(std::string s1, std::string s2, const WordSet & words)
{
	std::queue<std::string> wrdQueue;
	std::string solution;
	std::queue<int> adjChar;

	std::cout<<"\nstart of solution: "<< solution<< " \n" << std::endl;
	std::cout<<"This is what s1 needs to turn into: "<< s2 << std::endl;

	// compare strings
	std::cout<<"s1: "<<s1 <<" s2: "<<s2 <<std::endl;
	for(int i = s1.length()-1; i >= 0; i--) {
		if( s1[i] == s2[i]) {
			std::cout<<"s1: "<< s1 << " and s2: " << s2 << " share a char at: "<< i << std::endl;
		}
		else {
			adjChar.push(i);
		}
	}

wrdQueue.push(s1);
	while(!adjChar.empty()) {
		int temp = adjChar.front();
		std::cout<<"\nchars that need adjusting: "<< temp << std::endl;;
		std::string wtemp = wrdQueue.front(); 
			for ( int w = 0 ; w < 26 ; w++) {
				wtemp[temp] = 'a' + w;
				std::cout<<"wtemp = "<<wtemp<<"\t";
				if (wtemp == s2) {
					std::cout<<"\nTHIS IS CORRECT!!!! wtemp: " << wtemp <<std::endl;
					wrdQueue.push(wtemp);
					break;
				}
			}

// adds new string to solution
		if(solution == ""){
			solution = wrdQueue.front();
			wrdQueue.pop();
		}
		solution += " --> " + wtemp;
		adjChar.pop();
	}

	std::cout<<"\n**********-------------************: "<<solution<<std::endl;

	return solution;  // stub obviously 
}
