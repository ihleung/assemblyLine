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
#include "Station.h"
#include "Utilities.h"


namespace sdds
{
	int Station::id_generator{ 0 };
	unsigned int Station::m_widthField{ 0 };

	Station::Station() = default;

	Station::Station(const std::string& stationRecord)
	{
		Utilities util{};
		size_t nextPos{};
		bool more = true;
		
		stationID = ++id_generator;
		std::string name{};
		name = util.extractToken(stationRecord, nextPos, more);

		std::string stationNumber{};
		stationNumber = util.extractToken(stationRecord, nextPos, more);
		unsigned int number{};
		number = std::stoi(stationNumber);

		std::string stationItem{};
		stationItem = util.extractToken(stationRecord, nextPos, more);
		unsigned int items{};
		items = std::stoi(stationItem);
		

		if (util.getFieldWidth() > m_widthField)
		{
			m_widthField = util.getFieldWidth();
		}

		std::string desc{};
		desc = util.extractToken(stationRecord, nextPos, more);
		
		itemName = name;
		serialNumber = number;
		noOfItems = items;
		stationDescription = desc;
	}

	const std::string& Station::getItemName() const
	{
		return itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		return serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return noOfItems;
	}

	void Station::updateQuantity()
	{
		if (noOfItems > 0)
		{
			--noOfItems;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << std::right << std::setfill('0');
		os << std::setw(3) << stationID << " | ";
		os << std::left << std::setfill(' ');
		os << std::setw(m_widthField) << itemName << " | ";
		os << std::right << std::setfill('0');
		os << std::setw(6) << serialNumber << " | ";

		if (full) 
		{
			os << std::setfill(' ') << std::right << std::setw(4) << noOfItems << " | ";
			os << std::left << stationDescription;
		}
		os << std::endl;
	}
}