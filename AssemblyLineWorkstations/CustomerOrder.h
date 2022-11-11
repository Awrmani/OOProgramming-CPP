// Name: Arman Valaee Asr
// Seneca Student ID: 139550206
// Seneca email: avalaee-asr@myseneca.ca
// Date of completion: 2021-12-4
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_

#include <string>
#include "Station.h"

namespace sdds
{
	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
			Item() {};
		};

		std::string m_name;
		std::string m_product;
		size_t m_cntItem = 0;
		Item** m_lstItem{};
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string& record);
		CustomerOrder(const CustomerOrder& order);
		CustomerOrder& operator=(const CustomerOrder& order) = delete;
		CustomerOrder(CustomerOrder&& order) noexcept;
		CustomerOrder& operator=(CustomerOrder&& order) noexcept;
		~CustomerOrder();

		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_CUSTOMERORDER_H_
