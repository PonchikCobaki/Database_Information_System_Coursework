#include "CMenu.h"
#include "Account.h"

#include <conio.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>


// шаблоны пунктов меню
MenuTemplates allMenuTemplates = {
	">>",
	" ",
	"%",

	"навигация по меню:  arrow up/down - перемещение вверх/вниз, Enter - выбор пункта",
	" ПРОСМОТР ФАЙЛА",
	" СТАТИСТИКА",
	" НОВЫЙ ФАЙЛ",
	" ВЫХОД",

	"навигация: arrow Up/Down - перемещение вверх/вниз, arrow Right/Left - перемещение вправо/вле-\n"
	"во, Esc - возврат в меню, Enter - выбор элемента для редактирования нажмите любую клавишу для\n"
	"ввода нового элемента, Delite - удаление элемента",
	" |   №#   |           имя           |         фамилия         | матем | русс | англ | сумма |",
	" +--------+-------------------------+-------------------------+-------+------+------+-------+",
	"|",
	"                                   страница ",
	"/",

	"навигация по меню: arrow Right / Left - перемещение вправо/влево, Esc - возврат\n"
	"в главное меню",
	"\t\t\tСписок абитуриентов имеющих наивысший балл",
	"Процент абитуриентов не выдержавших конкурса: ",


	"  да",
	"  нет",
};

//	функция предотвращающая выход переменной верктикального указателя за пределы [V_B_P,height]
void FindingCursorPosition(u_int& vertPosOut, const u_int& height)
{
	if (vertPosOut < VERTICAL_BEGIN_POINT) {
		vertPosOut = (height - vertPosOut) % (height + 1);
	}
	else if (vertPosOut > height && height == 1) {
		vertPosOut = height;
	}
	else if (vertPosOut > height) {
		vertPosOut = vertPosOut % height;
	}
}
//	функция предотвращающая выход переменной верктикального и горизонтального указателя за пределы [V_B_P, height], [H_B_P, length]
void FindingCursorPosition(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height)
{
	if (horPosOut < HORIZONTAL_BEGIN_POINT) {
		horPosOut = (length - horPosOut) % (length + 1);
	}
	else if (horPosOut > length && length == 1) {
		horPosOut = length;
	}
	else if (horPosOut > length) {
		horPosOut /= length;
	}

	if (vertPosOut < VERTICAL_BEGIN_POINT) {
		vertPosOut = (height - vertPosOut) % (height + 1);
	}
	else if (vertPosOut > height && height == 1) {
		vertPosOut = height;
	}
	else if (vertPosOut > height) {
		vertPosOut = vertPosOut % height;
	}
}

//	заменяет пробел на указатель
std::string InsertCursorPosition(std::string str, const u_int& vertPos,
	const MenuTemplates& mTemps,u_short level, const u_int& iterator)
{

	if (level == LEVEL_MAIN)
	{
		switch (vertPos)
		{
		case ITEM_VIEW:
			if (mTemps.lineView == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_STATISTICS:
			if (mTemps.lineStatistics == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_CREATE:
			if (mTemps.lineCreate == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		case ITEM_EXIT:
			if (mTemps.lineExit == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		}
	}

	else if (level == LEVEL_VIEW) {
		if (vertPos == 0) {
			if (iterator == (vertPos + 1)) {
				str.replace(0, 1, mTemps.cursor);
			}
		}
		else {
			if (iterator == vertPos) {
				str.replace(0, 1, mTemps.cursor);
			}
		}
	}

	else if (level == LEVEL_SELECTION) {
		switch (vertPos)
		{
		case ITEM_SELECTION_YES:
			if (mTemps.selLineYes == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_SELECTION_NO:
			if (mTemps.selLineNo == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		}
	}

	return str;
}

//	меню выбора да/нет
bool SelectionMenuPrinting(std::string title, insertCursorPositionFnc insCurPosFnc,
		buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc)
{
	using namespace std;

	u_short codeState;
	u_int	horPos(HORIZONTAL_BEGIN_POINT);
	u_int	vertPos(VERTICAL_BEGIN_POINT);

	while (true) {
		system("cls");
		cout << title << "\n";
		cout << insCurPosFnc(allMenuTemplates.selLineYes, vertPos, allMenuTemplates, LEVEL_SELECTION, 0) << "\n";
		cout << insCurPosFnc(allMenuTemplates.selLineNo, vertPos, allMenuTemplates, LEVEL_SELECTION, 0) << endl;

		codeState = buttReadFnc(horPos, vertPos);
		findCurPosFnc(vertPos, HEIGHT_ITEM_SELECTION);

		if (codeState == KEY_ENTER) {
			switch (vertPos)
			{
			case ITEM_SELECTION_YES:
				return true;

			case ITEM_SELECTION_NO:
				return false;
			}
		}
	}

}

//	основное меню
void PrintMainMenu(const u_int& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc)
{
	using namespace std;

	system("cls");

	cout << insCurPosFnc(mTemps.lineView, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineStatistics, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineCreate, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineExit, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
}

// построение таблицы с функциями редактирования
void PrintTable(std::string dir, my::Array& usersData, const MenuTemplates& mTemps,
		insertCursorPositionFnc insCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc,
		buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc1, findingCursorPositionFnc2 findCurPosFnc2,
		readingBinaryFileFnc readBinFileFnc, writeInBinaryFileFnc writeInBinFileFnc,
		userInputFnc userInputFnc)
{
	using namespace std;

	u_int	dataCount(usersData.getSize());

	bool exitFlag = false;

	u_short codeState;								// код клавиши
	u_int	vertPos(VERTICAL_BEGIN_POINT);			// положение указателя

	u_int	dataPage(1);							// текущая страница
	u_int   prevDataPage(0);						// предыдущая страница
	u_int   dataPageCount(2);						// число страниц

	u_int	dataViewIndBeg(0);						// начальный индекс просмотра
	u_int	dataViewIndCount(DATA_FIELD_LENGTH);	// число эл. просмотра


	bool changeFlag = false;						// флаг изменения эл.
	stringstream dataBuffer;						// буфер для вывода

	//// переменные для изменения данных
	uint32_t changeInd(0);
	my::Account changeUser;
	bool offset;
	//bool invertedFlag = !selMenuPrintingFnc("Просмотр таблицы в прямом порядке",
	//	insCurPosFnc, buttReadFnc, findCurPosFnc1);
	// расчёт кол-ва выводимых данных
	if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
		dataViewIndCount = dataCount - dataViewIndBeg; // изменение размера кол-ва элементов вывода
	}


	while (!exitFlag)
	{
		//////////////////////////////////////////////
		// чтение и поиск всех необходимых индексов	//
		//////////////////////////////////////////////

		if (dataCount == 0) {
			exitFlag = true;
			break;
		}


		if (prevDataPage != dataPage || changeFlag) {
			// установка индексов среза вывода
			dataViewIndCount = DATA_FIELD_LENGTH;
			dataViewIndBeg = (dataPage - IND_CONV_FACTOR) * dataViewIndCount;

			// проверка длины среза вывода
			if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
				dataViewIndCount = dataCount - dataViewIndBeg;
			}

			findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);

			prevDataPage = dataPage;
		}

		// нахождение количества страниц
		if (dataCount % DATA_FIELD_LENGTH == 0) {
			dataPageCount = dataCount / DATA_FIELD_LENGTH;
		}
		else if (dataCount % DATA_FIELD_LENGTH != 0 && dataCount > DATA_FIELD_LENGTH) {
			dataPageCount = dataCount / DATA_FIELD_LENGTH;
			++dataPageCount;
		}
		else {
			dataPageCount = 1;
		}

		changeFlag = false;


		//////////////////////////////////////////////////
		//				вывод данных					//
		//////////////////////////////////////////////////

		// заполнение промежуточного потока для вывода таблицы
		dataBuffer << mTemps.tableSeparatorHorizontal << "\n" << mTemps.tableHeader << "\n" << mTemps.tableSeparatorHorizontal << "\n";
		for (int32_t uIndex = dataViewIndBeg; uIndex <= (dataViewIndBeg + dataViewIndCount - IND_CONV_FACTOR) ; ++uIndex) {
			u_int printInd;
			if (dataViewIndBeg != 0 && dataPage != dataPageCount) {
				printInd = (uIndex % dataViewIndCount) + 1;
			}
			else if (dataPage == dataPageCount) {
				printInd = uIndex - (DATA_FIELD_LENGTH * (dataPageCount - 1)) + 1;
			}
			else{
				printInd = uIndex + 1;
			}
			
			dataBuffer << insCurPosFnc(mTemps.space, vertPos, mTemps, LEVEL_VIEW, printInd)
				<< mTemps.tableSeparatorVertical << setw(COUNTER_FIELD_WIDTH) << right << uIndex + 1 << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << usersData[uIndex].getFirstName() << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << usersData[uIndex].getLastName() << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << usersData[uIndex].getMathScore() << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << usersData[uIndex].getRuLangScore() << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << usersData[uIndex].getEnLangScore() << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << usersData[uIndex].getTotalScore() << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << "\n";
			//invertedFlag ? --uIndex : ++uIndex;

		}

		dataBuffer << mTemps.tablePage << setw(PAGE_FIELD_WIDTH) << right << dataPage << mTemps.tablePageSeparator <<
						left << dataPageCount << "\n";
		dataBuffer << mTemps.itemViewDescription << endl;

		// перевод данных из буфера в поток вывода 
		system("cls");
		cout << dataBuffer.str();
		dataBuffer.str("");
		dataBuffer.clear();

		//////////////////////////////////////////////////
		//			обработка клавиатуры				//
		//////////////////////////////////////////////////
		 

		// обработка клавиш
		codeState = buttReadFnc(dataPage, vertPos);
		findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);

		switch (codeState)
		{
		case KEY_DELETE: // удаление эл. из базы
			changeInd = ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR;
			usersData.del(changeInd);
			//delFromBinFileFnc(dir, ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR,
			//	dataCount, writeInBinFileFnc);

			if (vertPos == dataViewIndCount && dataPage == dataPageCount) {
				--vertPos;
			}

			--dataCount;
			--dataViewIndCount;
			if (dataViewIndCount == 0) {
				--dataPageCount;
				--dataPage;
			}
			changeFlag = true;
			break;

		case KEY_ENTER: // изменение эл в базе
			system("cls");

			changeInd = ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR;
			cout << "\t\t\t\t редактируемая учетная запись \n"
				<< mTemps.tableSeparatorHorizontal << " " << mTemps.cursor << mTemps.tableSeparatorVertical
				<< setw(COUNTER_FIELD_WIDTH) << right << dataViewIndBeg + vertPos << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << usersData[changeInd].getFirstName() << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << usersData[changeInd].getLastName() << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getMathScore() << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getRuLangScore() << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getEnLangScore() << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getTotalScore() << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << "\n";

			cout << "\n\t\t введите новые данные: ";

			userInputFnc(changeUser);
			usersData[changeInd] = changeUser;
			//changeInBinFileFnc(dir, ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR,
			//	dataCount, changeUser, writeInBinFileFnc);

			changeFlag = true;
			break;

		case KEY_OTHER: // добваление данных
			system("cls");
			changeInd = ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR;
			offset = !selMenuPrintingFnc(dataBuffer.str() + "добавлениь на место куказанной учетной записи? иначе на место выше",
				insCurPosFnc, buttReadFnc, findCurPosFnc1);

			if (!offset)
			{
				cout << mTemps.tableSeparatorHorizontal << " " << mTemps.cursor << mTemps.tableSeparatorVertical
					<< setw(COUNTER_FIELD_WIDTH) << right << dataViewIndBeg + vertPos << mTemps.tableSeparatorVertical
					<< setw(FIRST_NAME_FIELD_WIDTH) << left << usersData[changeInd].getFirstName() << mTemps.tableSeparatorVertical
					<< setw(LAST_NAME_FIELD_WIDTH) << usersData[changeInd].getLastName() << mTemps.tableSeparatorVertical
					<< setw(MATCH_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getMathScore() << mTemps.tableSeparatorVertical
					<< setw(RU_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getRuLangScore() << mTemps.tableSeparatorVertical
					<< setw(EN_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getEnLangScore() << mTemps.tableSeparatorVertical
					<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getTotalScore() << mTemps.tableSeparatorVertical << "\n"
					<< mTemps.tableSeparatorHorizontal << "\n";
			}
			else
			{
				cout << mTemps.tableSeparatorHorizontal << mTemps.space << mTemps.space << mTemps.tableSeparatorVertical
					<< setw(COUNTER_FIELD_WIDTH) << right << dataViewIndBeg + vertPos << mTemps.tableSeparatorVertical
					<< setw(FIRST_NAME_FIELD_WIDTH) << left << usersData[changeInd].getFirstName() << mTemps.tableSeparatorVertical
					<< setw(LAST_NAME_FIELD_WIDTH) << usersData[changeInd].getLastName() << mTemps.tableSeparatorVertical
					<< setw(MATCH_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getMathScore() << mTemps.tableSeparatorVertical
					<< setw(RU_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getRuLangScore() << mTemps.tableSeparatorVertical
					<< setw(EN_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getEnLangScore() << mTemps.tableSeparatorVertical
					<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << usersData[changeInd].getTotalScore() << mTemps.tableSeparatorVertical << "\n"
					<< mTemps.tableSeparatorHorizontal 
					<< mTemps.cursor << "\n";
			}

			cout << "\n\t\t введите новые данные: ";

			userInputFnc(changeUser);
			//appInBinFileFnc(dir, ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR, offset,
			//	dataCount, changeUser, writeInBinFileFnc);

			if (offset && changeInd == dataCount - IND_CONV_FACTOR) // выбор метса записи
				usersData.pushBack(changeUser);
			else if(offset)
				usersData.append(changeInd + 1, changeUser);
			else
				usersData.append(changeInd, changeUser);

			++dataCount;
			changeFlag = true;
			break;

		case KEY_ESCAPE: // выход из ф. просмотра
			writeInBinFileFnc(dir, usersData);
			exitFlag = true;
			break;
		}
	}

}
// упрощённая версия для построение таблицы 
void PrintTable(const u_int& failCount, std::string dir, my::Array& usersData, const MenuTemplates& mTemps,
		insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc2)
{
	using namespace std;

	u_int	dataCount(usersData.getSize());

	bool exitFlag = false;

	u_short codeState;								// код клавиши
	u_int	vertPos(VERTICAL_BEGIN_POINT);			// положение указателя

	u_int	dataPage(1);							// текущая страница
	u_int   prevDataPage(0);						// предыдущая страница
	u_int   dataPageCount(2);						// число страниц

	u_int	dataViewIndBeg(0);						// начальный индекс просмотра
	u_int	dataViewIndCount(DATA_FIELD_LENGTH);	// число эл. просмотра


	bool changeFlag = false;						// флаг изменения эл.
	stringstream dataBuffer;						// буфер для вывода

	//// переменные для изменения данных
	uint32_t changeInd(0);
	my::Account changeUser;
	bool offset;
	//bool invertedFlag = !selMenuPrintingFnc("Просмотр таблицы в прямом порядке",
	//	insCurPosFnc, buttReadFnc, findCurPosFnc1);
	// расчёт кол-ва выводимых данных
	if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
		dataViewIndCount = dataCount - dataViewIndBeg; // изменение размера кол-ва элементов вывода
	}


	while (!exitFlag)
	{
		//////////////////////////////////////////////
		// чтение и поиск всех необходимых индексов	//
		//////////////////////////////////////////////

		if (dataCount == 0) {
			exitFlag = true;
			break;
		}


		if (prevDataPage != dataPage || changeFlag) {
			// установка индексов среза вывода
			dataViewIndCount = DATA_FIELD_LENGTH;
			dataViewIndBeg = (dataPage - IND_CONV_FACTOR) * dataViewIndCount;

			// проверка длины среза вывода
			if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
				dataViewIndCount = dataCount - dataViewIndBeg;
			}

			findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);

			prevDataPage = dataPage;
		}

		// нахождение количества страниц
		if (dataCount % DATA_FIELD_LENGTH == 0) {
			dataPageCount = dataCount / DATA_FIELD_LENGTH;
		}
		else if (dataCount % DATA_FIELD_LENGTH != 0 && dataCount > DATA_FIELD_LENGTH) {
			dataPageCount = dataCount / DATA_FIELD_LENGTH;
			++dataPageCount;
		}
		else {
			dataPageCount = 1;
		}

		changeFlag = false;

		//////////////////////////////////////////////////
		//				вывод данных					//
		//////////////////////////////////////////////////

		// заполнение промежуточного потока для вывода таблицы
		dataBuffer << mTemps.itemStatLinePercent << failCount << mTemps.percent << "\n";
		dataBuffer << mTemps.itemStatLineHeader << "\n";
		dataBuffer << mTemps.tableSeparatorHorizontal << "\n" << mTemps.tableHeader << "\n" << mTemps.tableSeparatorHorizontal << "\n";
		for (int32_t uIndex = dataViewIndBeg; uIndex <= (dataViewIndBeg + dataViewIndCount - IND_CONV_FACTOR); ++uIndex) {
			dataBuffer << mTemps.space 
				<< mTemps.tableSeparatorVertical << setw(COUNTER_FIELD_WIDTH) << right << uIndex + 1 << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << usersData[uIndex].getFirstName() << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << usersData[uIndex].getLastName() << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << usersData[uIndex].getMathScore() << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << usersData[uIndex].getRuLangScore() << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << usersData[uIndex].getEnLangScore() << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << usersData[uIndex].getTotalScore() << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << "\n";
		}


		dataBuffer << mTemps.tablePage << setw(PAGE_FIELD_WIDTH) << right << dataPage << mTemps.tablePageSeparator <<
			left << dataPageCount << "\n";
		dataBuffer << mTemps.itemStatDescription << endl;

		// перевод данных из буфера в поток вывода 
		system("cls");
		cout << dataBuffer.str();
		dataBuffer.str("");
		dataBuffer.clear();

		//////////////////////////////////////////////////
		//			обработка клавиатуры				//
		//////////////////////////////////////////////////


		// обработка клавиш
		codeState = buttReadFnc(dataPage, vertPos);
		findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);
		exitFlag = codeState == KEY_ESCAPE ?  true: false; // выход из ф. просмотра
	}

}

// функция вычисления статискитеских данных
void ComputeStatistics(const u_short& pasScore, const u_short& minMathScore, const u_short& minRuLangScore,
		const u_short& minEnLangScore, const std::string dir, my::Array& usersData,
		readingBinaryFileFnc readBinFileFnc, printTableFnc printTableFnc, insertCursorPositionFnc insCurPosFnc,
		buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc2)
{

	using namespace std;

	
	u_int dataCount;		// кол-во данных
	bool exitFlag(false);	// флаг выхода из функции

	// чтение файла с данными
	if (!usersData.getSize()) {	
		exitFlag = readBinFileFnc(dir, usersData);	// чтение данных
	}
	dataCount = (usersData.getSize());

	if (exitFlag) {
		return;
	}


	vector<u_int> bestScoreListInd;	// массив с писком индексов имеющих максимальный балл
	u_short maxScore(0);			// максимальное значение баллов
	u_int failCount(0);				// кол-во не проходящих условия

	for (unsigned int i = 0; i < dataCount; ++i) {
		// проверка на прохождение по критериям
		if (usersData[i].getTotalScore() < pasScore || usersData[i].getMathScore() < minMathScore
			|| usersData[i].getRuLangScore() < minRuLangScore || usersData[i].getEnLangScore() < minEnLangScore) {
			++failCount;
			continue;
		}
		// проверка на макстимальный балл
		if (usersData[i].getTotalScore() == maxScore) {
			bestScoreListInd.push_back(i);
		}
		else if (usersData[i].getTotalScore() > maxScore) {
			maxScore = usersData[i].getTotalScore();
			bestScoreListInd.clear();
			bestScoreListInd.push_back(i);
		}
	}

	// создание нового контейнера учетных запесей с лучшими баллами

	my::Array bestScoreList;
	for (u_int j = 0; j < bestScoreListInd.size(); ++j) {
		bestScoreList.pushBack(usersData[bestScoreListInd[j]]);
	}

	// вывод результатов 
	printTableFnc((float(failCount) / dataCount) * 100, dir, bestScoreList, allMenuTemplates,
		insCurPosFnc, buttReadFnc, findCurPosFnc2);
}

// функция создания нового файла в ручную
void PrintCreateItem(std::string& dir, my::Array& usersData, insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc,
		findingCursorPositionFnc1 findCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc, userInputFnc userInputFnc, writeInBinaryFileFnc writeInBinFileFnc)
{
	using namespace std;

	system("cls");

	// меню выбора
	if (selMenuPrintingFnc("записать в новый файл?", insCurPosFnc, buttReadFnc, findCurPosFnc) ) {
		cout << "\n\t\t введите путь и имя новго файла: ";
		string path;
		cin >> path;
		//getline(std::cin, path);
		dir = path;
		cout << "\n";
	}
	else {
		cout << "\t\t\t запись в текущий файл: " << dir << endl;
	}

	bool flagExit(false);
	u_int counter(1);				// абсолютный счётчик
	my::Account			userData;	// промежуточная структура для записи

	usersData.clear();
	cout << "Введите данные по порядку" << endl;
	while (!flagExit)
	{
		cout << "№ " << counter << " : ";
		UserInput(userData);
		usersData.pushBack(userData);

		++counter;	// абсолютный счётчик

		// проверка на выхода из цикла
		cout << "---------------------------------------нажмите ESC для выхода---------------------------------" << endl;
		u_int horPos(HORIZONTAL_BEGIN_POINT);
		u_int vertPos(VERTICAL_BEGIN_POINT);
		if (buttReadFnc(horPos, vertPos) == KEY_ESCAPE) {
			writeInBinFileFnc(dir, usersData);
			flagExit = true;
		}
	}

}
