// Name: Arman Valaee Asr
// Seneca Student ID: 139550206
// Seneca email: avalaee-asr@myseneca.ca
// Date of completion: 2021-12-4
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace sdds
{
	char Utilities::m_delimiter;
	void Utilities::setFieldWidth(size_t newWidth)
	{
		if (newWidth)
			m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		size_t pos1 = str.find(m_delimiter, next_pos);
		if (next_pos == pos1)
		{
			more = false;
			++next_pos;
			throw "delimeter at next_pos";
		}

		std::string newStr = "*empty*";
		if (pos1 == std::string::npos)
		{
			newStr = str.substr(next_pos);
			more = false;
			pos1 = 0;
		}
		else
		{
			more = true;
			newStr = str.substr(next_pos, pos1 - next_pos);
			++pos1;

		}

		next_pos = pos1;

		if (newStr.length() > m_widthField)
			setFieldWidth(newStr.length());

		return newStr;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		if (newDelimiter)
			m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}