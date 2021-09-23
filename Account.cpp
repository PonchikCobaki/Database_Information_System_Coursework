#include "Account.h"

void Account::_charInit() {
	_firstNameCh = new char[LENGTH_FIRST_NAME];
	_lastNameCh = new char[LENGTH_LAST_NAME];
}

Account::Account()
{
	_charInit();
	std::string _firstName = "имя не задано";
	std::string _lastName = "фамилия не задана";
	u_short _mathScore = 0;
	u_short _ruLangScore = 0;
	u_short _enLangScore = 0;
	std::cout << "zero Account create" << std::endl;
}
Account::Account(std::string firstName,	std::string lastName,
	u_short mathScore, u_short ruLangScore, u_short enLangScore)
	: _firstName(firstName), _lastName(lastName),
	_mathScore(mathScore), _ruLangScore(ruLangScore), _enLangScore(enLangScore)
{
	_charInit();
	std::cout << "Account create" << std::endl;
}

Account::~Account() {
	if (_firstNameCh) {
		delete[] _firstNameCh;
	}
	if (_firstNameCh) {
		delete[] _lastNameCh;
	}
	std::cout << "Account destruct\n";
}

void Account::operator= (Account& user) {
	_firstName = user.getFirstName();
	_lastName = user.getLastName();
	_mathScore = user.getMathScore();
	_ruLangScore = user.getRuLangScore();
	_enLangScore = user.getEnLangScore();
}
void Account::operator= (const Account& user) {
	this->_firstName = user._firstName;
	this->_lastName = user._lastName;
	this->_mathScore = user._mathScore;
	this->_ruLangScore = user._ruLangScore;
	this->_enLangScore = user._ruLangScore;
}

char* Account::getFirstNameChar() {
	strcpy_s(_firstNameCh, LENGTH_FIRST_NAME, _firstName.c_str());
	return _firstNameCh;
}

char* Account::getLastNameChar() {
	strcpy_s(_lastNameCh, LENGTH_FIRST_NAME, _lastName.c_str());
	return _lastNameCh;
}

std::string Account::getFirstName() {
	return _firstName;
}

void Account::setFirstName(std::string firstName) {
	_firstName = firstName;
}

std::string Account::getLastName() {
	return _lastName;
}

void Account::setLastName(std::string lastName) {
	_lastName = lastName;
}

u_short Account::getMathScore() {
	return _mathScore;
}

void Account::setMathScore(u_short mathScore) {
	_mathScore = mathScore;
}

u_short Account::getRuLangScore() {
	return _ruLangScore;
}

void Account::setRuLangScore(u_short ruLangScore) {
	_ruLangScore = ruLangScore;
}

u_short Account::getEnLangScore() {
	return _enLangScore;
}

void Account::setEnLangScore(u_short enLangScore) {
	_enLangScore = enLangScore;
}

u_short Account::getTotalScore() {

	return _mathScore + _ruLangScore + _enLangScore;
}


