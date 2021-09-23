#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <Windows.h>



enum StringFieldLength	//	перечесление размеров поля имен в структуре
{
	LENGTH_FIRST_NAME = 25,
	LENGTH_LAST_NAME = 25,
};


class Account
{
private:
	void _charInit();
	char* _firstNameCh;
	char* _lastNameCh;

	std::string _firstName;
	std::string _lastName;
	u_short _mathScore;
	u_short _ruLangScore;
	u_short _enLangScore;

public:
	Account();
	Account(std::string firstName, std::string lastName,
		u_short mathScore = 0, u_short ruLangScore = 0, u_short enLangScore = 0);

	~Account();


	void operator= (Account& user);
	void operator= (const Account& user);

	char* getFirstNameChar();
	char* getLastNameChar();

	std::string getFirstName();
	void setFirstName(std::string firstName);
	std::string getLastName();
	void setLastName(std::string lastName);

	const u_short* getMathScore();
	void setMathScore(u_short mathScore);
	const u_short* getRuLangScore();
	void setRuLangScore(u_short ruLangScore);
	const u_short* getEnLangScore();
	void setEnLangScore(u_short enLangScore);
	const u_short getTotalScore();
};

#endif // ACCOUNT_H