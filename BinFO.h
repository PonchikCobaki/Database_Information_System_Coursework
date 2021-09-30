#pragma once

#include "Account.h"
#include "Array.h"
#include <Windows.h>
#include <string>
#include <iostream>

enum LengthOfTableFields	// перечисленпие кол-ва читаемых учетных записей 
{
	DATA_FIELD_LENGTH = 14,	// кол-во читаемых учетных записей выводимых в консоль
};

enum IndexConst {
	IND_CONV_FACTOR = 1, // index conversion factor
};

enum DataBuffersSize {
	SUBFILE_SIZE = 7 * DATA_FIELD_LENGTH, // 7*14=98; размер подфайлов для удаления/изменения данных
};

// указатели на соответствующие функции
using readingBinaryFileFnc = bool(*)(const std::string& dir, my::Array& usersData);
using writeInBinaryFileFnc = bool(*)(const std::string& dir, my::Array& usersData);

// функция чтения файла
bool ReadingBinaryFile(const std::string& dir, my::Array& usersData);
// функция записи в файл
bool WriteInBinaryFile(const std::string& dir, my::Array& usersData);
