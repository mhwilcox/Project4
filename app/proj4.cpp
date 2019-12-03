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
	std::string solution = "";
	std::queue<int> adjChar;
	std::map<std::string, std::string> path;

	std::string temp = s2;
	std::string append;
	std::stack<std::string> stk;

	path.emplace(s1,"");


	std::cout<<"size of adjChar: "<<adjChar.size()<<std::endl;
	std::cout<<"size of path: "<<path.size()<<std::endl;
	std::cout<<"side of stk: "<<stk.size()<<std::endl;

std::cout<<"solution at beginning of convert:: "<<solution<<std::endl;

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

	std::string wtemp = wrdQueue.front();

	while(wtemp != s2) {
		int numCharAdj = adjChar.front();
		std::cout<<"\nchar that is being adjusted: "<< numCharAdj << std::endl;
		wtemp = wrdQueue.front();
		std::cout<<"just before for loop: "<<wtemp<<std::endl;
		// what I want to do is cycle through to see if s2 shows up and if it doesn't then check to see if 
		//   the cycle contains any real words and try them. 
			for ( int w = 0 ; w < 26 ; w++) {
				wtemp[numCharAdj] = 'a' + w;
				if(path.find(wtemp) != path.end()) { 
					std::cout<<"word alreay in path:  "<< wtemp <<std::endl;
					std::cout<<"   **********   \n   ******   \n"<<std::endl;
				}
				else if (wtemp == s2) {
					std::cout<<"\nTHIS IS CORRECT!!!! wtemp: " << wtemp <<std::endl;
					path.emplace(wtemp, wrdQueue.front());
					std::cout<<"&&&  this is path.at wtemp: "<<path.at(wtemp)<<std::endl;
					wrdQueue.push(wtemp);
					wrdQueue.pop();
					break;
				}
				else if (words.contains(wtemp)) { 
					if (wtemp[numCharAdj] == s2[numCharAdj]) {
					std::cout<<"wtemp = "<<wtemp<<"\t||  ";
						std::cout<<"This is if chars match from current word to s2."<<std::endl;
						path.emplace(wtemp, wrdQueue.front());
						std::cout<<"\tthis is path.at wtemp: "<<path.at(wtemp)<<std::endl;
						wrdQueue.push(wtemp);
						break;	
					}
					else {
						std::cout<<"\t************* doesn't match char to s2 : "<< wtemp <<std::endl;
						wrdQueue.push(wtemp);
					}
					
				}	// end if an actual word
				else if (w==25) {
					adjChar.push(numCharAdj);
					wrdQueue.push(wrdQueue.front());
					std::cout<<"w==25 and no match to s2."<<std::endl;
				}
			}	// end for loop
	if(wtemp == s2){
		break;
	}
	std::cout<<"adjChar size: "<<adjChar.size();
		adjChar.pop();
	std::cout<<",  after adjChar size: "<<adjChar.size()<<std::endl;
		std::string val=wrdQueue.front();
		std::cout<<"before val: "<<val;
		wrdQueue.pop();
		std::cout<<", curr val: "<<wrdQueue.front()<<std::endl;
		path.emplace(wrdQueue.front(), val);
	std::cout<<"path size: "<<path.size()<<std::endl;
	std::cout<<"   ********   \n  8888888   \n ******* \n\n"<<std::endl;
		
	}	// end while !adjChar.isEmpty()

	//std::cout<<"path size: "<<path.size()<<std::endl;
	
	stk.push(temp);

	//int x = 0;
	while(path.at(temp) != s1) {
		append = path.at(temp);
		std::cout<<"path value: "<< path.at(temp) <<std::endl;
		stk.push(append);
		temp = append;
	}
	stk.push(s1);

	solution += s1;
	stk.pop();

	while (!stk.empty()) {
		solution += " --> " + stk.top();
		std::cout<<"adding to solution: "<<stk.top()<<std::endl;
		stk.pop();
		
	}
	while(!wrdQueue.empty()) {
		wrdQueue.pop();
	}
	std::cout<<"stk size: "<<stk.size()<<std::endl;

		std::cout<<"\n**********-------------************: "<<solution<<std::endl;
		std::cout<<"clearing map, queue, & stack.\n"<<std::endl;

		path.clear();

	return solution;  // return solution
}

