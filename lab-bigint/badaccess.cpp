#include <iostream> 
#include <string>
#include "bigint.h" 

using namespace std;

int main()
{
	BigInt b("123");
	b.integers[1] = 4;
}