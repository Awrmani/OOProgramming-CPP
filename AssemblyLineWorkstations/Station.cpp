// Name: Arman Valaee Asr
// Seneca Student ID: 139550206
// Seneca email: avalaee-asr@myseneca.ca
// Date of completion: 2021-12-4
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;;
	Station::Station(const std::string& record)
	{
		Utilities util;
		bool more = true;
		size_t nextPos = 0;
		m_stationID = ++id_generator;
		m_itemName = util.extractToken(record, nextPos, more);
		m_serialNo = std::stoi(util.extractToken(record, nextPos, more));
		m_quantity = std::stoi(util.extractToken(record, nextPos, more));
		m_widthField = m_widthField > util.getFieldWidth() ? m_widthField : util.getFieldWidth();
		m_desc = util.extractToken(record, nextPos, more);
	}

	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serialNo++;
	}

	size_t Station::getQuantity() const
	{
		return m_quantity;
	}

	void Station::updateQuantity()
	{
		if (m_quantity > 0)
			--m_quantity;
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << "[" << std::setfill('0') << std::setw(3) << m_stationID << "] Item: "
			<< std::setfill(' ') << std::left << std::setw(m_widthField) << m_itemName
			<< " [" << std::right << std::setfill('0') << std::setw(6) << m_serialNo << "]" << std::setfill(' ');
		if (full)
			os << " Quantity: " << std::setw(m_widthField) << std::left << m_quantity << " Description: " << m_desc;
		os << std::endl << std::right;
	}
}