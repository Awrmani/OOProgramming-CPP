/*
Final Project Milestone 5
Module: Time
Filename: Time.cpp
Author	Arman Valaee Asr
avalaee-asr@myseneca.ca - 139550206
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#include "Time.h"
#include "utils.h"

namespace sdds 
{
	Time& Time::setToNow()
	{
		m_min = getTime();
		return *this;
	}

	Time::Time(unsigned int min)
	{
		m_min = min;
	}

	std::ostream& Time::write(std::ostream& ostr) const
	{
		int hour, minute;
		hour = m_min / 60;
		minute = m_min % 60;
		ostr.width(2);
		ostr.fill('0');
		ostr << hour << ":";
		ostr.width(2);
		ostr << minute;

		return ostr;
	}

	std::istream& Time::read(std::istream& istr) 
	{
		int hour = -1, minute = -1;
		char deli;
		istr >> hour >> deli >> minute;
		if (hour < 0 || minute < 0 || deli != ':')
			istr.setstate(std::ios::failbit);
		else
			m_min = hour * 60 + minute;

		return istr;
	}

	Time& Time::operator-=(const Time& D)
	{
		if (m_min > D.m_min)
			m_min -= D.m_min;
		else
		{
			int diff = (D.m_min - m_min) / 60; // Time difference in hours
			int multi = (diff / 24) + 1;
			m_min += multi * 24 * 60;
			m_min -= D.m_min;
		}

		return *this;
	}

	Time Time::operator-(const Time& D)const
	{
		Time temp;
		if (m_min > D.m_min)
			temp.m_min = m_min - D.m_min;
		else
		{
			int diff = (D.m_min - m_min) / 60; // Time difference in hours
			int multi = (diff / 24) + 1;
			temp.m_min = m_min + (multi * 24 * 60);
			temp.m_min -= D.m_min;
		}

		return temp;
	}

	Time& Time::operator+=(const Time& D)
	{
		m_min += D.m_min;
		return *this;
	}

	Time Time::operator+(const Time& D)const
	{
		Time temp;
		temp.m_min = m_min + D.m_min;
		return temp;
	}
	
	Time& Time::operator=(unsigned int val)
	{
		m_min = val;
		return *this;
	}

	Time& Time::operator *= (unsigned int val)
	{
		m_min *= val;
		return *this;
	}

	Time& Time::operator /= (unsigned int val)
	{
		m_min /= val;
		return *this;
	}

	Time Time::operator *(unsigned int val)const
	{
		Time temp;
		temp.m_min = m_min * val;
		return temp;
	}

	Time Time::operator /(unsigned int val)const
	{
		Time temp;
		temp.m_min = m_min / val;
		return temp;
	}

	Time::operator unsigned int()const
	{
		return (int)m_min;
	}

	Time::operator int()const
	{
		return m_min;
	}
	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		D.write(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Time& D)
	{
		D.read(istr);
		return istr;
	}
}