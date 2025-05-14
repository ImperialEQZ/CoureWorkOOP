#ifndef COURSEWORKOOP_MAGAZINERATINGS_H
#define COURSEWORKOOP_MAGAZINERATINGS_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"
#include "WorkLoad.h"
//Использование json для работы с файлом.json (вместо txt)
using json = nlohmann::json;
//Журнал оценок
class GradeBook {
private:
    static GradeBook* instance;
    json data;

    GradeBook() { loadData(); }
    //Загрузить данные
    void loadData() {
        std::ifstream f("data.json");
        if (f.peek() == std::ifstream::traits_type::eof()) {
            data = json{{"institutes", json::array()}};
        } else {
            try {
                f >> data;
            } catch (json::parse_error& e) {
                std::cerr << "Error JSON file parsing: " << e.what() << std::endl;
                data = json{{"institutes", json::array()}};
            }
        }
    }

public:

};

GradeBook* GradeBook::instance = nullptr;

#endif //COURSEWORKOOP_MAGAZINERATINGS_H
