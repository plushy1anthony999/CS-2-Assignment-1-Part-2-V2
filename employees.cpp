#include "Employees.h"

using namespace std;


void Employees::sortByID() {
	for (size_t i = 0; i < employeesLength; i++) {

		// Minus 'i' is done so the loop doesn't look at elements already sorted and moved to the end
		for (size_t j = 0; j < employeesLength - 1 - i; j++) {
			if (employees[j].getIdNumber() > employees[j + 1].getIdNumber()) { // Check if left-employee has a greater Id than right-employee

				Employee rightEmployee = employees[j + 1];
				employees[j + 1] = employees[j]; // Move leftEmployee close to the end of the array
				employees[j] = rightEmployee;
			}
		}
	}
}
void Employees::sortByLastName() {
	for (size_t i = 0; i < employeesLength; i++) {
		
		// Minus 'i' is done so the loop doesn't look at elements already sorted and moved to the end
		for (size_t j = 0; j < employeesLength - 1 - i; j++) { 
			string capitalizedLastName1; // Used for non-case-sensitive sorting
			string capitalizedLastName2;

			for (char letter : employees[j].getLastName())
				capitalizedLastName1 += toupper(letter);
			for (char letter : employees[j + 1].getLastName())
				capitalizedLastName2 += toupper(letter);

			if (capitalizedLastName1 > capitalizedLastName2) { 
				Employee rightEmployee = employees[j + 1];
				employees[j + 1] = employees[j]; // Move leftEmployee close to the end of the array
				employees[j] = rightEmployee;
			}

		}
	}
}
void Employees::sortByGrossSalary() {
	for (size_t i = 0; i < employeesLength; i++) {

		// Minus 'i' is done so the loop doesn't look at elements already sorted and moved to the end
		for (size_t j = 0; j < employeesLength - 1 - i; j++) {
			if (employees[j].getGrossSalary() > employees[j + 1].getGrossSalary()) { // Check if left-employee has a greater grossSalary than right-employee

				Employee rightEmployee = employees[j + 1];
				employees[j + 1] = employees[j]; // Move leftEmployee close to the end of the array
				employees[j] = rightEmployee;
			}
		}
	}
}

Employees::Employees(const string filename, ifstream & employeeDataFile) { // Pass in an opened input-file
	if (employeeDataFile.is_open()) {
		cout << "Reading employee data from " << filename << " ..." << endl;

		if (employeeDataFile.peek() == ifstream::traits_type::eof()) { // Check if file is empty
			cout << filename << " has 0 employees listed, so none were stored." << endl << endl;
		}
		else {
			for (size_t i = 0; i < MAX_NUM_OF_EMPLOYEES; i++) { // Will read in 7 tokens and create an Employee per iteration
				if (!employeeDataFile.eof()) {					// Txt file should have 2 lines with 7 tokens per employee
			
					// Employee info to be passed in when constructing an employee
					string firstName;
					string lastName;
					char employeeCode = '\0';
					int idNumber = -1;
					int classificationCode = -1;
					int yearsOfService = -1;
					int educationalCode = -1;

					size_t currentToken = 0;

					// Read in 7 tokens to fill out employee info variables
					for (; currentToken < 7 && !employeeDataFile.eof(); currentToken++) { // Check if at end of file before reading in a token
						switch (currentToken) {
							case 0:
								employeeDataFile >> firstName;
								break;

							case 1:
								employeeDataFile >> lastName;
								break;

							case 2:
								employeeDataFile >> employeeCode;
								break;

							case 3:
								employeeDataFile >> idNumber;
								break;

							case 4:
								employeeDataFile >> classificationCode;
								break;

							case 5:
								employeeDataFile >> yearsOfService;
								break;

							case 6:
								employeeDataFile >> educationalCode;
								break;
							}
						}

					// An employee is only created when 7 tokens (a full employee) is read from the infile
					if (currentToken == 7) {
						// If bad data is read from the infile and passed in, an invalid Employee is created and added to the array
						employees[i] = Employee( // Pass in the 7 tokens to construct and add an employee to the array
							false,
							firstName,
							lastName,
							employeeCode,
							idNumber,
							classificationCode,
							yearsOfService,
							educationalCode
						);

						employeesLength++;
					}
				}
			}

			// Check if file still has employees that haven't been read
			if (employeeDataFile.peek() != ifstream::traits_type::eof()) {
				cout << filename << " has more than 30 employees listed." << endl;
				cout << "Only 30 employees were read from file and stored." << endl << endl;
			} 
			else {
				cout << employeesLength << " employees were read and stored." << endl << endl;
				employeeDataFile.close();
			}
		}

	}
	else 
		cout << "The file couldn't be opened..." << endl;
}

Employee Employees::getEmployeeByIndex(unsigned int index) const {
	if (index < employeesLength) // prevent going outside array
		return employees[index];
		
	return Employee(); // Will return an invalid, empty employee when an actual employee in the array can't be found
}
Employee Employees::getEmployeeByLastName(string lastName) const {
	string inputLastName;

	for (const char & letter : lastName) 
		inputLastName += toupper(letter);

	for (size_t i = 0; i < employeesLength; i++) {
		string employeeLastName;
		
		for (const char & letter : employees[i].getLastName())
			employeeLastName += toupper(letter);

		if (inputLastName == employeeLastName)
			return employees[i];
	}
	return Employee(); // Will return an invalid, empty employee when given an unknown name
}
Employee Employees::getEmployeeByID(unsigned int ID) const {
	for (size_t i = 0; i < employeesLength; i++) {
		if (employees[i].getIdNumber() == ID)
			return employees[i];
	}
	return Employee(); // Will return an invalid, empty employee when given an unknown ID
}

size_t Employees::getEmployeesLength() const {
	return employeesLength;
}

void Employees::sort(EMPLOYEE_SORT_FLAGS SORT_FLAG) {
	switch (SORT_FLAG) {
	case EMPLOYEE_SORT_FLAGS::ID:
		sortByID();
		break;

	case EMPLOYEE_SORT_FLAGS::LAST_NAME:
		sortByLastName();
		break;

	case EMPLOYEE_SORT_FLAGS::GROSS_SALARY:
		sortByGrossSalary();
		break;
	}
}

void Employees::writeToFile(ofstream & outFile) const {
	
	outFile << left << setw(20) << "Name" << setw(10) << "ID#" << setw(16) << "Job Type" << setw(16) << "Gross Salary" << endl;

	for (size_t i = 0; i < employeesLength; i++) {
		Employee currentEmployee = getEmployeeByIndex(i);
		size_t currentEmployeeIndex = i;

		outFile << left << setw(20) << currentEmployee.getFirstName() + " " + currentEmployee.getLastName() << setw(10) << currentEmployee.getIdNumber() << setw(16) << currentEmployee.getJobType();
			
		if (currentEmployee.getIsValidEmployee())
			outFile << '$' << setw(16) << fixed << setprecision(2) << currentEmployee.getGrossSalary() << endl;
		else
			outFile << setw(16) << "N/A" << endl;
	}

}
void Employees::writeToConsole(std::ostream & console) const {
	for (size_t i = 0; i < employeesLength; i++) {
		Employee currentEmployee = getEmployeeByIndex(i);
		size_t currentEmployeeIndex = i;

		console << left << setw(20) << "Name" << setw(10) << "ID#" << setw(16) << "Job Type" << setw(16) << "Gross Salary" << endl;
		console << left << setw(20) << currentEmployee.getFirstName() + " " + currentEmployee.getLastName() << setw(10) << currentEmployee.getIdNumber() << setw(16) << currentEmployee.getJobType();

		if (currentEmployee.getIsValidEmployee())
			console << '$' << setw(16) << fixed << setprecision(2) << currentEmployee.getGrossSalary() << endl;
		else
			console << setw(16) << "N/A" << endl;

		console << left << setw(20) << "------" << setw(10) << "------" << setw(16) << "------" << setw(16) << "------" << endl;
		if (!currentEmployee.getIsValidEmployee())
			console << "Gross Salary Couldn't be calculated due to bad employee data" << endl;
	}
}