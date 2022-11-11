// Name: Arman Valaee Asr
// Seneca Student ID: 139550206
// Seneca email: avalaee-asr@myseneca.ca
// Date of completion: 2021-12-4
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds
{
	size_t CustomerOrder::m_widthField;
	CustomerOrder::CustomerOrder()
	{
		m_name = "";
		m_product = "";
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& record)
	{
		Utilities util;
		bool more = true;
		size_t nextPos = 0;
		m_name = util.extractToken(record, nextPos, more);
		m_product = util.extractToken(record, nextPos, more);
		size_t pos = nextPos;
		while (more)
		{
			util.extractToken(record, nextPos, more);
			++m_cntItem;
		}

		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++)
			m_lstItem[i] = new Item(util.extractToken(record, pos, more));

		m_widthField = m_widthField > util.getFieldWidth() ? m_widthField : util.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& order)
	{
		throw "Error! Copy constructor is not allowed.";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept
	{
		*this = std::move(order);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept
	{
		if (this != &order)
		{
			m_name = order.m_name;
			order.m_name = "";
			m_product = order.m_product;
			order.m_product = "";
			
			if (m_lstItem)
				for (size_t i = 0; i < m_cntItem; i++)
					delete m_lstItem[i];
			delete[] m_lstItem;

			m_cntItem = order.m_cntItem;
			order.m_cntItem = 0;
			m_lstItem = order.m_lstItem;

			order.m_lstItem = nullptr;
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem)
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];
		delete[] m_lstItem;
		m_lstItem = nullptr;
		m_cntItem = 0;
		m_name = "";
		m_product = "";
	}

	bool CustomerOrder::isFilled() const
	{
		bool result = true;
		for (size_t i = 0; i < m_cntItem; i++)
			if (!m_lstItem[i]->m_isFilled)
				result = false;

		return result;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool result = true;
		for (size_t i = 0; i < m_cntItem; i++)
			if (m_lstItem[i]->m_itemName == itemName)
				if (!m_lstItem[i]->m_isFilled)
					result = false;

		return result;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() >= 1)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << std::setfill(' ') << "] ";
			os << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled)
				os << "FILLED";
			else
				os << "TO BE FILLED";
			os << std::right << std::endl;
		}
	}
}