#pragma once
#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#include <string>

class Employee {
public:
  Employee(std::string theName, float thePayRate);

  std::string getName() const;
  float getPayRate() const;

  float pay(float hoursWorked) const;

protected:
  std::string name;
  float payRate;
};

#endif /* not defined _EMPLOYEE_H */

