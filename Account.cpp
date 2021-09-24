#include "Account.h"


using namespace my;

void Account::m_charInit() {
	m_firstNameCh = new char[LENGTH_FIRST_NAME];
	m_lastNameCh = new char[LENGTH_LAST_NAME];
}

Account::Account()
{
	m_charInit();
	std::string m_firstName = "имя не задано";
	std::string m_lastName = "фамилия не задана";
	uint16_t m_mathScore = 0;
	uint16_t m_ruLangScore = 0;
	uint16_t m_enLangScore = 0;
	std::cout << "zero Account create" << std::endl;
}
Account::Account(std::string firstName,	std::string lastName,
	uint16_t mathScore, uint16_t ruLangScore, uint16_t enLangScore)
	: m_firstName(firstName), m_lastName(lastName),
	m_mathScore(mathScore), m_ruLangScore(ruLangScore), m_enLangScore(enLangScore)
{
	m_charInit();
	std::cout << "Account create" << std::endl;
}

Account::~Account() {
	if (m_firstNameCh) {
		delete[] m_firstNameCh;
	}
	if (m_firstNameCh) {
		delete[] m_lastNameCh;
	}
	std::cout << "Account destruct\n";
}

void Account::operator= (Account& user) {
	m_firstName = user.getFirstName();
	m_lastName = user.getLastName();
	m_mathScore = user.getMathScore();
	m_ruLangScore = user.getRuLangScore();
	m_enLangScore = user.getEnLangScore();
}
void Account::operator= (const Account& user) {
	this->m_firstName = user.m_firstName;
	this->m_lastName = user.m_lastName;
	this->m_mathScore = user.m_mathScore;
	this->m_ruLangScore = user.m_ruLangScore;
	this->m_enLangScore = user.m_enLangScore;
}

char* Account::getFirstNameChar() {
	strcpy_s(m_firstNameCh, LENGTH_FIRST_NAME, m_firstName.c_str());
	return m_firstNameCh;
}

char* Account::getLastNameChar() {
	strcpy_s(m_lastNameCh, LENGTH_FIRST_NAME, m_lastName.c_str());
	return m_lastNameCh;
}

std::string Account::getFirstName() {
	return m_firstName;
}

void Account::setFirstName(std::string firstName) {
	m_firstName = firstName;
}

std::string Account::getLastName() {
	return m_lastName;
}

void Account::setLastName(std::string lastName) {
	m_lastName = lastName;
}

uint16_t Account::getMathScore() {
	return m_mathScore;
}

void Account::setMathScore(uint16_t mathScore) {
	m_mathScore = mathScore;
}

uint16_t Account::getRuLangScore() {
	return m_ruLangScore;
}

void Account::setRuLangScore(uint16_t ruLangScore) {
	m_ruLangScore = ruLangScore;
}

uint16_t Account::getEnLangScore() {
	return m_enLangScore;
}

void Account::setEnLangScore(uint16_t enLangScore) {
	m_enLangScore = enLangScore;
}

uint16_t Account::getTotalScore() {

	return m_mathScore + m_ruLangScore + m_enLangScore;
}

uint16_t Account::getWriteSize() {

	return sizeof(uint16_t) * 3 + sizeof(char) * LENGTH_FIRST_NAME + sizeof(char) * LENGTH_LAST_NAME;
}
