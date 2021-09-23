#include "Array.h"


void Array::_defaultExtend(Account* oldArray) {
	_size = _members + 1 + DEFAULT_ARRAY_EXTEND;
	Account* bufferArray = new Account[_size];
	for (u_int i(0); i < _members; ++i)
		bufferArray[i] = _array[i];

	if (_array)
		delete[] _array;

	_array = bufferArray;
}

void Array::_move(const u_int& id, const bool invertion)
{
	if (invertion) {	// удаление элемента

		for (u_int i = id; i < _members - 1; ++i) {
			_array[i] = _array[i + 1];
		}
		--_members;
	}
	else {	// добавление элемента
		if (_members >= _size) 	// расширение массива
			_defaultExtend(_array);

		for (u_int i(_members + 1 - 1); i > id; --i)
			_array[i] = _array[i - 1];
	
		++_members;
	}

}

Array::Array() {
	_members = 0;
	_size = DEFAULT_ARRAY_EXTEND;
	_array = new Account[_size];
	std::cout << "zero Array create" << std::endl;
}
Array::Array(u_int members) : _members(members),
_size(members + DEFAULT_ARRAY_EXTEND)
{
	_array = new Account[_size];
	std::cout << "Array create" << std::endl;
}

Array::~Array()
{
	if (_array) {
		delete[] _array;
	}
	std::cout << "Array destruct\n";
}


Account& Array::operator[] (const long int id) {
	try {
		if (id >= long int(_members) || -id < -long int(_members) ) {
			throw "\nindex out of range: ";
		}

		if (id >= 0)
			return _array[id];
		else
			return _array[id + _members];
	}
	catch (const char* str) {
		std::cerr << str << id << std::endl;
		return _array[_size - 1];
	}
}

void Array::append(const u_int id, const Account& user) {
	try {
		if (id > _members) {
			throw "\nindex out of range: ";
		}
		_move(id);
		_array[id] = user;
	}
	catch (const char* str) {
		std::cerr << str << id << std::endl;
	}
}

void Array::del(const u_int id) {
	try {
		if (id >= _members) {
			throw "\nindex out of range: ";
		}
		_move(id, true);
	}
	catch (const char* str) {
		std::cerr << str << id << std::endl;
	}
}

u_int Array::getSize() {
	return _members;
}
