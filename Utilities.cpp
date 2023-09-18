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
#include "Utilities.h"


namespace sdds
{
    char Utilities::m_delimiter{};

    Utilities::Utilities() = default;

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string setFormat(std::string& s)
    {
        std::string format;
        unsigned int startOfString{};
        unsigned int endOfString{};
        startOfString = s.find_first_not_of(' ');
        endOfString = s.find_last_not_of(' ');
        format = s.substr(startOfString, endOfString - startOfString + 1);
        return format;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        std::string temp{};
        std::string token{};
        size_t newPos{};

        unsigned int startPos{};
        unsigned int endPos{};

        temp = str;
        newPos = temp.find(m_delimiter, next_pos);
        startPos = next_pos;
        endPos = newPos - next_pos;

        if (newPos != std::string::npos)
        {   
            if (newPos == next_pos) 
            {
                more = false;
                throw std::string("Delimiter is found at next_pos.");
            }
            token = temp.substr(startPos, endPos);
            next_pos = newPos + 1;
            more = true;
        }
        else
        {
            token = temp.substr(next_pos);
            more = false;
        }

        token = setFormat(token);
        if (m_widthField < token.length())
        {
            m_widthField = token.length();
        }
       
        return token;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}