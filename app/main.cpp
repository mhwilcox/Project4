#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

#include "proj4.hpp"
#include "Wordset.hpp"


int main()
{
	std::cout<<"this is resize test1 Tab2. "<<std::endl;
	WordSet ws;
	ws.insert("sleepy");
	ws.insert("happy");
	std::cout<<"sleepy and happy inserted correctly, going to check capacity. "<<std::endl;
	if(ws.getCapacity() == 11 ) {
		std::cout<<"capacity is 11.   ******************************************************\n"<<std::endl;
	}
	//EXPECT_TRUE(ws.getCapacity() == 11);
	ws.insert("dopey");
	std::cout<<"after insert dopey"<<std::endl;
	//EXPECT_TRUE(ws.getCapacity() == 23);
	if(ws.getCapacity() == 23) {
		std::cout<<"capacity is 23.          ////////////////////////////   // \n"<<std::endl;
	}
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	std::cout<<"inserted: sneezy, datalink, australia, guacamole, and phylum"<<std::endl;
	//EXPECT_TRUE(ws.contains("happy"));
	if(ws.contains("happy")) {
		std::cout<<"contains 'happy' "<<std::endl;
	}
	//EXPECT_TRUE(ws.contains("dopey"));
	if(ws.contains("dopey")) {
		std::cout<<"contains 'dopey' "<<std::endl;
	}
	std::cout<<"\nnumber of strings in table: "<< ws.getCount()<<std::endl;
	std::cout<<"this is the capacity: "<< ws.getCapacity()<<std::endl;

    return 0;
}

