#include "BinFO.h"

#include <conio.h>
#include <fstream>
#include <random>


// функция чтения файла
bool ReadingBinaryFile(const std::string& dir, my::Array& usersData)
{
	using namespace std;

	// открытие файла
	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input buffer file on time reading" << endl;
		system("pause");
		return true;
	}

	uint16_t dataCount = inBinFile.seekg(0, ios::end).tellg() / usersData[0].getWriteSize();
	inBinFile.seekg(0, ios::beg);

	// создание нового среза
	my::Account dataBuffer;	// буффер для класса
	char* strBuffer;	// буффер для строк
	uint16_t buffer;	// буффер для чисел
	usersData.clear();

	for (u_int i = 0; i < dataCount; ++i) {
			
		// чтение и запись в класс 
		strBuffer = new char[static_cast<uint16_t>(my::LENGTH_FIRST_NAME)];
		inBinFile.read(strBuffer, sizeof(char) * static_cast<uint16_t>(my::LENGTH_FIRST_NAME));
		dataBuffer.setFirstName(strBuffer);
		delete[] strBuffer;

		strBuffer = new char[static_cast<uint16_t>(my::LENGTH_FIRST_NAME)];
		inBinFile.read(strBuffer, sizeof(char) * static_cast<uint16_t>(my::LENGTH_LAST_NAME));
		dataBuffer.setLastName(strBuffer);
		delete[] strBuffer;

		inBinFile.read(reinterpret_cast<char*>(&buffer), sizeof(uint16_t));
		dataBuffer.setMathScore(buffer);
		inBinFile.read(reinterpret_cast<char*>(&buffer), sizeof(uint16_t));
		dataBuffer.setRuLangScore(buffer);
		inBinFile.read(reinterpret_cast<char*>(&buffer), sizeof(uint16_t));
		dataBuffer.setEnLangScore(buffer);

		usersData.pushBack(dataBuffer);
	}

	inBinFile.close();

	return false;
}

// функция записи в файл
bool WriteInBinaryFile(const std::string& dir, my::Array& usersData)
{
	using namespace std;

	// очистка и открытие файла
	ofstream outBinFile(dir, ios::binary | ios::trunc);
	if (!outBinFile) {
		cerr << "Error opening input buffer file on time reading" << endl;
		system("pause");
		return true;
	}

	uint16_t buffer;	// фуффер для записи
	// почленная запись в файл
	for (uint16_t i(0); i < usersData.getSize(); ++i) {
		outBinFile.write(usersData[i].getFirstNameChar(), sizeof(*usersData[i].getFirstNameChar()) * my::LENGTH_FIRST_NAME);
		outBinFile.write(usersData[i].getLastNameChar(), sizeof(*usersData[i].getFirstNameChar()) * my::LENGTH_LAST_NAME);

		buffer = usersData[i].getMathScore();
		outBinFile.write(reinterpret_cast<char*>(&buffer), sizeof(usersData[i].getMathScore()));
		buffer = usersData[i].getRuLangScore();
		outBinFile.write(reinterpret_cast<char*>(&buffer), sizeof(usersData[i].getRuLangScore()));
		buffer = usersData[i].getEnLangScore();
		outBinFile.write(reinterpret_cast<char*>(&buffer), sizeof(usersData[i].getEnLangScore()));
	}

	outBinFile.close();

	return false;
}
