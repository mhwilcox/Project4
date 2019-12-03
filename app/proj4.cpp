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
	std::map<std::string, std::string> path;

	std::cout<<"\nstart of solution: "<< solution<< " \n" << std::endl;
	std::cout<<"This is what s1 needs to turn into: "<< s2 << std::endl;

	// compare strings
	std::cout<<"s1: "<<s1 <<" s2: "<<s2 <<std::endl;
	for(int i = s1.length()-1; i >= 0; i--) {
		if( s1[i] == s2[i]) {
			std::cout<<"s1: "<< s1 << " and s2: " << s2 << " share a char at: "<< i << std::endl;
		}
		else {
			std::cout<<"\n    char doesn't match at: "<<i<<" pushing to adjChar. "<< std::endl;
			adjChar.push(i);
		}
	}

wrdQueue.push(s1);


	while(!adjChar.empty()) {
		int temp = adjChar.front();
		std::cout<<"\nchar that is being adjusted: "<< temp << std::endl;;
		std::string wtemp = wrdQueue.front();
		// what I want to do is cycle through to see if s2 shows up and if it doesn't then check to see if 
		//   the cycle contains any real words and try them. 
			for ( int w = 0 ; w < 26 ; w++) {
				wtemp[temp] = 'a' + w;
				std::cout<<"wtemp = "<<wtemp<<"\t";
				if (wtemp == s2) {
					std::cout<<"\nTHIS IS CORRECT!!!! wtemp: " << wtemp <<std::endl;
					path.emplace(wtemp, wrdQueue.front());
					wrdQueue.push(wtemp);
					wrdQueue.pop();
					break;
				}
				else if (words.contains(wtemp)) {
					std::cout<<"this is a real word: "<<wtemp<<std::endl;
					path.emplace(wtemp, wrdQueue.front());
					wrdQueue.push(wtemp);
					wrdQueue.pop();
					break;
				}
			}

		adjChar.pop();
	}	// end while !adjChar.isEmpty()

	solution += s1;
std::cout<<"s1 in solution."<<std::endl;
	std::string temp = s1;
	std::string append;
	int x = 0;
	std::cout<<"path size: "<<path.size()<<std::endl;
	while(x < path.size()) {
		std::cout<<"trying temp."<<std::endl;
		append = path.at(temp);
		std::cout<<"append = path.at(temp)"<<std::endl;
		solution += " --> " + append;
		temp = append;
		x++;
		std::cout<<"temp=append & x++ & solution appended. "<<std::endl;
	}

		std::cout<<"\n**********-------------************: "<<solution<<std::endl;

	return solution;  // stub obviously 
}

/*
std::queue<std::string> abcChange(std::string s1, std::string s2, std::queue adjChar) {
	std::queue<std::string> realWords;
	int currChar = adjChar.front();
	std::queue<std::string> path;

	while(!adjChar.empty()) {
		if(path.back() == s2) {
			return path;
		}



	}	// end while !adjChar.empty()


	return path;

}

*/