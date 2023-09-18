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
#include "Workstation.h"


namespace sdds
{
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation() = default;

	Workstation::Workstation(const std::string& work) : Station(work)
	{

	}
	
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool stop = false;
		if (!m_orders.empty())
		{
			CustomerOrder& customer = m_orders.front();

			if (customer.isItemFilled(getItemName()) || getQuantity() == 0)
			{
				if (!m_pNextStation)
				{
					if (!customer.isOrderFilled())
					{
						g_incomplete.push_back(std::move(customer));
						m_orders.pop_front();
					}
					else
					{
						g_completed.push_back(std::move(customer));
						m_orders.pop_front();
					}
					stop = true;
				}
				else
				{
					*m_pNextStation += std::move(customer); 
					m_orders.pop_front();
					stop = true;
				}
			}

		}
		return stop;

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
		{
			os << m_pNextStation->getItemName() << std::endl;
		}
		else 
		{
			os << "End of Line" << std::endl;
		}
		
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}