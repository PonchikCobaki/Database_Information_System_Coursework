#include "Account.h"



#ifndef ARRAY_H
#define ARRAY_H


enum ArrayDefinoons {
	DEFAULT_ARRAY_EXTEND = 1,
};


class Array
{
private:
	u_int _members;
	u_int _size;
	Account* _array;

	void _defaultExtend(Account* oldArray);
	void _move(const u_int& id, const bool invertion = false);


public:
	Array();
	Array(u_int members);

	~Array();


	Account& operator[] (const long int id);

	void append(const u_int id, const Account& user);
	void del(const u_int id);

	u_int getSize();

};

#endif // ARRAY_H