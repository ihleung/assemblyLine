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
#include <sstream>
#include <algorithm> 
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"
#include "Workstation.h"
#include "LineManager.h"

namespace sdds
{
    LineManager::LineManager() = default;

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
        Utilities util;
        util.setDelimiter('|');
       
        std::ifstream fstr(file);

        if (fstr)
        {
           do
           {
                bool more{};
                size_t nextPos{};
                std::string temp{};
                std::getline(fstr, temp);
                if (fstr)
                {
                    std::string currentStation{};
                    currentStation = util.extractToken(temp, nextPos, more);

                    std::string nextStation{};
                    nextStation = util.extractToken(temp, nextPos, more);

                    auto station1 = std::find_if(stations.begin(), stations.end(), [&](Workstation* lineStation)
                        {
                            bool stop = false;
                            if (lineStation->getItemName() != currentStation)
                            {
                                stop = false;
                            }
                            else
                            {
                                stop = true;
                            }
                            return stop;
                        });

                    auto station2 = std::find_if(stations.begin(), stations.end(), [&](Workstation* lineStation)
                        {
                            bool stop = false;
                            if (lineStation->getItemName() != nextStation)
                            {
                                stop = false;
                            }
                            else
                            {
                                stop = true;
                            }
                            return stop;
                        });

                    if (station1 == stations.end())
                    {
                        throw std::string("Error! " + currentStation + " does not exist");
                    }
                    else
                    {
                        m_activeLine.push_back(*station1);
                        if (station2 != station1 && station2 != stations.end())
                        {
                            (*station1)->setNextStation(*station2);
                        }
                    }
                }
           } while (fstr.good());

           auto firstStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* lineStation)
               {
                   return std::find_if(m_activeLine.begin(), m_activeLine.end(), [lineStation](Workstation* lineManageStation)
                       {
                           bool stop = false;
                           if (lineManageStation != lineStation && lineManageStation->getNextStation() == lineStation)
                           {
                               stop = true;
                           }
                           return stop;
                       }) == m_activeLine.end();
               });

           m_firstStation = *firstStation;
           m_cntCustomerOrder = g_pending.size();
        }
        else
        {
            throw std::string("File is incorrect...");
        }
	}

	void LineManager::reorderStations()
	{
        std::vector<Workstation*> tempStation{};
        Workstation* recentStation{};

        recentStation = m_firstStation;

        do
        {
            tempStation.push_back(recentStation);
            recentStation = recentStation->getNextStation();

        } while (recentStation);

        m_activeLine = std::move(tempStation);
	}

	bool LineManager::run(std::ostream& os)
	{
        bool stop = false;
        static int count = 0;

        count = count + 1;

        os << "Line Manager Iteration: " << count << std::endl;

        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto& lineStation : m_activeLine)
        {
            lineStation->fill(os);
        }

        for (auto& lineStation : m_activeLine)
        {
            lineStation->attemptToMoveOrder();
        }

        unsigned int totalSize{};
        totalSize = g_completed.size() + g_incomplete.size();

        if (totalSize != m_cntCustomerOrder)
        {
            stop = false;
        }
        else
        {
            stop = true;
        }
        return stop;
      
	}

	void LineManager::display(std::ostream& os) const
	{
        for (auto& lineStation : m_activeLine)
        {
            lineStation->display(os);
        }
	}
}