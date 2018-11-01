#include<iostream>
using namespace std;

//global
int ArrayB[3]={1,2,3};
int ArrayC[3]={2,3,4};

int main()
{
	ArrayB[0]= ArrayB[0]+ArrayC[0];
	cout << "result=" << ArrayB[0] << endl;

return 0;
}
