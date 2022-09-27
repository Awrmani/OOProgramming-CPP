//--------------------------------------
// Workshop 1							
//										
// Arman Valaee Asr - 139550206			
// avalaee-asr@myseneca.ca				
//										
// 2021-9-19							
//--------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "event.h"

unsigned int g_sysClock = 0;

namespace sdds
{
	Event::Event()
	{
		m_desc = nullptr;
		m_time = 0;
	}

	Event::Event(const Event& event)
	{
		if (event.m_desc)
		{
			m_desc = new char[strlen(event.m_desc) + 1];
			strncpy(m_desc, event.m_desc, strlen(event.m_desc) + 1);
			m_time = event.m_time;
		}
		else
		{
			m_desc = nullptr;
			m_time = 0;
		}
	}

	Event& Event::operator=(const Event& event)
	{
		if (this != &event)
		{
			if (event.m_desc)
			{
				delete[] m_desc;
				m_desc = new char[strlen(event.m_desc) + 1];
				strncpy(m_desc, event.m_desc, strlen(event.m_desc) + 1);
				m_time = event.m_time;
			}
			else
			{
				m_desc = nullptr;
				m_time = 0;
			}
		}
		return *this;
	}

	void Event::display() const
	{
		static unsigned int counter = 0;
		std::cout << std::setw(2) << std::setfill(' ') << ++counter << ". ";
		if (m_desc)
		{
			int MM = m_time / 60;
			int SS = m_time % 60;
			int HH = MM / 60;
			MM = MM % 60;
			std::cout << std::setw(2) << std::setfill('0') << HH << ":"
				<< std::setw(2) << std::setfill('0') << MM << ":"
				<< std::setw(2) << std::setfill('0') << SS << " => " << m_desc << std::endl;
		}
		else
			std::cout << "| No Event |" << std::endl;
	}

	void Event::set(const char* arr)
	{
		m_time = ::g_sysClock;
		if (arr != nullptr)
		{
			delete[] m_desc;
			m_desc = new char[strlen(arr) + 1];
			strncpy(m_desc, arr, strlen(arr) + 1);
		}
		else
		{
			delete[] m_desc;
			m_desc = nullptr;
		}
	}

	Event::~Event()
	{
		delete[] m_desc;
		m_desc = nullptr;
	}
}