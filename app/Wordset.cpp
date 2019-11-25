#include "Wordset.hpp"
#include <string>

const int BASE_TO_USE = 37; 
const double LOAD_LIMIT = 0.25;


// returns s, as a number in the given base, mod the given modulus
int hashFunction(std::string s, int base, int mod)
{
	return 0; // this is not correct.
}


WordSet::WordSet()
{

}

WordSet::~WordSet()
{

}

void WordSet::insert(std::string s)
{

}


bool WordSet::contains(std::string s) const
{
	return false;  // stub, not correct.
}

// return how many distinct strings are in the set
int WordSet::getCount() const
{
	return BASE_TO_USE + LOAD_LIMIT; // this is not the right answer. 
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{
	return 1729; // that isn't even a prime number!
}
