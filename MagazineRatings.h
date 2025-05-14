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
    static GradeBook* getInstance() {
        if (!instance) instance = new GradeBook();
        return instance;
    }

    void saveData() {
        std::ofstream("data.json") << data.dump(4);
        std::cout << "Data saved in data.json.\n";
    }
    void addGrade(const std::string& institute,
                  const std::string& department,
                  const std::string& group,
                  const std::string& studentId,
                  const std::string& subject,
                  WorkloadType workloadType,
                  int mark) {

        try {
            std::string typeStr;
            switch(workloadType) {
                case WorkloadType::EXAM: typeStr = "exam"; break;
                case WorkloadType::LAB: typeStr = "lab"; break;
                case WorkloadType::COURSE_PROJECT: typeStr = "course"; break;
                case WorkloadType::CREDIT: typeStr = "credit"; break;
            }

            for (auto& inst : data["institutes"]) {
                if (inst["name"] == institute) {
                    for (auto& dep : inst["departments"]) {
                        if (dep["name"] == department) {
                            for (auto& grp : dep["groups"]) {
                                if (grp["name"] == group) {
                                    for (auto& student : grp["students"]) {
                                        if (student["id"] == studentId) {
                                            student["grades"][subject] = {{"type", typeStr}, {"mark", mark}};
                                            saveData();
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            std::cerr << "Error: element not found!\n";
        } catch (const std::exception& e) {
            std::cerr << "JSON error: " << e.what() << "\n";
            throw; // Перебрасываем исключение дальше
        }
    }
    //вычисление среднего значения
    double calculateAverage(const std::string& studentId) {
        for (auto& inst : data["institutes"]) {
            for (auto& dep : inst["departments"]) {
                for (auto& grp : dep["groups"]) {
                    for (auto& student : grp["students"]) {
                        if (student["id"] == studentId) {
                            double sum = 0;
                            int count = 0;
                            for (auto& [subject, grade] : student["grades"].items()) {
                                std::string type = grade["type"].get<std::string>();
                                int mark = grade["mark"].get<int>();
                                if (type != "Credit") { // Игнорирование зачета
                                    sum += mark;
                                    count++;
                                }
                            }
                            return count > 0 ? sum / count : 0.0;
                        }
                    }
                }
            }
        }
        return 0.0;
    }

    // Метод для получения списка studentId
    std::vector<std::string> getStudentIds(const std::string& institute, const std::string& department, const std::string& group);

    // Метод для получения информации о студенте
    json getStudentInfo(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId);
};

GradeBook* GradeBook::instance = nullptr;

#endif //COURSEWORKOOP_MAGAZINERATINGS_H
