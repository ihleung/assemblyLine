// Name: Ivan Leung
// Seneca Student ID: 032657132
// Seneca email: ihleung1@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>


namespace sdds
{
	class Station 
	{
		int stationID{};
		std::string itemName{};
		std::string stationDescription{};
		unsigned int serialNumber{};
		unsigned int noOfItems{};
		static unsigned int m_widthField;
		static int id_generator;

		public:
			Station();
			Station(const std::string& stationRecord);
			const std::string& getItemName() const;
			size_t getNextSerialNumber();
			size_t getQuantity() const;
			void updateQuantity();
			void display(std::ostream& os, bool full) const;

	};

}

#endif