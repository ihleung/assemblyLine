// Name: Ivan Leung
// Seneca Student ID: 032657132
// Seneca email: ihleung1@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>


namespace sdds
{
	class Utilities
	{
		unsigned int m_widthField{ 1 };
		static char m_delimiter;
		
		public:
			Utilities();
			void setFieldWidth(size_t newWidth);
			size_t getFieldWidth() const;
			std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
			static void setDelimiter(char newDelimiter);
			static char getDelimiter();
	};
	std::string setFormat(std::string& s);
}

#endif