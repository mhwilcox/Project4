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

	std::string append;
	std::stack<std::string> stk;

	int count = 0;

	path.emplace(s1,"");

	// compare strings
	for(int i = s1.length()-1; i >= 0; i--) {
		if( s1[i] == s2[i]) {
		}
		else {
			adjChar.push(i);
		}
	}

wrdQueue.push(s1);
	std::string wtemp = wrdQueue.front();

	while(wtemp != s2) {	// wtemp != s2
		int numCharAdj = adjChar.front();
		std::string secndWd = wrdQueue.front();
		wtemp = wrdQueue.front();
		wrdQueue.pop();
		// what I want to do is cycle through to see if s2 shows up and if it doesn't then check to see if 
		//   the cycle contains any real words and try them. 
			for ( int w = 0 ; w < 26 ; w++) {
				wtemp[numCharAdj] = 'a' + w;
				
				if(path.find(wtemp) != path.end()) {
				}
				else if (wtemp == s2) {	// if wtemp == s2 then put in in path and break from the loop;
					path.emplace(wtemp, secndWd);
					std::cout<<"!!!****!!!  emplace: "<<wtemp<<", "<<secndWd<<std::endl;
					wrdQueue.push(wtemp);
					break;
				}
				else if (words.contains(wtemp)) { 	// if wtemp is a word enter codeblock
					int check = 0;
					
						for(int i = 0; i<s2.length(); i++){
							if(wtemp[i]!=secndWd[i]){
								check++;
							}
						}

						if (wtemp[numCharAdj] == s2[numCharAdj] && check == 1 ) {	// if wtemp has a char match with s2
							path.emplace(wtemp, secndWd);	//	emplace in path
							std::cout<<"^-^ emplace: "<<wtemp<<", "<<secndWd<<std::endl;
							wrdQueue.push(wtemp);					// and push wtemp back onto wordqueue
							break;	
						}
						else if ( wtemp[numCharAdj] == secndWd[numCharAdj] && check == 1 ) {
							path.emplace(wtemp, secndWd);
							std::cout<<"@  emplace: "<<wtemp<<", "<<secndWd<<std::endl;
							wrdQueue.push(wtemp);
							adjChar.push(numCharAdj);
						}
						else if ( check == 1){
							wrdQueue.push(wtemp);
						}
								
				}	// end if an actual word
				else if (w==25) {
					adjChar.push(numCharAdj);
					wrdQueue.push(secndWd);
					break;
				}
			}	// end for loop

	if(wtemp == s2){
		break;
	}
		adjChar.pop();
		adjChar.push(numCharAdj);
		wrdQueue.push(secndWd);
		if(path.find(wtemp) == path.end()) {
			int check = 0;
			for(int i = 0; i<s2.length(); i++){
				if(wrdQueue.front()[i]!=secndWd[i]){
					check++;
				}
			}
			if(wrdQueue.front() != secndWd && check==1){ 
				path.emplace(wrdQueue.front(), secndWd);
				std::cout<<"## emplace: "<<wrdQueue.front()<<", "<< secndWd<<std::endl;
			}
		}	// not currently in path
	}	// end while !adjChar.isEmpty()
	


		std::string curWord = s2;
	// create stack for solution set
	while(curWord != s1) {	// curWord = furthest right value *starts at s2
		append = path.at(curWord);		// append = value right before temp
		count = 0;
		int check = 0;
		std::string beforeVal = path.at(append);	// beforeVal = value before append / 2 left from temp
		std::cout<<"curWord: "<<curWord<< ", append: "<<append<<", and beforeVal: "<<beforeVal<<std::endl;

		if(!stk.empty()){std::cout<<"stk.top(): "<<stk.top()<<std::endl;}
		else if ( append == s1) {
			stk.push(curWord);
			break;
		}
		for( int i = 0; i < s2.length(); i++) {
			if ( curWord[i] != beforeVal[i] ) {
				count++;
			}
			if(append == s1 && stk.top()[i] != s1[i]) {
				std::cout<<"s1 check"<<std::endl;
				check++;
			}
			else if( !stk.empty() && curWord[i] != stk.top()[i]) {
				check++;
			}
		}

	std::cout<<"count: "<<count <<std::endl;
	if(append == s1) {
		std::cout<<"!!!!!!!!!!!! append == s1"<<std::endl;
	}
if(!stk.empty()){	std::cout<<"check: "<<check<<std::endl;	}
		if ( append == s1 && check == 1) {
			std::cout<<"s1 break;"<<std::endl;
			break;
		}
		else if (append == s1) {
			stk.push(curWord);
			std::cout<<"s1 push then break;\n"<<std::endl;
			break;
		}
		if ( count == 1 && check == 1 ) {
			std::cout<<"stk(curWord) curWord = beforeVal"<<std::endl;
			stk.push(curWord);
			std::cout<<"curWord: "<<curWord<<std::endl;
			while(check<=1) {
				check = 0;
				for(int t = 0; t<s1.length(); t++){
					if(curWord[t] != path.at(curWord)[t]) {
						check++;
					}
				}
				if(check==2) {
					break;
				}
				curWord = path.at(curWord);
				std::cout<<"while loop"<<std::endl;
			}
			curWord = beforeVal;
		}
		else if (check >1) {
			curWord = append;
		}
		else {
			std::cout<<"push: "<<curWord<<std::endl;
			stk.push(curWord);
			curWord = append;
		}
	}
	stk.push(s1);
std::cout<<"\n******\nThis is the size of the solution: "<<stk.size()<<std::endl;
	solution += s1;
	stk.pop();
	// put the words in the stack in the solution string for return
	while (!stk.empty()) {
		solution += " --> " + stk.top();
		stk.pop();		
	}

	while(!wrdQueue.empty()) {
		wrdQueue.pop();
	}
	
		path.clear();
std::cout<<"solution:  "<<solution<<std::endl;
	return solution;  // return solution
}

