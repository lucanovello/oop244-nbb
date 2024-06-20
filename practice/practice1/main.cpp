#include <iostream>

usingnamespace std;

classNumber{

int num;

public:

Number(int n) {

num = n;

}

int getNum() const {

return num;

}

};

int main() {

	const Number n1(5);

	Number n2(10);

	const Number& ref = n2;

	cout << n1.getNum() + ref.getNum() << endl; return0;

}