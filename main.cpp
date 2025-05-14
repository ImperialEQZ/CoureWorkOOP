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
    BORCHENKO["grades"]["IO"] = {{"type", "exam"}, {"mark", 5}};
    BORCHENKO["grades"]["VichMath"] = {{"type", "laboratory"}, {"mark", 4}};
    BORCHENKO["grades"]["FOPI"] = {{"type", "laboratory"}, {"mark", 3}};
    BORCHENKO["grades"]["OOP"] = {{"type", "credit"}, {"mark", 0}};
    BORCHENKO["grades"]["EEiS"] = {{"type", "laboratory"}, {"mark", 5}};
    BORCHENKO["grades"]["Gardening"] = {{"type", "coursework"}, {"mark", 4}};

    VT232["students"].push_back(BORCHENKO);

    // Студент номер 2 ВТ-232
    json ABOBOVICH = {
            {"id", "88005553535"},
            {"surname", "Abobovich"},
            {"name", "Petr"},
            {"middlename", "Vladimirovich"},
            {"grades", json::object()}
    };
    ABOBOVICH["grades"]["OP"] = {{"type", "exam"}, {"mark", 4}};
    ABOBOVICH["grades"]["Astrology"] = {{"type", "laboratory"}, {"mark", 3}};
    ABOBOVICH["grades"]["computer science"] = {{"type", "credit"}, {"mark", 0}};
    ABOBOVICH["grades"]["OOP"] = {{"type", "coursework"}, {"mark", 3}};
    ABOBOVICH["grades"]["potions"] = {{"type", "laboratory"}, {"mark", 3}};
    VT232["students"].push_back(ABOBOVICH);

    // Студент номер 3 ПВ-233
    json BOGDANYUS = {
            {"id", "11111111"},
            {"surname", "Bogdanyus"},
            {"name", "Bogdan"},
            {"middlename", "Dimonovich"},
            {"grades", json::object()}
    };
    BOGDANYUS["grades"]["IO"] = {{"type", "exam"}, {"mark", 5}};
    BOGDANYUS["grades"]["VichMath"] = {{"type", "laboratory"}, {"mark", 4}};
    BOGDANYUS["grades"]["FOPI"] = {{"type", "laboratory"}, {"mark", 3}};
    BOGDANYUS["grades"]["OOP"] = {{"type", "credit"}, {"mark", 0}};
    BOGDANYUS["grades"]["EEiS"] = {{"type", "laboratory"}, {"mark", 5}};
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


    //Второй институт - институт энергетики
    json IEIE = {{"name", "IEIE"}, {"departments", json::array()}};

    // Кафедра: Электроэнергетика и электротехника группа ЭиЭ-231
    json Energy = {{"name", "Electricity and electrical engineering"}, {"groups", json::array()}};
    json EiE231 = {{"name", "EiE-231"}, {"students", json::array()}};
    json PETROV = {{"id", "67890569"},
                   {"surname", "Petrov"},
                   {"name", "Ivan"},
                   {"middlename", "Ivanovich"},
                   {"grades", json::object()}};

    PETROV["grades"]["Electricity"] = {{"type", "exam"}, {"mark", 3}};
    PETROV["grades"]["Welding"] = {{"type", "coursework"}, {"mark", 4}};

    EiE231["students"].push_back(PETROV);
    Energy["groups"].push_back(EiE231);
    IEIE["departments"].push_back(Energy);

    // Кафедра: Теплоэнергетика и теплотехника группа ТиТ-232
    json Heat = {{"name", "Heat power engineering and heat engineering"}, {"groups", json::array()}};
    json TIT232 = {{"name", "TiT-232"}, {"students", json::array()}};

    json SIDOROV = {{"id", "1357978936"},
                    {"surname", "Sidorov"},
                    {"name", "Stepan"},
                    {"middlename", "Sergeevich"},
                    {"grades", json::object()}};

    SIDOROV["grades"]["Ternod"] = {{"type", "exam"}, {"mark", 5}};

    TIT232["students"].push_back(SIDOROV);
    Heat["groups"].push_back(TIT232);
    IEIE["departments"].push_back(Heat);

    data["institutes"].push_back(IEIE);

    std::ofstream("data.json") << data.dump(4);
    std::cout << "Test data created in data.json\n";

    ControlUnit control;
    control.run();

    return 0;
}
