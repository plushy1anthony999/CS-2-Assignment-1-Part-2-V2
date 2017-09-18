#include "Employee.h"

using namespace std;

Employee::Employee() {
	this->firstName = "";
	this->lastName = "";
	this->employeeCode = '\0';
	this->idNumber = 0000;
	this->classificationCode = -1;
	this->yearsOfService = -1;
	this->educationalCode = -1;

	isEmptyEmployee = true;
}

Employee::Employee(
	bool isEmptyEmployee,
	string firstName,
	string lastName,
	char employeeCode,
	int idNumber,
	int classificationCode,
	int yearsOfService,
	int educationalCode
) {
	// Initialize member variables with arguments passed in
	this->firstName = firstName;
	this->lastName = lastName;
	this->employeeCode = employeeCode;
	this->idNumber = idNumber;
	this->classificationCode = classificationCode;
	this->yearsOfService = yearsOfService;
	this->educationalCode = educationalCode;

	this->isEmptyEmployee = isEmptyEmployee;

	//Initialize private member variables
	calculateJobType();
	calculateEmployeeBasePay();
	validate();
	calculateGrossSalary(); // Invalid employees will have a grossSalary of -1
}

// Private Setters
void Employee::calculateJobType() {
	switch (employeeCode) {
	case 'S':
		jobType = "Factory Worker";
		break;

	case 'O':
		jobType = "Office Worker";
		break;

	case 'M':
		jobType = "Management";
		break;
	default:
		jobType = "N/A";
		break;
	}
}
void Employee::calculateEmployeeBasePay() {

	switch (employeeCode) {
	case 'S':
		employeeBasePay = EMPLOYEE_CODE_S_BASE_PAY;
		break;
	case 'O':
		employeeBasePay = EMPLOYEE_CODE_O_BASE_PAY;
		break;
	case 'M':
		employeeBasePay = EMPLOYEE_CODE_M_BASE_PAY;
		break;
	}
}
bool Employee::validate() { // If all necessary info is found, the employee object is marked Valid
							// Is a "Setter" for isValidEmployee
	if (
		(
			employeeCode == 'S' ||
			employeeCode == 'O' ||
			employeeCode == 'M'
		)
			&&
		(
			classificationCode == 1 ||
			classificationCode == 2 ||
			classificationCode == 3
		)
			&&
		(
			yearsOfService > 0 && yearsOfService <= 50
		)
			&&
		(
			educationalCode == 1 ||
			educationalCode == 2 ||
			educationalCode == 3 ||
			educationalCode == 4
		)
	) {
		isValidEmployee = true;
		return isValidEmployee;
	}

	else {
		isValidEmployee = false;
		return isValidEmployee;
	}

}
void Employee::calculateGrossSalary() {
	if (!isValidEmployee) { // Invalid Employees will have an invalid '-1' gross salary
		grossSalary = -1;
		return;
	}

	grossSalary = employeeBasePay; // The initial value before adding bonuses

	switch (classificationCode) {
	case 1:
		grossSalary = grossSalary + (employeeBasePay * CLASSIFICATION_CODE_1_BONUS);
		break;

	case 2:
		grossSalary = grossSalary + (employeeBasePay * CLASSIFICATION_CODE_2_BONUS);
		break;

	case 3:
		grossSalary = grossSalary + (employeeBasePay * CLASSIFICATION_CODE_3_BONUS);
		break;
	}

	if (yearsOfService <= 10)
		grossSalary = grossSalary + (employeeBasePay * YEARS_OF_SERVICE_0_TO_10_BONUS);
	if (yearsOfService > 10)
		grossSalary = grossSalary + (employeeBasePay * (YEARS_OF_SERVICE_0_TO_10_BONUS + ((yearsOfService - 10) * YEARS_OF_SERVICE_ABOVE_10_BONUS)));

	switch (educationalCode) {
	case 1:
		grossSalary = grossSalary + (employeeBasePay * EDUCATIONAL_CODE_1_BONUS);
		break;

	case 2:
		grossSalary = grossSalary + (employeeBasePay * EDUCATIONAL_CODE_2_BONUS);
		break;

	case 3:
		grossSalary = grossSalary + (employeeBasePay * EDUCATIONAL_CODE_3_BONUS);
		break;

	case 4:
		grossSalary = grossSalary + (employeeBasePay * EDUCATIONAL_CODE_4_BONUS);
		break;
	}
}

// Getters
const string Employee::getFirstName() const {
	return firstName;
}
const string Employee::getLastName() const {
	return lastName;
}
char Employee::getEmployeeCode() const {
	return employeeCode;
}
int Employee::getIdNumber() const {
	return idNumber;
}
int Employee::getClassificationCode() const {
	return classificationCode;
}
int Employee::getYearsOfService() const {
	return yearsOfService;
}
int Employee::getEducationalCode() const {
	return educationalCode;
}
const string Employee::getJobType() const {
	return jobType;
}
double Employee::getEmployeeBasePay() const {
	return employeeBasePay;
}
double Employee::getGrossSalary() const {
	return grossSalary;
}
bool Employee::getIsValidEmployee() const {
	return isValidEmployee;
}
bool Employee::getIsEmptyEmployee() const {
	return isEmptyEmployee;
}

// Writes a single Employee's Info formatted in a table to the console
void Employee::writeToConsole(ostream & console) const {
	console << left << setw(20) << "Name" << setw(10) << "ID#" << setw(16) << "Job Type" << setw(16) << "Gross Salary" << endl;
	console << left << setw(20) << firstName + " " + lastName << setw(10) << idNumber << setw(16) << jobType;

	if (isValidEmployee)
		console << '$' << setw(16) << fixed << setprecision(2) << grossSalary << endl;
	else
		console << setw(16) << "N/A" << endl;

	console << left << setw(20) << "------" << setw(10) << "------" << setw(16) << "------" << setw(16) << "------" << endl;
	if (!isValidEmployee)
		console << "Gross Salary Couldn't be calculated due to bad employee data" << endl;
}	 