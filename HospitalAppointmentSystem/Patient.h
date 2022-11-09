/*
Final Project Milestone 5
Module: Patient
Filename: Patient.h
Author	Arman Valaee Asr
avalaee-asr@myseneca.ca - 139550206
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include <string>
#include <cstring>
#include "IOAble.h"
#include "Ticket.h"
#include "utils.h"

namespace sdds
{
	class Patient : public IOAble
	{
		char* m_name = nullptr;
		unsigned int m_ohip = 0;
		Ticket m_ticket;
		bool m_ioFlag;
	public:
		Patient(int ticketNo = 0, bool ioFlag = false);
		Patient(const Patient& patient) = delete;
		Patient& operator=(const Patient&) = delete;
		~Patient();
		virtual char type()const = 0;
		bool fileIO()const;
		void fileIO(int ioFlag);
		bool operator==(char c)const;
		bool operator==(const Patient& patient)const;
		void setArrivalTime();
		operator Time()const;
		int number()const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}

#endif // !SDDS_PATIENT_H_
