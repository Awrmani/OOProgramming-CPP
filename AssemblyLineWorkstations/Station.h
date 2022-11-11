// Name: Arman Valaee Asr
// Seneca Student ID: 139550206
// Seneca email: avalaee-asr@myseneca.ca
// Date of completion: 2021-12-4
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_

#include <string>

namespace sdds
{
	class Station
	{
		int m_stationID;
		std::string m_itemName;
		std::string m_desc;
		size_t m_serialNo;
		size_t m_quantity;
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H_
