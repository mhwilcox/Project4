#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

#include "proj4.hpp"
#include "Wordset.hpp"


int main()
{
	std::cout<<"head to tail test. "<<std::endl;
	WordSet words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);

 	std::string r = convert("head", "tail", words);
 	if( r == "head --> heal --> teal --> tell --> tall --> tail") {
 		std::cout<<"TRUE!!!!!!!!!!"<<std::endl;
 	}

 	std::cout<<"\n*******\n*******\nreturn of 'head' to 'tail': \t"<<r<<std::endl;

    return 0;
}

