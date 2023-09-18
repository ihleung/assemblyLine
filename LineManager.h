// Name: Ivan Leung
// Seneca Student ID: 032657132
// Seneca email: ihleung1@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <deque>
#include "CustomerOrder.h"
#include "Workstation.h"

namespace sdds
{
	class LineManager
	{
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};

		public:
			LineManager();
			LineManager(const std::string& file, const std::vector<Workstation*>& stations);
			void reorderStations();
			bool run(std::ostream& os);
			void display(std::ostream& os) const;

	};
}

#endif