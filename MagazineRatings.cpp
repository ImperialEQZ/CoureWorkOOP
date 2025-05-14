#include "MagazineRatings.h"

#include <string>
#include <vector>
//Использование JSON
using json = nlohmann::json;

std::vector<std::string> GradeBook::getStudentIds(const std::string& institute, const std::string& department, const std::string& group) {
    std::vector<std::string> studentIds;
    for (auto& inst : data["institutes"]) {
        if (inst["name"] == institute) {
            for (auto& dep : inst["departments"]) {
                if (dep["name"] == department) {
                    for (auto& grp : dep["groups"]) {
                        if (grp["name"] == group) {
                            for (auto& student : grp["students"]) {
                                studentIds.push_back(student["id"].get<std::string>());
                            }
                            return studentIds; // Возвращаем найденный список ID
                        }
                    }
                }
            }
        }
    }
    return studentIds; // Возвращаем пустой список, если не найдено
}
//Получить информацию о студенте
json GradeBook::getStudentInfo(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId) {
    for (auto& inst : data["institutes"]) {
        if (inst["name"] == institute) {
            for (auto& dep : inst["departments"]) {
                if (dep["name"] == department) {
                    for (auto& grp : dep["groups"]) {
                        if (grp["name"] == group) {
                            for (auto& student : grp["students"]) {
                                if (student["id"] == studentId) {
                                    return student; // Возвращаем данные о студенте
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return json{}; // Возвращаем пустой JSON-объект, если не найдено ничего
}
