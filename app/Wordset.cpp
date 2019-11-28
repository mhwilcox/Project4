#include "Wordset.hpp"
#include <string>

const int BASE_TO_USE = 37; 
const double LOAD_LIMIT = 0.25;


// returns s, as a number in the given base, mod the given modulus
int hashFunction(std::string s, int base, int mod)
{
std::cout<<"hash"<<std::endl;
	
	int sum4hash = 0;

	for (int i = 0; i < s.length(); i++) {
		sum4hash = (  (sum4hash * BASE_TO_USE) + (s[i] -'a')  ) % mod;
	}
std::cout<<"******** "<<s<<std::endl;
	std::cout <<"This is sum4hash of "<< s << ": "<< sum4hash << std::endl;
	
	return sum4hash; // 
}


WordSet::WordSet()
{
	cap = 0;
	setCapacity(cap);
	int size = getCapacity();
//	std::string s[size]; // would be static.  Look up heap vs stack memory.
	table = new std::string[ size ] ;
	count = 0;
}

WordSet::~WordSet()
{
	delete [] table;
}

void WordSet::insert(std::string s)
{
	if ( s == "" ) {
		return;
	}

	int tabSize = getCapacity();
	int numKeys = getCount() + 1;
	int tempHashVal = hashFunction( s, BASE_TO_USE, getCapacity() );
	// test load-factor
	double one = 1;
	double test = (numKeys*one) / (tabSize);

	std::cout<<"load limit test: "<< (test) << std::endl;
	if (test >= LOAD_LIMIT) {
		reSize(table);
	}
	

// input string into hash array
std::cout<<"outside if hash val : "<<tempHashVal<<std::endl;
// use contains to figure out the insert
int inc = 0;
while (table[tempHashVal + (inc*inc) % getCapacity()] != "") {
	inc++;
}

}


bool WordSet::contains(std::string s) const
{
	// finds the hash value of the string
	int tmH = hashFunction(s, BASE_TO_USE, getCapacity());
	// is the string at the hashed value in the table?
	std::cout<<"contains:\t"<< s << std::endl;
	int inc = 0;
	if(table[tmH] == s) {
		return true;
	}
	else {
		while (table[(tmH + (inc*inc) ) % getCapacity()] != "" && table[(tmH + (inc*inc) ) % getCapacity()] != s) {
			std::cout << "(" << inc << ") : " << ( (tmH+ (inc*inc) ) % getCapacity() ) << "\t : "  << table[(tmH+ (inc*inc) ) % getCapacity()] << std::endl;
			inc++;
		}

		std::cout << "final value of inc " << inc << std::endl; 
		std::cout<<"value at inc: "<< table[tmH + (inc*inc) % getCapacity()];

		if(table[(tmH + (inc*inc) ) % getCapacity()] == s ){
			return true;
		}
		else {
			return false;
		}
	}
}

// return how many distinct strings are in the set
int WordSet::getCount() const
{
	return count; //  
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{

	return SIZES[cap]; // 
}

// increase the value of the hash (h(k) + i^2) % mod
int WordSet::rehashIn(int startHash, int inc) {
	int temp = startHash;
	int mod = getCapacity();

	while ( table[temp] != "") {
		temp = (temp + (inc*inc) ) % mod;
		inc+=1;		
	}
	
	return temp;
}



// makes table bigger and rehashes values into the new table
void WordSet::reSize(std::string * origTable) {
	setCapacity(cap+1);
	table = new std::string[ getCapacity() ];

	for(int i = 0; i < getCapacity(); i++) {
		if(origTable[i] != "") {
			int tempHashVal = hashFunction(origTable[i], BASE_TO_USE, getCapacity());
			int inc = 0;
			while(table[tempHashVal + (inc*inc) % getCapacity()] != "") {
				inc++;
			}	// end while loop
			table[tempHashVal + (inc*inc) % getCapacity()] = origTable[i];
		}	// end if
	}	// end for loop
}	// end reSize