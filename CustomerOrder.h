// Name: Ivan Leung
// Seneca Student ID: 032657132
// Seneca email: ihleung1@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>


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
		};

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};

		static unsigned int m_widthField;

		public:
			CustomerOrder();
			~CustomerOrder();
			CustomerOrder(const CustomerOrder& copy);
			CustomerOrder& operator=(const CustomerOrder& copy) = delete;
			CustomerOrder(CustomerOrder&& copy) noexcept;
			CustomerOrder& operator=(CustomerOrder&& copy) noexcept;
			CustomerOrder(const std::string& customerOrder);
			bool isOrderFilled() const;
			bool isItemFilled(const std::string& itemName) const;
			void fillItem(Station& station, std::ostream& os);
			void display(std::ostream& os) const;
			
	};
}

#endif