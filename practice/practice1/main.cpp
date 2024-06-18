#include <iostream>
#include <stdlib.h>

using namespace std;


class Numbers {
	int nums;
	int min_number = 1;
	int max_number = 1000;
	int* numbers;
public:
	Numbers(int = 0);
	~Numbers();
	void initNumbers();
	void setNums(int n);
	int getNums();
	int getMaxNums();
	void setNumbers(int n);
	int getNumbers();
	void display();

};
Numbers::Numbers(int n) {
	nums = n;
	numbers = nullptr;
}
Numbers::~Numbers() {
	delete numbers;
}
void Numbers::setNums(int n) {
	nums = n;
}
int Numbers::getNums() {
	return nums;
}
int Numbers::getMaxNums() {
	return max_number;
}
void Numbers::setNumbers(int n) {
	for (int i = 0; i < n; i++)	{
		// numbers[i] = rand() % max_number + min_number;
		// numbers[i] = i;
		numbers[i] = nums - i - 1;
	}
}
int Numbers::getNumbers() {
	return *numbers;
}
void Numbers::display() {
	for (int i = 0; i < nums; i++) {
		cout << "[" << numbers[i] << "]";
	}
}
void Numbers::initNumbers() {
	numbers = new int[nums];
}




int main() {
	Numbers numbers;

	while (numbers.getNums() < 1 || numbers.getNums() > numbers.getMaxNums()) {
		int n;
		cout << "Enter the number of numbers (must be between 1-" << numbers.getMaxNums() << "): ";
		cin >> n;
		numbers.setNums(n);
		if (cin.fail() || numbers.getNums() < 1 || numbers.getNums() > numbers.getMaxNums()) {
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
			numbers.setNums(0); // Reset num to stay in the loop
			cout << "Invalid input. ";
		}
	}
	numbers.initNumbers();
	cout << "\nYour numbers are: " << endl;
	numbers.setNumbers(numbers.getNums());
	numbers.display();
	cout << ".......\n\nBOOM!!!\n\n";
	return 0;
}
