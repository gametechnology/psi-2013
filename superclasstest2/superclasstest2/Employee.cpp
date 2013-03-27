#include "StdAfx.h"
#include "Employee.h"
#include <string>

Employee::Employee(std::string theName, float thePayRate)
{
  name = theName;
  payRate = thePayRate;
}

std::string Employee::getName() const
{
  return name;
}

float Employee::getPayRate() const
{
  return payRate;
}

float Employee::pay(float hoursWorked) const
{
  return hoursWorked * payRate;
}
