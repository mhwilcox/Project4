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
		std::cout<<"for sum4hash: "<<sum4hash<<std::endl;
	}

	std::cout <<"This is sum4hash of "<< s << ": "<< sum4hash << std::endl;

	if( table[sum4hash] == 0 ) {
		return sum4hash;
	}
	else {
		// increase the value of the hash (h(k) + i^2) % mod
		sum4hash = rehash(sum4hash, 0);
	}

	return sum4hash; // this is not correct.
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
	count= count +1;;	// increment count
	int tabSize = getCapacity();
	std::cout<<"this is after capacity()"<<std::endl;
	int numKeys = getCount();
	int tempHashVal = hashFunction( s, BASE_TO_USE, getCapacity() );
	// test load-factor
	double one = 1;
	double test = (numKeys*one) / (tabSize);

	std::cout<<"load limit test: "<< (test) << std::endl;

	if ( test >= LOAD_LIMIT ) {
		std::string * temp = new std::string[getCapacity()];
		for (int i = 0; i < numKeys - 1; i++) {
			temp[i] = table[i];
		}
		cap = cap + 1;
		setCapacity(cap);
		std::cout<<"capacity = "<<getCapacity()<<std::endl;

		table = new std::string[getCapacity()];

		for (int k = 0; k < numKeys - 1; k++) {
			int tmHash = hashFunction(temp[k], BASE_TO_USE, getCapacity());
			table[tmHash] = temp[k];
		}

		table[tempHashVal] = s;

	}	// end (if test >= load limit)

// input string into hash array
std::cout<<"outside if hash val : "<<tempHashVal<<std::endl;
	table[tempHashVal] = s;
		
}


bool WordSet::contains(std::string s) const
{
	int tmH = hashFunction(s, BASE_TO_USE, getCapacity());
	if ( table[tmH] == s ) {
		return true;
	}
	else {
		return false;  
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
int rehash(int startHash, int inc) {
	int temp = startHash;
	int mod = getCapacity();

	while ( table[temp] != 0) {
		temp = (temp + pow(inc,2)) % mod;
		inc++;
		rehash(temp,inc);		
	}
	return temp;
}