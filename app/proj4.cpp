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
							wrdQueue.push(wtemp);					// and push wtemp back onto wordqueue
							break;	
						}
						else if ( wtemp[numCharAdj] == secndWd[numCharAdj] && check == 1 ) {
							path.emplace(wtemp, secndWd);
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

		if ( append == s1) {
			stk.push(curWord);
			break;
		}
		for( int i = 0; i < s2.length(); i++) {
			if ( curWord[i] != beforeVal[i] ) {	//checks if we can skip inbetween word
				count++;
			}
			if(append == s1 && stk.top()[i] != s1[i]) {	// check to see if we can skip current word because stk.top is directly before s1
				check++;
			}
			else if( !stk.empty() && curWord[i] != stk.top()[i]) {	// current word has only 1 char different from stk.top
				check++;
			}
		}	// end char comparison  ||  count and check

		// starting to push to stk for solution
		// if append == s1
		if ( append == s1 && check == 1) {	// can skip adding current word to stk
			break;
		}
		else if (append == s1) {	// add current word to stk
			stk.push(curWord);
			break;
		}
		// if append != s1
		if ( count == 1 && check == 1 ) {	// can skip inbetween word(s)
			stk.push(curWord);
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
			}
			curWord = beforeVal;
		}
		else if (check >1) {	// not time to add to stk just yet
			curWord = append;
		}
		else {	// add current word to stk and change current word to the word previous to it
			stk.push(curWord);
			curWord = append;
		}
	}
	stk.push(s1);	// add s1 to stack
	solution += s1;	// s1 added to solution
	stk.pop();	// pop s1 from stack.
	// put the words in the stack in the solution string for return
	while (!stk.empty()) {
		solution += " --> " + stk.top();
		stk.pop();		
	}

	while(!wrdQueue.empty()) {
		wrdQueue.pop();
	}
	
		path.clear();
	return solution;  // return solution
}

