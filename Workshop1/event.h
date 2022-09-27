//--------------------------------------
// Workshop 1							
//										
// Arman Valaee Asr - 139550206			
// avalaee-asr@myseneca.ca				
//										
// 2021-9-19							
//--------------------------------------

#ifndef SDDS_EVENT_H_
#define SDDS_EVENT_H_

extern unsigned int g_sysClock;

namespace sdds
{

	class Event
	{
		char* m_desc;
		unsigned int m_time;
	public:
		Event();
		Event(const Event& event);
		Event& operator=(const Event& event);
		void display() const;
		void set(const char* arr = nullptr);
		~Event();
	};
}

#endif // !SDDS_EVENT_H_
