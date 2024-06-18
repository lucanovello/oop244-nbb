#include <iostream>
#include <locale>
#ifdef _WIN32
#define NOMINMAX // Prevent windows.h from defining min and max macros
#include <windows.h>
#endif
using namespace std;

const int NG = 20;

class Student {
	int no;
	double grades[NG];
	int ng;
public:
	Student();
	~Student();
};

Student::Student() {
	no = 0;
	ng = 0;
}

Student::~Student() {
	// No need to delete grades since it was not allocated with new
}

int main() {
	int num = 0;
	double nums[NG];
	// On Windows, set the console to UTF-8 code page
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	#endif

	// Set the locale to the user's default locale
	std::locale::global(std::locale(""));

	cout.setf(iostream::fixed);
	cout.precision(2);

	while (num < 1 || num > NG) {
		cout << "Enter the number of numbers (must be between 1-" << NG << "): ";
		cin >> num;

		if (cin.fail() || num < 1 || num > NG) {
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
			num = 0; // Reset num to stay in the loop
			cout << "Invalid input. Please enter a valid integer." << endl;
		}
	}

	for (int i = 0; i < num; i++) {
		double number;
		while (true) {
			cout << "Enter number " << i + 1 << " of " << num << ": ";
			cin >> number;

			if (cin.fail()) {
				cin.clear(); // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
				cout << "Invalid input. Please enter a number." << endl;
			}
			else {
				nums[i] = number;
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any extra input
				break;
			}
		}
	}

	cout << "\nYou entered: \n";
	for (int i = 0; i < num; i++) {
		cout << " \u2022 " << nums[i] << endl;
	}
	cout << endl;

	return 0;
}
