/*虚函数*/
#include <iostream>
#include <stdio.h>  
using namespace std;
class Base{

public:
    int a;
    virtual void f() { cout << " Base::f()" << endl; }
	virtual void g() { cout << " Base::g()" << endl; }
    virtual void h() { cout << " Base::h()" << endl; }
};

int main(int argc,char *argv[])
{
    Base A;
    int addr;
	A.a = 0x1234;
    cout << "A sizeof:" << sizeof(A) << endl;
    cout << "&A   addr:" << (int*)&(A) << endl;
    cout << "&A.a addr:" << (int*)&(A.a) << endl;


	cout <<"*((int*)&(A))      value:" <<  *((int*)&(A)) << endl;
    cout <<"*(*((int*)&(A)))   value:" <<  (int*)*(int*)&A << endl;
    cout <<"*(*((int*)&(A)))   value:" <<  (int*)*(int*)&A+1 << endl;
	cout <<"*(*((int*)&(A)))   value:" << (int*)*(int*)&A+2 << endl;

    cout <<"f()	addr:" << &Base::f << endl;
	printf("%X\n", &Base::f );
	//cout <<"f() addr:" <<(int*)&ptr << endl;
    //cout <<"g() addr:" <<(int*)&Base::g << endl;
	//cout <<"h() addr:" <<(int*)&Base::h << endl;

    return(0);
}
