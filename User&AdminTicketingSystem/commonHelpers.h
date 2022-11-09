
// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Arman Valaee Asr
//  Student ID    : 139550206
//  Student Email : avalaee-asr@myseneca.ca
//  Course Section: ZCC
// ===================================================================================

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

int currentYear(void);
void clearStandardInputBuffer(void);

//1 Gets an Integar value
int getInteger(void);

//2 Gets a positive Integer value
int getPositiveInteger(void);

//3 Gets a double value
double getDouble(void);

//4 Gets a positive double value
double getPositiveDouble(void);

//5 Get an Integer and check if it is in a range
int  getIntFromRange(int lowerbound, int upperbound);

//6 Gets a char, and checks if the character is inside the considered string
char getCharOption(const char validchar[]);

//7 Gets a string between min and max length
void getCString(char Cstring[], int min, int max);

#endif // !COMMON_HELPERS_H_