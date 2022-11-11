// Name: Arman Valaee Asr
// Seneca Student ID: 139550206
// Seneca email: avalaee-asr@myseneca.ca
// Date of completion: 2021-12-4
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds
{
	std::deque<CustomerOrder> pending;
	std::deque<CustomerOrder> completed;
	std::deque<CustomerOrder> incomplete;

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		try
		{
			if (file == "")
				throw "Wrong filename!";
			std::fstream fileOpen(file);
			if (!fileOpen)
				throw "Error! File is not open!";

			std::string temp, current, next;
			Utilities util;
			size_t pos = 0;
			bool more = false;
			while (std::getline(fileOpen, temp))
			{
				next = "";
				current = util.extractToken(temp, pos, more);
				if (more)
					next = util.extractToken(temp, pos, more);
				auto fn1 = [&](Workstation* recentWs)
				{
					if (recentWs->getItemName() == current)
					{
						auto fn2 = [&](Workstation* afterWs)
						{
							if (afterWs->getItemName() == next)
								recentWs->setNextStation(afterWs);
						};
						std::for_each(stations.begin(), stations.end(), fn2);
						activeLine.push_back(recentWs);
					}
				};
				std::for_each(stations.begin(), stations.end(), fn1);
			}
			m_firstStation = activeLine.front();
			m_cntCustomerOrder = pending.size();
		}
		catch (std::string errorMsg)
		{
			std::cout << errorMsg;
		}
		catch (...)
		{
			std::cout << "Error!";
		}
	}

	void LineManager::linkStations()
	{
		size_t element = 0;
		std::vector<Workstation*> tmpVec{ };
		tmpVec.push_back(m_firstStation);

		auto fn1 = [&](Workstation*)
		{
			auto fn2 = [&](Workstation* ws)
			{
				if (tmpVec[element]->getNextStation())
					if (tmpVec[element]->getNextStation()->getItemName() == ws->getItemName())
					{
						tmpVec.push_back(ws);
						++element;
					}
			};
			std::for_each(activeLine.begin(), activeLine.end(), fn2);
		};
		std::for_each(activeLine.begin(), activeLine.end(), fn1);
		if (!tmpVec.empty())
			activeLine = tmpVec;

	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t counter = 1;
		bool result = false;
		os << "Line Manager Iteration: " << counter << std::endl;
		if (!pending.empty())
		{
			(*m_firstStation).operator+=(std::move(pending.front()));
			pending.pop_front();
		}
		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
			(*i)->fill(os);

		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
			(*i)->attemptToMoveOrder();

		++counter;

		if (pending.empty() && (completed.size() + incomplete.size()) == m_cntCustomerOrder)
			result = true;

		return result;
	}

	void LineManager::display(std::ostream& os) const
	{
		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
			(*i)->display(os);
	}
}