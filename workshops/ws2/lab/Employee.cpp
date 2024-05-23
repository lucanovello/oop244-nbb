#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Employee.h"
#include "File.h"
using namespace std;
namespace seneca {

	int noOfEmployees;
	Employee* employees;


	// TODO: Finish the implementation of the 1 arg load function which
	// reads one employee record from the file and loads it into the employee reference
	// argument
	bool load(Employee& emp) {
		int empNumber;
		double salary;
		bool ok = false;
		char name[128];
		/* if reading of employee number, salay and name are successful
				allocate memory to the size of the name + 1
				and keep its address in the name of the Employee Reference
		*/
		if (read(empNumber) && read(salary) && read(name)) {
			size_t nameLength = strlen(name) + 1;
			emp.m_name = new char[nameLength];

			//copy the name into the newly allocated memroy
			strcpy(emp.m_name, name);
			emp.m_empNo = empNumber;
			emp.m_salary = salary;

			// make sure the "ok" flag is set to true
			ok = true;
			// end if
		}
		return ok;
	}
	// TODO: Finish the implementation of the 0 arg load function 
	bool load() {
		bool ok = false;
		int i = 0;
		if (openFile(DATAFILE)) {
			/*
			 Set the noOfEmployees to the number of recoreds in the file.
			 dyanamically allocated an array of employees into the global
			 Employee pointer; "employees" to the size of the noOfEmployees. */
			noOfEmployees = noOfRecords();
			employees = new Employee[noOfEmployees];
			//In a loop load the employee records from the file into the dynamic array.
			for (i = 0; i < noOfEmployees; ++i) {
				// If the number of the records does not match the number of reads print the message "Error: incorrect number of records read; the data is possibly corrupted"
				if (!load(employees[i])) {
					std::cerr << "Error: incorrect number of records read; the data is possibly corrupted." << std::endl;
					return ok;
				}
			}
			// Otherwise set the ok flag to true
			if (i == noOfEmployees) {
				ok = true;
				//End if
			}

			//close the file
			closeFile();
		}
		else {
			cout << "Could not open data file: " << DATAFILE << endl;
		}
		return ok;
	}

	// TODO: Implementation for the display functions go here
	void display(const Employee& emp) {
		std::cout << emp.m_empNo << ": " << emp.m_name << ", " << emp.m_salary << std::endl;
	}

	void display() {
		std::cout << "Employee Salary report, sorted by employee number" << std::endl;
		std::cout << "no- Emp no, Name, Salary" << std::endl;
		std::cout << "------------------------------------------------" << std::endl;

		sort();

		for (int i = 0; i < noOfEmployees; ++i) {
			std::cout << i + 1 << "- ";
			display(employees[i]);
		}
	}
	// TODO: Implementation for the deallocateMemory function goes here
	void deallocateMemory() {
		for (int i = 0; i < noOfEmployees; ++i) {
			delete[] employees[i].m_name;
		}
		delete[] employees;
		employees = nullptr;
	}

	// Sort function
	void sort() {
		for (int i = 0; i < noOfEmployees - 1; ++i) {
			for (int j = i + 1; j < noOfEmployees; ++j) {
				if (employees[i].m_empNo > employees[j].m_empNo) {
					Employee temp = employees[i];
					employees[i] = employees[j];
					employees[j] = temp;
				}
			}
		}
	}
}