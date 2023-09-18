// Name: Ivan Leung
// Seneca Student ID: 032657132
// Seneca email: ihleung1@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm> 
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"


namespace sdds
{
	unsigned int CustomerOrder::m_widthField{};

	CustomerOrder::CustomerOrder() = default;
	
	CustomerOrder::~CustomerOrder()
	{
		for (unsigned int i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		delete[]m_lstItem;
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& copy)
	{
		throw std::string("Copy constructor is not allow copy operations.");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& copy) noexcept
	{
		*this = std::move(copy);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& copy) noexcept
	{
		if (this != &copy)
		{
			for (unsigned int i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
			m_name = copy.m_name;
			m_product = copy.m_product;
			m_lstItem = copy.m_lstItem;
			copy.m_lstItem = nullptr;
			m_cntItem = copy.m_cntItem;
			copy.m_cntItem = 0;

		}
		return *this;
	}

	CustomerOrder::CustomerOrder(const std::string& customerOrder)
	{
		Utilities util{};
		size_t nextPos{};
		bool more = true;
		
		
		std::string customerName{};
		customerName = util.extractToken(customerOrder, nextPos, more);

		std::string orderName{};
		orderName = util.extractToken(customerOrder, nextPos, more);
		
		unsigned int newPos{};
		newPos = nextPos;

		do
		{
			util.extractToken(customerOrder, nextPos, more);
			m_cntItem++;
			
		} while (more);

		nextPos = newPos;
		more = true;

		m_lstItem = new Item * [m_cntItem];

		for (unsigned int i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(util.extractToken(customerOrder, nextPos, more));
		}

		if (util.getFieldWidth() > m_widthField)
		{
			m_widthField = util.getFieldWidth();
		}

		m_name = customerName;
		m_product = orderName;

	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool stop = true;
		for (unsigned int i = 0; i < m_cntItem; i++)
		{
			if (!(m_lstItem[i]->m_isFilled))
			{
				stop = false;
			}
		}
		return stop;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool stop = true;
		bool flag = false;
		for (unsigned int i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				flag = true;
			}
		}

		if (flag)
		{
			for (unsigned int i = 0; i < m_cntItem; i++) 
			{
				if (m_lstItem[i]->m_itemName == itemName) 
				{
					if (!m_lstItem[i]->m_isFilled) 
					{
						stop = false;
					}
				}
			}
		}
		else
		{
			stop = true;
		}

		return stop;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool stop = false;
		for (unsigned int i = 0; i < m_cntItem && !stop; i++)
		{
			if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled)
			{
				if (!station.getQuantity())
				{
					os << "    Unable to fill " << m_name;
					os << ", " << m_product << " [";
					os << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else
				{
					stop = true;
					station.updateQuantity();
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					os << "    Filled " << m_name << ", ";
					os << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
			
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (unsigned int i = 0; i < m_cntItem; i++)
		{
			os << std::setfill('0') << "[" << std::setw(6);
			os << std::right << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setfill(' ') << std::left << std::setw(m_widthField);
			os << m_lstItem[i]->m_itemName << " - ";
			if (!m_lstItem[i]->m_isFilled)
			{
				os << "TO BE FILLED" << std::endl;
			}
			else
			{
				os << "FILLED" << std::endl;
			}
			
		}
	}
}