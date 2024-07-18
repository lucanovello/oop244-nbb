#include <iostream>

using namespace std;



class A {

public:

	A() { cout << "A Constructor" << endl; }

	virtual void f() { cout << "A::f" << endl; }

	virtual void g() { cout << "A::g" << endl; }

	virtual ~A() { cout << "A Destructor" << endl; }

};



class B : public A {

public:

	B() { cout << "B Constructor" << endl; }

	void f() { cout << "B::f" << endl; }

	void h() { cout << "B::h" << endl; }

	~B() { cout << "B Destructor" << endl; }

};



class C : public B {

public:

	C() { cout << "C Constructor" << endl; }

	void f() { cout << "C::f" << endl; }

	void g() { cout << "C::g" << endl; }

	~C() { cout << "C Destructor" << endl; }

};



void callFunctions(A* obj) {

	obj->f();

	obj->g();

}



int main() {

	A* a = new C();

	callFunctions(a);

	delete a;

	return 0;

}