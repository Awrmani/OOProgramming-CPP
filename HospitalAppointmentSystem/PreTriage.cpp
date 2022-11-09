/*
Final Project Milestone 5
Module: PreTriage
Filename: PreTriage.cpp
Author	Arman Valaee Asr
avalaee-asr@myseneca.ca - 139550206
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "PreTriage.h"

namespace sdds
{
	void PreTriage::reg()
	{
		if (m_lineupSize == maxNoOfPatients)
			std::cout << "Line up full!" << std::endl;
		else
		{
			int select = -1;
			bool exit = false;
			m_pMenu >> select;
			if (select == 1)
				m_lineup[m_lineupSize] = new CovidPatient();
			else if (select == 2)
				m_lineup[m_lineupSize] = new TriagePatient();
			else if (!select)
				exit = true;

			if (!exit)
			{
				m_lineup[m_lineupSize]->setArrivalTime();
				m_lineup[m_lineupSize]->fileIO(false);
				std::cout << "Please enter patient information: " << std::endl;
				std::cin >> *m_lineup[m_lineupSize];
				std::cout << std::endl << "******************************************" << std::endl << *m_lineup[m_lineupSize];
				std::cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << std::endl;
				std::cout << "******************************************" << std::endl << std::endl;
			}
			m_lineupSize++;
		}
	}

	void PreTriage::admit()
	{
		int select = -1;
		char type = '\0';
		bool exit = false;
		m_pMenu >> select;
		if (select == 1)
			type = 'C';
		else if (select == 2)
			type = 'T';
		else if (!select)
			exit = true;

		if (!exit)
		{
			int index = indexOfFirstInLine(type);
			if (index != -1)
			{
				std::cout << std::endl << "******************************************" << std::endl;
				m_lineup[index]->fileIO(false);
				std::cout << "Calling for ";
				std::cout << *m_lineup[index];
				std::cout << "******************************************" << std::endl << std::endl;
				setAverageWaitTime(*m_lineup[index]);
				removePatientFromLineup(index);
			}
		}
	}

	const Time PreTriage::getWaitTime(const Patient& p)const
	{
		unsigned int inLineNo = 0;
		for (int i = 0; i < m_lineupSize; i++)
			if (*m_lineup[i] == p)
				inLineNo++;

		return p == 'C' ? m_averCovidWait * inLineNo : m_averTriageWait * inLineNo;
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		int CT = p.operator sdds::Time().setToNow();
		int AWT = p == 'C' ? m_averCovidWait : m_averTriageWait;
		int PTN = p.number();
		int PTT = p.operator sdds::Time();
		if (p == 'C')
			m_averCovidWait = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
		else
			m_averTriageWait = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
	}

	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type)const
	{
		int index = -1;
		for (int i = 0; i < m_lineupSize && index == -1; i++)
			if (*m_lineup[i] == type)
				index = i;

		return index;
	}

	void PreTriage::load()
	{
		Patient* patient = 0;
		std::ifstream ifst;
		char deli = ',';
		char newType = 'x';
		std::cout << "Loading data..." << std::endl;
		ifst.open(m_dataFilename);

		if (ifst.is_open())
		{
			ifst >> m_averCovidWait >> deli >> m_averTriageWait;
			for (int i = 0; i < maxNoOfPatients && !ifst.fail(); i++)
			{
				ifst >> newType >> deli;
				if (newType == 'C' || newType == 'T')
				{
					if (newType == 'C')
						patient = new CovidPatient;
					else if (newType == 'T')
						patient = new TriagePatient;

					patient->fileIO(true);
					patient->csvRead(ifst);
					patient->fileIO(false);
					m_lineup[m_lineupSize] = (patient);
					m_lineupSize++;
					newType = 'x';
				}
			}
			if (!ifst.eof())
				std::cout << "Warning: number of records exceeded 100" << std::endl;
		}

		if (m_lineupSize == 0 || !ifst.is_open())
			std::cout << "No data or bad data file!" << std::endl << std::endl;
		else
			std::cout << m_lineupSize << " Records imported..." << std::endl << std::endl;

		if (ifst.is_open())
			ifst.close();
	}

	PreTriage::PreTriage(const char* dataFilename) : m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
		m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		if (dataFilename)
		{
			m_dataFilename = new char[strlen(dataFilename) + 1];
			strcpy(m_dataFilename, dataFilename);
		}
		load();
	}

	PreTriage::~PreTriage()
	{
		std::ofstream ofst;
		ofst.open(m_dataFilename);
		std::cout << "Saving Average Wait Times," << std::endl;
		std::cout << "   COVID Test: " << m_averCovidWait << std::endl;
		std::cout << "   Triage: " << m_averTriageWait << std::endl;
		std::cout << "Saving m_lineup..." << std::endl;
		if (ofst.is_open())
		{
			ofst << m_averCovidWait << "," << m_averTriageWait << std::endl;
			for (int i = 0; i < m_lineupSize; i++)
			{
				m_lineup[i]->csvWrite(ofst);
				ofst << std::endl;
				std::cout << i + 1 << "- ";
				m_lineup[i]->csvWrite(std::cout);
				std::cout << std::endl;
				delete m_lineup[i];
			}
			delete[] m_dataFilename;
			m_dataFilename = nullptr;
			std::cout << "done!" << std::endl;
			ofst.close();
		}
	}

	void PreTriage::run()
	{
		int select = -1;
		while (select)
		{
			m_appMenu >> select;
			if (select == 1)
				reg();
			else if (select == 2)
				admit();
		}
	}

}