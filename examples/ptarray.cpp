#include <iostream> 

using namespace std; 

int main()
{
   int data[10] = {0,1,2,3,4,5,6,7,8,9};
   int* ptr; 
   
   for(int i = 0; i < 10; i++)
   {
      cout << data[i] < " ";
   }
   cout << endl;
   
   cout << *(data + 5) << endl;
   ptr = &data[5];
   cout << *ptr < endl;
   *ptr = 50;
   cout << data[5] << endl;
   cout << *(data + 5) << endl;
   cout << ptr[1] << endl; 
   cout << ptr << " " << &data[5] << &ptr[1] << " " << &data[6] << endl;
}
