#ifndef ARRAY_H
#define ARRAY_H

#include "Account.h"


namespace my {

	enum ArrayDefinoons {
		DEFAULT_ARRAY_EXTEND = 8,
	};


	class Array
	{
	private:
		u_int m_members;
		u_int m_size;
		Account* m_array;

		void m_defaultExtend(Account* oldArray);
		void m_move(const u_int& id, const bool invertion = false);


	public:
		Array();
		Array(u_int members);

		~Array();


		Account& operator[] (const long int id);
		

		Array& append(const u_int id, const Account& user);
		Array& pushBack(const Account& user);
		Array& del(const u_int id);
		Array& reverse();
		Array& clear();

		u_int getSize();

	};
}

#endif // ARRAY_H