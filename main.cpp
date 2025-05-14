#include <iostream>
#include <windows.h>
#include "ControlUnit.h"
#include "ControlUnit.cpp"
#include "MagazineRatings.h"
#include "MagazineRatings.cpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    json data;

    data["institutes"] = json::array();

    // Создаем ИИТУС, ПОВТАС (2 студента в ВТ-232 и  1 в ПВ-233)
    //Массив института
    json IITUS = {{"name", "IITUS"}, {"departments", json::array()}};
    //Массив кафедры
    json POVTAS = {{"name", "POVTAS"}, {"groups", json::array()}};
    //Массив 2 разных групп со стулентами
    json VT232 = {{"name", "VT-232"}, {"students", json::array()}};
    json PV233 = {{"name", "PV-233"}, {"students", json::array()}};

    // Студент номер 1 ВТ-232
    json BORCHENKO = {
            {"id", "105233196"},
            {"surname", "Borchenko"},
            {"name", "Alexander"},
            {"middlename", "Sergeevich"},
            {"grades", json::object()}
    };
    BORCHENKO["grades"]["IO"] = {{"type", "Exam"}, {"mark", 5}};
    BORCHENKO["grades"]["VichMath"] = {{"type", "Laboratory"}, {"mark", 4}};
    BORCHENKO["grades"]["FOPI"] = {{"type", "Laboratory"}, {"mark", 3}};
    BORCHENKO["grades"]["OOP"] = {{"type", "Credit"}, {"mark", 0}};
    BORCHENKO["grades"]["EEiS"] = {{"type", "Laboratory"}, {"mark", 5}};
    BORCHENKO["grades"]["Gardening"] = {{"type", "Coursework"}, {"mark", 4}};

    VT232["students"].push_back(BORCHENKO);

    // Студент номер 2 ВТ-232
    json ABOBOVICH = {
            {"id", "88005553535"},
            {"surname", "Abobovich"},
            {"name", "Petr"},
            {"middlename", "Vladimirovich"},
            {"grades", json::object()}
    };
    ABOBOVICH["grades"]["OP"] = {{"type", "Exam"}, {"mark", 4}};
    ABOBOVICH["grades"]["Astrology"] = {{"type", "Laboratory"}, {"mark", 3}};
    ABOBOVICH["grades"]["computer science"] = {{"type", "Credit"}, {"mark", 0}};
    ABOBOVICH["grades"]["OOP"] = {{"type", "Coursework"}, {"mark", 3}};
    ABOBOVICH["grades"]["potions"] = {{"type", "Laboratory"}, {"mark", 3}};
    VT232["students"].push_back(ABOBOVICH);

    // Студент номер 3 ПВ-233
    json BOGDANYUS = {
            {"id", "11111111"},
            {"surname", "Bogdanyus"},
            {"name", "Bogdan"},
            {"middlename", "Dimonovich"},
            {"grades", json::object()}
    };
    BOGDANYUS["grades"]["IO"] = {{"type", "Exam"}, {"mark", 5}};
    BOGDANYUS["grades"]["VichMath"] = {{"type", "Laboratory"}, {"mark", 4}};
    BOGDANYUS["grades"]["FOPI"] = {{"type", "Laboratory"}, {"mark", 3}};
    BOGDANYUS["grades"]["OOP"] = {{"type", "Credit"}, {"mark", 0}};
    BOGDANYUS["grades"]["EEiS"] = {{"type", "Laboratory"}, {"mark", 5}};
    //Добавление студента в группу
    PV233["students"].push_back(BOGDANYUS);

    // Собираем полную структуру теста
    //Добавление групп в каведру
    POVTAS["groups"].push_back(VT232);
    POVTAS["groups"].push_back(PV233);
    //Добавление кафедры в институт
    IITUS["departments"].push_back(POVTAS);
    //Добавление данных института
    data["institutes"].push_back(IITUS);



    std::ofstream("data.json") << data.dump(4);
    std::cout << "Test data created in data.json\n";

    ControlUnit control;
    control.run();

    return 0;
}
