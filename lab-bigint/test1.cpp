#include "bigint.h"
#include <iostream>
using namespace std;

int main() {
   BigInt a("99");
   BigInt b("902");
   b.add(a);    // increase b by a
   cout << b.to_string() << endl; // prints 55
   b.add(a);    // increase b by a
   cout << b.to_string() << endl; // prints 68
}
