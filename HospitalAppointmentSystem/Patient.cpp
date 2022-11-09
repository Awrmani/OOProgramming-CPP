/*
Final Project Milestone 5
Module: Patient
Filename: Patient.cpp
Author	Arman Valaee Asr
avalaee-asr@myseneca.ca - 139550206
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#include "Patient.h"

namespace sdds
{
	Patient::Patient(int ticketNo, bool ioFlag) : m_ticket(ticketNo)
	{
		m_ioFlag = ioFlag;
	}

	Patient::~Patient()
	{
		delete[] m_name;
		m_name = nullptr;
	}

	bool Patient::fileIO()const
	{
		return m_ioFlag;
	}

	void Patient::fileIO(int ioFlag)
	{
		m_ioFlag = ioFlag;
	}

	bool Patient::operator==(char c)const
	{
		return type() == c;
	}

	bool Patient::operator==(const Patient& patient)const
	{
		return type() == patient.type();
	}

	void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}

	Patient::operator Time()const
	{
		return (Time) m_ticket;
	}

	int Patient::number()const
	{
		return m_ticket.number();
	}

	std::ostream& Patient::csvWrite(std::ostream& ostr)const
	{
		ostr << type() << ',' << m_name << ',' << m_ohip << ',';
		m_ticket.csvWrite(ostr);
		return ostr;
	}

	std::istream& Patient::csvRead(std::istream& istr)
	{
		delete[] m_name;
		m_name = getcstr(nullptr, istr, ',');
		istr >> m_ohip;
		istr.ignore(1000, ',');
		m_ticket.csvRead(istr);

		return istr;
		
	}

	std::ostream& Patient::write(std::ostream& ostr)const
	{
		ostr << m_ticket << std::endl;
		std::string str = m_name;
		str = str.substr(0, 25);
		ostr << str << ", OHIP: " << m_ohip;

		return ostr;
	}

	std::istream& Patient::read(std::istream& istr)
	{
		delete[] m_name;
		m_name = getcstr("Name: ", istr);
		m_ohip = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ");

		return istr;
	}
}