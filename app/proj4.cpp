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

	int count = 0;

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
		wtemp = wrdQueue.front();
		// what I want to do is cycle through to see if s2 shows up and if it doesn't then check to see if 
		//   the cycle contains any real words and try them. 
			for ( int w = 0 ; w < 26 ; w++) {
				wtemp[numCharAdj] = 'a' + w;
				if(path.find(wtemp) != path.end()) { 
				}
				else if (wtemp == s2) {
					path.emplace(wtemp, wrdQueue.front());
					wrdQueue.push(wtemp);
					wrdQueue.pop();
					break;
				}
				else if (words.contains(wtemp)) { 
					if (wtemp[numCharAdj] == s2[numCharAdj]) {
						path.emplace(wtemp, wrdQueue.front());
						wrdQueue.push(wtemp);
						break;	
					}
					else {
						wrdQueue.push(wtemp);
					}
					
				}	// end if an actual word
				else if (w==25) {
					adjChar.push(numCharAdj);
					wrdQueue.push(wrdQueue.front());
				}
			}	// end for loop
	if(wtemp == s2){
		std::cout<<"s2 acheived. break"<<std::endl;
		break;
	}
		adjChar.pop();
		std::string val=wrdQueue.front();

		wrdQueue.pop();
		// val is previous and wrdQueue.front() is the current word
		
		path.emplace(wrdQueue.front(), val);

	}	// end while !adjChar.isEmpty()
	
	stk.push(temp);

	while(path.at(temp) != s1) {	// 
		append = path.at(temp);
		count = 0;
		std::string beforeVal = path.at(append);
		std::string curWord = wrdQueue.front();
		std::cout<<"trying to fix emplacemtn. wrdQueue.front(): "<<curWord<<" and path.at(val): "<<beforeVal<<std::endl;
		for( int i = 0; i < s2.length(); i++) {
			if ( curWord[i] != beforeVal[i] ) {
				count++;
			}
			
		}
		std::cout<<"this is temp: "<<temp <<" this is what's before temp: "<<path.at(temp)
			<<" and this is what's before that: "<<path.at(append)<<std::endl;

		if ( count == 1 ) {
			std::cout<<"count == 1"<<std::endl;
			if(path.at(append) == s1) {
				std::cout<<"path.at(append)==s1  break!"<<std::endl;
				break;
			}
			temp = path.at(append);	
		}
		std::cout<<"add append to stack. \n"<<std::endl;
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

