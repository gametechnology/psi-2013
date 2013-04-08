#pragma once
#include "Person.h"
#include <string>
#include <ostream>
#include <iostream>
// Employee publicly inherits from Person
class Employee: public Person
{
public:
    std::string m_strEmployerName;
    double m_dHourlySalary;
    long m_lEmployeeID;
 
	Employee()
	{}

    Employee(std::string strEmployerName, double dHourlySalary, long lEmployeeID)
        : m_strEmployerName(strEmployerName), m_dHourlySalary(dHourlySalary),
            m_lEmployeeID(lEmployeeID)
    {
    }
 
    double GetHourlySalary() { return m_dHourlySalary; }
    void PrintNameAndSalary()
    {
        std::cout << m_strName << ": " << m_dHourlySalary << std::endl; 

	}
};