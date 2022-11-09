/*
Final Project Milestone 5
Module: Menu
Filename: Menu.h
Author	Arman Valaee Asr
avalaee-asr@myseneca.ca - 139550206
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_

#include <cstring>
namespace sdds
{
    class Menu
    {
        char* m_text; // holds the menu content dynamically
        int m_noOfSel;  // holds the number of options displayed in menu content
        void display()const;

    public:
        Menu(const char* MenuContent, int NoOfSelections);
        Menu(const Menu& menu);
        virtual ~Menu();
        int& operator>>(int& Selection);
        Menu& operator=(const Menu&) = delete;
    };
}

#endif // !SDDS_MENU_H_
