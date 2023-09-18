// Name: Ivan Leung
// Seneca Student ID: 032657132
// Seneca email: ihleung1@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <deque>
#include "CustomerOrder.h"

namespace sdds
{
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{};

		public:
			Workstation();
			Workstation(const Workstation& copy) = delete;
			Workstation& operator=(const Workstation& copy) = delete;
			Workstation(Workstation&& copy) = delete;
			Workstation& operator=(Workstation&& copy) = delete;
			Workstation(const std::string& work);
			void fill(std::ostream& os);
			bool attemptToMoveOrder();
			void setNextStation(Workstation* station = nullptr);
			Workstation* getNextStation() const;
			void display(std::ostream& os) const;
			Workstation& operator+=(CustomerOrder&& newOrder);
	};
}


#endif