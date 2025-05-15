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
#include "Institute.h"

//Использование json для работы с файлом.json (вместо txt)
using json = nlohmann::json;
//Журнал оценок
class GradeBook {
private:
    static GradeBook* instance;
    json data;
    std::vector<Institute> institutes; // Хранит информацию об институтах

    GradeBook() { loadData(); }
    //Загрузить данные
    void loadData();

public:
    //Реализация паттерна одиночка (синглтон)
    static GradeBook* getInstance();
    //Сохранение данных в JSON файл
    void saveData();
    //Добавление оценки студенту (+ тип нагрузки предмета)
    void addGrade(const std::string& instituteName,
                  const std::string& departmentName,
                  const std::string& groupName,
                  const std::string& studentId,
                  const std::string& subjectName,
                  WorkloadType workloadType,
                  int mark);
    //вычисление среднего значения
    double calculateAverage(const std::string& studentId);
    // Метод для получения списка studentId
    std::vector<std::string> getStudentIds(const std::string& instituteName, const std::string& departmentName, const std::string& groupName);

    // Метод для получения информации о студенте
    json getStudentInfo(const std::string& instituteName, const std::string& departmentName, const std::string& groupName, const std::string& studentId);
    void addInstitute(const Institute& institute);
};

GradeBook* GradeBook::instance = nullptr;
#endif //COURSEWORKOOP_MAGAZINERATINGS_H
