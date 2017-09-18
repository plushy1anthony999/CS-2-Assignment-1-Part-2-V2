#include <assert.h>
#include "Employee.h"
#include "Employees.h"

using namespace std;

void doUnitTesting();

const bool UNIT_TESTING = false;



int main() {
	if (UNIT_TESTING) doUnitTesting();

	/* Read in Employee Info input file */
	string inputFileName;
	cout << "Please provide an input file to read from: ";
	cin >> inputFileName;
	cout << endl;

	ifstream infile(inputFileName);

	Employees employees(inputFileName, infile);

	if (employees.getEmployeesLength() == 0) // Exit Program if input file is empty
		return 0;

	// Create Output Files
	ofstream outfile("outFile.txt");

	// Write Unsorted Employees to Output Files	
	cout << "Writing Employee Info to File \"outfile.txt\"..." << endl;
	outfile << "Unsorted Employees: " << endl << endl;
	employees.writeToFile(outfile);

	outfile << endl;
	

	// Employees sorted by ID
	employees.sort(EMPLOYEE_SORT_FLAGS::ID);
	outfile << "Employees sorted by ID: " << endl << endl;
	employees.writeToFile(outfile);
	outfile << endl;

	// Employees sorted by Last Name
	employees.sort(EMPLOYEE_SORT_FLAGS::LAST_NAME);
	outfile << "Employees sorted by Last Name: " << endl << endl;
	employees.writeToFile(outfile);
	outfile << endl;

	// Employees sorted by Gross Salary
	employees.sort(EMPLOYEE_SORT_FLAGS::GROSS_SALARY);
	outfile << "Employees sorted by Gross Salary: " << endl << endl;
	employees.writeToFile(outfile);
	outfile << endl;

	/* Display User Menu */
	while (true) {

		cout << "----------------------------------------------------------" << endl;
		cout << "1. Search for an employee by their ID Number" << endl;
		cout << "2. Search for an employee by their Last Name (if more than one is found, only the first one is returned)" << endl;
		cout << "3. Quit" << endl;
		cout << endl;

		int menuOption;
		cout << "Enter your choice: ";
		cin >> menuOption;

		if (!cin) { // Bad input given
			cin.clear();
			cin.ignore(100000, '\n');
			cout << "Please select a number from 1 to 3" << endl << endl;
			continue; // Display menu again
		}

		switch (menuOption) {
		case 1: {
			int employeeIdNumber;
			cout << "Enter the employee's ID Number: ";
			cin >> employeeIdNumber;
			cout << endl;

			if (!cin) { // Bad input given
				cin.clear();
				cin.ignore(100000, '\n');
				cout << "Invalid ID Number Given" << endl << endl;
				continue; // Display menu again
			}

			Employee employee = employees.getEmployeeByID(employeeIdNumber);
			if (employee.getIsEmptyEmployee()) {
				cin.ignore(10000, '\n');
				cout << "An employee with ID " << employeeIdNumber << " could not be found." << endl << endl;
				continue;
			}
			else {
				employee.writeToConsole(cout);
				cout << endl;
				continue;
			}
			 
			cout << endl;
			continue;

		}

		case 2: {
			string employeeLastName;
			cout << "Enter the employee's last name: ";
			cin >> employeeLastName;
			cout << endl;

			Employee employee = employees.getEmployeeByLastName(employeeLastName); // If last name couldn't be found, an empty employee is created
			if (employee.getIsEmptyEmployee()) {
				cin.ignore(10000, '\n');
				cout << "The employee \"" << employeeLastName << "\" could not be found." << endl << endl;
				continue;
			}
			else {
				employee.writeToConsole(cout);
				cout << endl;
				continue;
			}
		}

		case 3:
			return 0; // Quit the Program

		default:
			cout << "Please select a number from 1 to 3" << endl << endl;
			continue;
		}
	}
}


void doUnitTesting() {
	/* Test Employee Class */
	Employee employee_1 = Employee(
		false,
		"Anthony",
		"Ghouri",
		'M',
		1000,
		3,
		12,
		4
	);

	Employee employee_2 = Employee(
		false,
		"Emily",
		"Ghouri",
		'S',
		1001,
		3,
		50,
		1
	);

	// Test Employee Getter Methods
	assert(employee_1.getFirstName() == "Anthony");
	assert(employee_1.getLastName() == "Ghouri");
	assert(employee_1.getEmployeeCode() == 'M');
	assert(employee_1.getIdNumber() == 1000);
	assert(employee_1.getClassificationCode() == 3);
	assert(employee_1.getYearsOfService() == 12);
	assert(employee_1.getEducationalCode() == 4);
	assert(employee_1.getJobType() == "Management");
	assert(employee_1.getEmployeeBasePay() == EMPLOYEE_CODE_M_BASE_PAY);
	assert(employee_1.getGrossSalary() == 2205);
	assert(employee_1.getIsValidEmployee() == true);

	assert(employee_2.getFirstName() == "Emily");
	assert(employee_2.getLastName() == "Ghouri");
	assert(employee_2.getEmployeeCode() == 'S');
	assert(employee_2.getIdNumber() == 1001);
	assert(employee_2.getClassificationCode() == 3);
	assert(employee_2.getYearsOfService() == 50);
	assert(employee_2.getEducationalCode() == 1);
	assert(employee_2.getJobType() == "Factory Worker");
	assert(employee_2.getEmployeeBasePay() == EMPLOYEE_CODE_S_BASE_PAY);
	assert(employee_2.getGrossSalary() == 1320);


	/* Test Employees Class */
	ifstream inputFile1("namelist.txt");
	ifstream inputFile2("namelist2.txt");
	ifstream inputFile3("namelist3.txt");

	Employees employeesContainer[] = {
		Employees("namelist.txt", inputFile1),
		Employees("namelist2.txt", inputFile2),
		Employees("namelist3.txt", inputFile3)
	};

	// Test "namelist.txt"

	// Before Sorting
	assert(employeesContainer[0].getEmployeeByIndex(0).getLastName() == "Smith");
	assert(employeesContainer[0].getEmployeeByIndex(0).getFirstName() == "Jeff");
	assert(employeesContainer[0].getEmployeeByIndex(0).getEmployeeCode() == 'M');
	assert(employeesContainer[0].getEmployeeByIndex(0).getIdNumber() == 1234);
	assert(employeesContainer[0].getEmployeeByIndex(0).getClassificationCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(0).getYearsOfService() == 12);
	assert(employeesContainer[0].getEmployeeByIndex(0).getEducationalCode() == 2);
	assert(employeesContainer[0].getEmployeeByIndex(0).getJobType() == "Management");
	assert(employeesContainer[0].getEmployeeByIndex(0).getEmployeeBasePay() == EMPLOYEE_CODE_M_BASE_PAY);
	assert(employeesContainer[0].getEmployeeByIndex(0).getGrossSalary() == 1980);

	// After Sorting by ID
	employeesContainer[0].sort(EMPLOYEE_SORT_FLAGS::ID);

	assert(employeesContainer[0].getEmployeeByIndex(1).getLastName() == "Summer");
	assert(employeesContainer[0].getEmployeeByIndex(1).getFirstName() == "Jeff");
	assert(employeesContainer[0].getEmployeeByIndex(1).getEmployeeCode() == 'M');
	assert(employeesContainer[0].getEmployeeByIndex(1).getIdNumber() == 1294);
	assert(employeesContainer[0].getEmployeeByIndex(1).getClassificationCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(1).getYearsOfService() == 22);
	assert(employeesContainer[0].getEmployeeByIndex(1).getEducationalCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(1).getJobType() == "Management");
	assert(employeesContainer[0].getEmployeeByIndex(1).getEmployeeBasePay() == EMPLOYEE_CODE_M_BASE_PAY);
	assert(employeesContainer[0].getEmployeeByIndex(1).getGrossSalary() == 2235);

	// After Sorting by Last Name
	employeesContainer[0].sort(EMPLOYEE_SORT_FLAGS::LAST_NAME);

	assert(employeesContainer[0].getEmployeeByIndex(0).getLastName() == "Adam");
	assert(employeesContainer[0].getEmployeeByIndex(0).getFirstName() == "John");
	assert(employeesContainer[0].getEmployeeByIndex(0).getEmployeeCode() == 'O');
	assert(employeesContainer[0].getEmployeeByIndex(0).getIdNumber() == 6703);
	assert(employeesContainer[0].getEmployeeByIndex(0).getClassificationCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(0).getYearsOfService() == 42);
	assert(employeesContainer[0].getEmployeeByIndex(0).getEducationalCode() == 3);
	assert(employeesContainer[0].getEmployeeByIndex(0).getJobType() == "Office Worker");
	assert(employeesContainer[0].getEmployeeByIndex(0).getEmployeeBasePay() == EMPLOYEE_CODE_O_BASE_PAY);
	assert(employeesContainer[0].getEmployeeByIndex(0).getGrossSalary() == 1690);

	// After Sorting by Gross Salary
	employeesContainer[0].sort(EMPLOYEE_SORT_FLAGS::GROSS_SALARY);

	assert(employeesContainer[0].getEmployeeByIndex(0).getIsValidEmployee() == false); // All invalid employees should have invalid Gross Salaries
																					  // and so should be first in the array
	assert(employeesContainer[0].getEmployeeByIndex(0).getGrossSalary() == -1);
	

	// Find and test against the first Valid Employee
	for (size_t i = 0; i < employeesContainer[0].getEmployeesLength(); i++) {
		if (employeesContainer[0].getEmployeeByIndex(i).getIsValidEmployee()) {
			assert(employeesContainer[0].getEmployeeByIndex(i).getLastName() == "Khan");
			assert(employeesContainer[0].getEmployeeByIndex(i).getFirstName() == "Jack");
			assert(employeesContainer[0].getEmployeeByIndex(i).getEmployeeCode() == 'S');
			assert(employeesContainer[0].getEmployeeByIndex(i).getIdNumber() == 23414);
			assert(employeesContainer[0].getEmployeeByIndex(i).getClassificationCode() == 2);
			assert(employeesContainer[0].getEmployeeByIndex(i).getYearsOfService() == 5);
			assert(employeesContainer[0].getEmployeeByIndex(i).getEducationalCode() == 2);
			assert(employeesContainer[0].getEmployeeByIndex(i).getJobType() == "Factory Worker");
			assert(employeesContainer[0].getEmployeeByIndex(i).getEmployeeBasePay() == EMPLOYEE_CODE_S_BASE_PAY);
			assert(employeesContainer[0].getEmployeeByIndex(i).getGrossSalary() == 960);

			break;
		}
	}


	// Test Employees Getter Methods
	Employee employeeById = employeesContainer[0].getEmployeeByID(6703);
	assert(employeeById.getLastName() == "Adam");
	assert(employeeById.getFirstName() == "John");
	assert(employeeById.getEmployeeCode() == 'O');
	assert(employeeById.getIdNumber() == 6703);
	assert(employeeById.getClassificationCode() == 3);
	assert(employeeById.getYearsOfService() == 42);
	assert(employeeById.getEducationalCode() == 3);
	assert(employeeById.getJobType() == "Office Worker");
	assert(employeeById.getEmployeeBasePay() == EMPLOYEE_CODE_O_BASE_PAY);
	assert(employeeById.getGrossSalary() == 1690);
	

	cout << "All tests passed" << endl;
}
