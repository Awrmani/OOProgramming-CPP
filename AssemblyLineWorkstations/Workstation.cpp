// Name: Arman Valaee Asr
// Seneca Student ID: 139550206
// Seneca email: avalaee-asr@myseneca.ca
// Date of completion: 2021-12-4
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"

namespace sdds
{
	Workstation::Workstation(const std::string& str) : Station(str)
	{
		// Do Nothing
	}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
				m_orders.front().fillItem(*this, os);
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool result = false;
		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() < 1)
			{
				if (!m_pNextStation)
				{
					if (m_orders.front().isFilled())
						completed.push_back(std::move(m_orders.front()));
					else
						incomplete.push_back(std::move(m_orders.front()));

					m_orders.pop_front();
					result = true;
				}
				else
				{
					*m_pNextStation += std::move(m_orders.front());
					m_orders.pop_front();
					result = true;
				}
			}
		}
		return result;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";
		if (m_pNextStation)
			os << m_pNextStation->getItemName();
		else
			os << "End of Line";
		os << std::endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{	
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}