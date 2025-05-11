#include <iostream>
#include <windows.h>
#include "ControlUnit.h"
#include "ControlUnit.cpp"
#include "MagazineRatings.h"
#include "MagazineRatings.cpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    json data;

    // Очищаем старые данные и создаем новые
    data["institutes"] = json::array();

    // Создаем ИИТУС, ПОВТАС, ВТ-232, студент Борченко
    json IITUS = {{"name", "ИИТУС"}, {"departments", json::array()}};
    json POVTAS = {{"name", "ПОВТАС"}, {"groups", json::array()}};
    json VT232 = {{"name", "ВТ-232"}, {"students", json::array()}};
    json BORCHENKO = {{"id", "105233196"}, {"surname", "Борченко"}, {"name", "Александр"}, {"middlename", "Сергеевич"}, {"grades", json::object()}};
    BORCHENKO["grades"]["ИО"] = {{"type", "экзамен"}, {"mark", 5}};
    BORCHENKO["grades"]["Вычмат"] = {{"type", "лабораторная"}, {"mark", 5}};
    BORCHENKO["grades"]["ФОПИ"] = {{"type", "лабораторная"}, {"mark", 5}};
    BORCHENKO["grades"]["ООП"] = {{"type", "зачет"}, {"mark", "зачет"}};
    BORCHENKO["grades"]["ЭЭиС"] = {{"type", "лабораторная"}, {"mark", 5}};
    VT232["students"].push_back(BORCHENKO);
    POVTAS["groups"].push_back(VT232);
    IITUS["departments"].push_back(POVTAS);
    data["institutes"].push_back(IITUS);


    // Сохраняем данные в MagazineRatings
    std::ofstream("data.json") << data.dump(4);
    std::cout << "Созданы данные по умолчанию в data.json.\n";

    // Создаем ControlUnit
    ControlUnit control;

    // Запускаем программу
    control.run();

    return 0;
}
