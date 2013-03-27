#include "StdAfx.h"
#include "Manager.h"
#include "Employee.h"

Manager::Manager(std::string theName,
                 float thePayRate,
                 bool isSalaried)
  : Employee(theName, thePayRate)
{
  salaried = isSalaried;
}

bool Manager::getSalaried() const
{
  return salaried;
}

float Manager::pay(float hoursWorked) const
{
  if (salaried)
    return payRate;
  /* else */
  return Employee::pay(hoursWorked);
}
