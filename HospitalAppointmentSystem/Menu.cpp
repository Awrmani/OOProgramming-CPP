/*
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
Author	Arman Valaee Asr
avalaee-asr@myseneca.ca - 139550206
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
#include "utils.h"

namespace sdds
{
	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{
		m_text = new char[strlen(MenuContent) + 1];
		strcpy(m_text, MenuContent);
		m_noOfSel = NoOfSelections;
	}

	Menu::Menu(const Menu& menu)
	{
		m_text = new char[strlen(menu.m_text) + 1];
		strcpy(m_text, menu.m_text);
		m_noOfSel = menu.m_noOfSel;
	}
	 
	Menu::~Menu()
	{
		delete[] m_text;
		m_text = nullptr;
	}

	void Menu::display()const
	{
		std::cout << m_text << std::endl;
		std::cout << "0- Exit" << std::endl;
	}

	int& Menu::operator>>(int& Selection)
	{
		display();
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);
		return Selection;
	}
}