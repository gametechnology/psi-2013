// superclasstest.cpp : Defines the entry point for the console application.
// made from tutorial:
// http://www.learncpp.com/cpp-tutorial/112-basic-inheritance-in-c/

#include "stdafx.h"
#include <iostream>
#include "BaseBallPlayer.h"
#include "Person.h"
#include "Employee.h"
#include <ostream>


int _tmain(int argc, _TCHAR* argv[])
{
	  // Create a new BaseballPlayer object
    BaseBallPlayer cJoe;
    // Assign it a name (we can do this directly because m_strName is public)
	cJoe.m_strName = "Joe";
    // Print out the name
    std::cout << cJoe.GetName() << std::endl;

	BaseBallPlayer cHenk;
	cHenk.m_bIsMale = true;
	std::cout << cHenk.IsMale()<<std::endl;

	Employee cKoen;
	cKoen.m_nAge = 15;
	cKoen.m_dHourlySalary = 20;
	std::cout << cKoen.GetAge() << std::endl;
	std::cout << cKoen.GetHourlySalary() << std::endl;

    return 0;
}

