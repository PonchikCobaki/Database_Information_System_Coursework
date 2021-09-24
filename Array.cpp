#include "Array.h"


using namespace my;

void Array::m_defaultExtend(Account* oldArray) {
	m_size = m_members + 1 + DEFAULT_ARRAY_EXTEND;
	Account* bufferArray = new Account[m_size];
	for (u_int i(0); i < m_members; ++i)
		bufferArray[i] = m_array[i];

	if (m_array)
		delete[] m_array;

	m_array = bufferArray;
}

void Array::m_move(const u_int& id, const bool invertion)
{
	if (invertion) {	// удаление элемента

		for (u_int i = id; i < m_members - 1; ++i) {
			m_array[i] = m_array[i + 1];
		}
	}
	else {	// добавление элемента
		if (m_members >= m_size) 	// расширение массива
			m_defaultExtend(m_array);

		for (u_int i(m_members + 1 - 1); i > id; --i)
			m_array[i] = m_array[i - 1];
	}

}

Array::Array() {
	m_members = 0;
	m_size = DEFAULT_ARRAY_EXTEND;
	m_array = new Account[m_size];
	std::cout << "zero Array create" << std::endl;
}
Array::Array(u_int members) : m_members(members),
m_size(members + DEFAULT_ARRAY_EXTEND)
{
	m_array = new Account[m_size];
	std::cout << "Array create" << std::endl;
}

Array::~Array()
{
	if (m_array) {
		delete[] m_array;
	}
	std::cout << "Array destruct\n";
}


Account& Array::operator[] (const long int id) {
	try {
		if ((id >= long int(m_members) || -id < -long int(m_members)) && m_members != 0) {
			throw "\nindex out of range: ";
		}

		if (id >= 0)
			return m_array[id];
		else
			return m_array[id + m_members];
	}
	catch (const char* str) {
		std::cerr << str << id << std::endl;
		return m_array[m_size - 1];
	}
}

Array& Array::append(const u_int id, const Account& user) {
	try {
		if (id >= m_members) {
			throw "\nindex out of range: ";
		}
		m_move(id);
		m_array[id] = user;
		++m_members;
	}
	catch (const char* str) {
		std::cerr << str << id << std::endl;
	}

	return *this;
}

Array& Array::pushBack(const Account& user) {
	m_move(m_members);
	m_array[m_members] = user;
	++m_members;
	return *this;
}

Array& Array::del(const u_int id) {
	try {
		if (id >= m_members) {
			throw "\nindex out of range: ";
		}
		m_move(id, true);
		--m_members;
	}
	catch (const char* str) {
		std::cerr << str << id << std::endl;
	}

	return *this;
}

Array& Array::clear() {
	if (m_array) {
		delete[] m_array;
	}
	m_members = 0;
	m_size = DEFAULT_ARRAY_EXTEND;

	return *this;
}


u_int Array::getSize() {
	return m_members;
}
