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

    // Создаем ИИТУС, ПОВТАС, ВТ-232
    json IITUS = {{"name", "IITUS"}, {"departments", json::array()}};
    json POVTAS = {{"name", "POVTAS"}, {"groups", json::array()}};
    json VT232 = {{"name", "VT-232"}, {"students", json::array()}};

    // Студент номер 1
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

    VT232["students"].push_back(BORCHENKO);


    std::ofstream("data.json") << data.dump(4);
    std::cout << "Тестовые данные созданы в data.json\n";

    ControlUnit control;
    control.run();

    return 0;
}
