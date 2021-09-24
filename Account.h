#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <Windows.h>


namespace my {

	enum StringFieldLength	//	перечесление размеров поля имен в структуре
	{
		LENGTH_FIRST_NAME = 25,
		LENGTH_LAST_NAME = 25,
	};


	class Account
	{
	private:
		void m_charInit();
		char* m_firstNameCh;
		char* m_lastNameCh;

		std::string m_firstName;
		std::string m_lastName;
		uint16_t m_mathScore;
		uint16_t m_ruLangScore;
		uint16_t m_enLangScore;
		uint16_t m_writeSize;

	public:
		Account();
		Account(std::string firstName, std::string lastName,
			uint16_t mathScore = 0, uint16_t ruLangScore = 0, uint16_t enLangScore = 0);

		~Account();


		void operator= (Account& user);
		void operator= (const Account& user);

		char* getFirstNameChar();
		char* getLastNameChar();

		std::string getFirstName();
		void setFirstName(std::string firstName);
		std::string getLastName();
		void setLastName(std::string lastName);

		uint16_t getMathScore();
		void setMathScore(uint16_t mathScore);
		uint16_t getRuLangScore();
		void setRuLangScore(uint16_t ruLangScore);
		uint16_t getEnLangScore();
		void setEnLangScore(uint16_t enLangScore);

		uint16_t getTotalScore();
		uint16_t getWriteSize();
	};

}
#endif // ACCOUNT_H

