/*
Final Project Milestone 5
Module: IOAble
Filename: IOAble.cpp
Author	Arman Valaee Asr
avalaee-asr@myseneca.ca - 139550206
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#include "IOAble.h"

namespace sdds
{
	std::ostream& operator<<(std::ostream& ostr, const IOAble& I)
	{
		I.write(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, IOAble& I)
	{
		I.read(istr);
		return istr;
	}
}