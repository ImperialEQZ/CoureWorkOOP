#ifndef COURSEWORKOOP_MAGAZINERATINGS_H
#define COURSEWORKOOP_MAGAZINERATINGS_H
//пока что так, возможно доработка нужна будет
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

// Класс GradeBook предназначен для хранения и управления оценками студентов
class GradeBook {
private:
    //Статический указатель для реализации паттерна "Одиночка"
    static GradeBook* gradeBookInstance;
    // При создании экземпляра сразу вызывается метод initialize() для загрузки данных из файлов.
    GradeBook() {
        initialize();
    }

public:
    /*markBook - это основная структура данных для хранения оценок.
        1) название группы (string)
        2) номер зачетной книжки студента (string).
        3) Ключ третьего уровня - название предмета (string).
        4) Значение - оценка студента по данному предмету (int).*/
    std::map<std::string, std::map<std::string, std::map<std::string, int>>> markBook;
//статический метод, который возвращает экземпляр класса GradeBook (для паттерна одиночки)
    static GradeBook* getInstance() {
        if (!gradeBookInstance) {
            gradeBookInstance = new GradeBook();
        }
        return gradeBookInstance;
    }
    //это метод, который загружает данные об оценках из файла
    void initialize() {
        //Открытие файла information/information about group.txt, в котором содержится информация о группах и студентах.
        std::ifstream inputFile("information/information about group.txt");
        //Переменные для чтения данных из файла.
        std::string instituteName, directionName, groupName, name, surName, middleName, creditCardID/*зачетка*/, grade, mark;
        //Чтение данных из файла построчно
        while (inputFile >> instituteName >> directionName >> groupName >> name >> surName >> middleName >> creditCardID) {
            //Создание пути к файлу с информацией об оценках для конкретной группы
            std::string filePath = "information about group/" + groupName + ".txt";
            // Открываем файл с информацией об оценках.
            std::ifstream studentFile(filePath);
            if (!studentFile.is_open()) {
                std::cerr << "Не удалось открыть файл для группы: " << groupName << std::endl;
                //если не открыли файл - завершаем программу
                exit(1);
            }

            std::string line;
            std::getline(studentFile, line);

            std::stringstream ss(line);
            // Вектор для хранения названий предметов
            std::vector<std::string> grades;
            std::string gradeName;
            // Читаем названия предметов из строки.
            while (ss >> gradeName) {
                grades.push_back(gradeName);
            }
            //Запись для группы, если ее еще нет
            markBook[groupName][creditCardID] = {};
            while (studentFile >> creditCardID) {
                //Для каждого предмета прохожусь
                for (const auto& subj : grades) {
                    int analogMark;
                    studentFile >> analogMark;//не придумал еще синонимы, читаю оценку
                    markBook[groupName][creditCardID][subj] = analogMark;
                }
            }
            studentFile.close();//Закрытие файла с информацией об оценках для группы
        }
        inputFile.close();//Закрытие файла со списком групп
    }
    //на будущее, добавить в журнал оценку
    void addGrade(const std::string& groupName, const std::string& studentID, const std::string& subject, int mark) {
        markBook[groupName][studentID][subject] = mark;
    }
    //На будущее, изменить оценку
    void updateGrade(const std::string& groupName, const std::string& studentID, const std::string& subject, int newMark) {
        markBook[groupName][studentID][subject] = newMark;
    }
};
//Инициализация статического члена класса (указатель на GradeBook)
GradeBook* GradeBook::gradeBookInstance = nullptr;

#endif //COURSEWORKOOP_MAGAZINERATINGS_H
