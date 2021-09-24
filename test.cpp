#include <iostream>
#include "Array.h"



int main()
{
    using namespace std;
    setlocale(LC_ALL, "ru");
    my::Account User;
    my::Account User2("Никита", "Цветков", 70);
    my::Account User3("Иван", "Поляков", 2, 55, 6);

    cout << "User" << endl;
    std::cout << "Имя: " << User.getFirstName() << " ";
    std::cout << "Фамилия: " << User.getLastName() << " ";
    std::cout << User.getMathScore() << " ";
    std::cout << User.getRuLangScore() << " ";
    std::cout << User.getEnLangScore() << " ";
    std::cout << User.getTotalScore() << std::endl;

    cout << "User2" << endl;
    std::cout << "Имя: " << User2.getFirstNameChar() << " ";
    std::cout << "Фамилия: " << User2.getLastNameChar() << " ";
    std::cout << User2.getMathScore() << " ";
    std::cout << User2.getRuLangScore() << " ";
    std::cout << User2.getEnLangScore() << " ";
    std::cout << User2.getTotalScore() << std::endl;

    cout << "User3" << endl;
    std::cout << "Имя: " << User3.getFirstNameChar() << " ";
    std::cout << "Фамилия: " << User3.getLastNameChar() << " ";
    std::cout << User3.getMathScore() << " ";
    std::cout << User3.getRuLangScore() << " ";
    std::cout << User3.getEnLangScore() << " ";
    std::cout << User3.getTotalScore() << std::endl;


    //cout << "User = User2" << endl;
    //std::cout << "Имя: " << User.getFirstName() << " ";
    //std::cout << "Фамилия: " << User.getLastName() << " ";
    //std::cout << User.getMathScore() << " ";
    //std::cout << User.getRuLangScore() << " ";
    //std::cout << User.getEnLangScore() << " ";
    //std::cout << User.getTotalScore() << std::endl;

    //Exam.append(1, my::Account("Петр", "Иванов", 55, 66));

    //Exam[0] = my::Account("Никита", "Цветков", 70, 69, 65);

    my::Array Exam;

    for (int i = 0; i < 5; ++i) {
        Exam.pushBack(User2);
    }
    Exam.append(Exam.getSize() - 1, User3);
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "extend array" << std::endl;
    cout << "size: " << Exam.getSize() << endl;
    for (short i = 0; i < Exam.getSize(); ++i) {
        cout << "№" << i << endl;
        std::cout << "Имя: " << Exam[i].getFirstName() << " ";
        std::cout << "Фамилия: " << Exam[i].getLastName() << " ";
        std::cout << Exam[i].getMathScore() << " ";
        std::cout << Exam[i].getRuLangScore() << " ";
        std::cout << Exam[i].getEnLangScore() << " ";
        std::cout << Exam[i].getTotalScore() << std::endl;
    }
}