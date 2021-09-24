#include "BinFO.h"

#include <conio.h>
#include <fstream>
#include <random>


// функция автозаполнения файла
void CreateRandomBinDataset(std::string dir)
{
	using namespace std;
	using std::cout;
	random_device rd;
	mt19937 mersenne(rd());

	uint16_t size;
	cout << "количество учетных записей: ";
	cin >> size;
	string firstNames[] = { "Иван", "Пётр", "Василий", "Марат", "Григорий",
		"Ильназ", "Али", "Максим", "Артём", "Джек" };
	string lastNames[] = { "Иванов", "Пётров", "Васильевич", "Айзатов",
		"Шайхутдинов", "Кларксон", "Ахматович", "Белых", "Понасенков", "Хабибулин" };
	
	my::Account users;
	uint16_t buffer;
	ofstream outBinFile(dir, ios::binary);
	for (u_int i = 0; i < size; i++) {
		users.setFirstName( firstNames[mersenne() % 10].c_str());
		users.setLastName(lastNames[mersenne() % 10].c_str());
		users.setMathScore(mersenne() % 101);
		users.setRuLangScore(mersenne() % 101);
		users.setEnLangScore(mersenne() % 101);

		outBinFile.write(users.getFirstNameChar(), sizeof(*users.getFirstNameChar()) * my::LENGTH_FIRST_NAME);
		outBinFile.write(users.getLastNameChar(), sizeof(*users.getFirstNameChar()) * my::LENGTH_LAST_NAME);
		
		buffer = users.getMathScore();
		outBinFile.write(reinterpret_cast<char*>(&buffer), sizeof(users.getMathScore()));
		buffer = users.getRuLangScore();
		outBinFile.write(reinterpret_cast<char*>(&buffer), sizeof(users.getRuLangScore()));
		buffer = users.getEnLangScore();
		outBinFile.write(reinterpret_cast<char*>(&buffer), sizeof(users.getEnLangScore()));

		//cout << i + 1 << " " << setw(FIRST_NAME_FIELD_WIDTH) << users.firstName << " " << setw(LAST_NAME_FIELD_WIDTH) 
		//	<< users.lastName << " " << setw(MATCH_SCORE_FIELD_WIDTH) << users.mathScore <<
		//	" " << setw(RU_SCORE_FIELD_WIDTH) << users.ruLangScore << " " << setw(EN_SCORE_FIELD_WIDTH) << users.enLangScore << endl;
	}
	outBinFile.close();
	cout << "END" << endl;
	system("pause");
}

// функция чтения файла
bool ReadingBinaryFile(const std::string& dir, my::Array& usersData, const u_int& dataReadIndBeg,
		const u_int& dataReadIndCount, u_int& dataCountOut)
{
	using namespace std;

	// открытие файла
	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input buffer file on time reading" << endl;
		system("pause");
		return true;
	}

	dataCountOut = inBinFile.seekg(0, ios::end).tellg() / usersData[0].getWriteSize();

	if (dataReadIndCount != 0)
	{
		// создание нового среза
		my::Account dataBuffer;	// буффер для класса
		char* strBuffer;	// буффер для строк
		uint16_t buffer;	// буффер для чисел
		inBinFile.seekg(dataReadIndBeg * dataBuffer.getWriteSize(), ios::beg);
		for (u_int i = 0; i < dataReadIndCount; ++i) {
			
			// чтение и запись в класс 
			strBuffer = new char[my::LENGTH_FIRST_NAME];
			inBinFile.read(strBuffer, sizeof(char) * my::LENGTH_FIRST_NAME);
			dataBuffer.setFirstName(strBuffer);
			delete[] strBuffer;

			strBuffer = new char[my::LENGTH_FIRST_NAME];
			inBinFile.read(strBuffer, sizeof(char) * my::LENGTH_LAST_NAME);
			dataBuffer.setLastName(strBuffer);
			delete[] strBuffer;

			inBinFile.read(reinterpret_cast<char*>(&buffer), sizeof(uint16_t));
			dataBuffer.setMathScore(buffer);
			inBinFile.read(reinterpret_cast<char*>(&buffer), sizeof(uint16_t));
			dataBuffer.setRuLangScore(buffer);
			inBinFile.read(reinterpret_cast<char*>(&buffer), sizeof(uint16_t));
			dataBuffer.setEnLangScore(buffer);

			// проверка на случай имеющейся базы
			if (usersData.getSize() != dataCountOut)
				usersData.pushBack(dataBuffer);
			else if (usersData.getSize() >= dataCountOut) 
				usersData[i] = dataBuffer;
			else
				exit(-1);

		}
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
