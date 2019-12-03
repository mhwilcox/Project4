#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

#include "proj4.hpp"
#include "Wordset.hpp"


int main()
{
	std::cout<<"second words test. "<<std::endl;
	WordSet words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);

 	std::string r = convert("ant", "eat", words);
 	if( r == "ant --> aft -> oft --> oat --> eat") {
 		std::cout<<"TRUE!!!!!!!!!!"<<std::endl;
 	}

 	std::cout<<"return of 'ant to eat': "<<r<<std::endl;

    return 0;
}

