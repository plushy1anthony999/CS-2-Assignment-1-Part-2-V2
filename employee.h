#pragma once

#include <string>
#include <iostream>
#include <iomanip>

/* Used for Calculating an Employee's Gross Salary */
const double EMPLOYEE_CODE_S_BASE_PAY = 800;
const double EMPLOYEE_CODE_O_BASE_PAY = 1000;
const double EMPLOYEE_CODE_M_BASE_PAY = 1500;
const double CLASSIFICATION_CODE_1_BONUS = 0.05;     // 5%
const double CLASSIFICATION_CODE_2_BONUS = 0.1;      // 10%
const double CLASSIFICATION_CODE_3_BONUS = 0.2;      // 20% 
const double EDUCATIONAL_CODE_1_BONUS = 0;		     // 0%
const double EDUCATIONAL_CODE_2_BONUS = 0.05;        // 5%
const double EDUCATIONAL_CODE_3_BONUS = 0.12;	     // 12%
const double EDUCATIONAL_CODE_4_BONUS = 0.2;	     // 20%
const double YEARS_OF_SERVICE_0_TO_10_BONUS = 0.05;  // 5%
const double YEARS_OF_SERVICE_ABOVE_10_BONUS = 0.01; // Add 1% for every year above ten to gross pay


class Employee {
    bool isValidEmployee = false;
    bool isEmptyEmployee = true;
	std::string jobType;
	double employeeBasePay;
	double grossSalary;

	std::string firstName;
	std::string lastName;
	char employeeCode;
	int idNumber;
	int classificationCode;
	int yearsOfService;
	int educationalCode;

public:
    Employee();

	Employee(
		bool isEmptyEmployee,
		std::string firstName = "",
		std::string lastName = "",
		char employeeCode = '\0',
		int idNumber = 0000,
		int classificationCode = 0,
		int yearsOfService = 0,
		int educationalCode = 0
	);

	// Private Setters
	void calculateJobType();
	void calculateEmployeeBasePay();
	bool validate();
	void calculateGrossSalary();

	// Getters
	const std::string getFirstName() const;
	const std::string getLastName() const;
	char getEmployeeCode() const;
	int getIdNumber() const;
	int getClassificationCode() const;
	int getYearsOfService() const;
	int getEducationalCode() const;

	const std::string getJobType() const;
	double getEmployeeBasePay() const;
	double getGrossSalary() const;
	bool getIsValidEmployee() const;
	bool getIsEmptyEmployee() const;

	// Writes a single Employee's Info formatted in a table to the console
	void writeToConsole(std::ostream & console) const;
};
