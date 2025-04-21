#ifndef COURSEWORKOOP_MAGAZINERATINGS_H
#define COURSEWORKOOP_MAGAZINERATINGS_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

// Структура для хранения информации о студенте
struct StudentInfo {
    std::string name;
    std::string surname;
    std::string middlename;
};

// Класс GradeBook предназначен для хранения и управления оценками студентов
class GradeBook {
private:
    static GradeBook* gradeBookInstance;
    GradeBook() { initialize(); }

public:
    // Структура данных для хранения информации об оценках и студентах:
    // groupName -> studentID -> (StudentInfo,  subject -> grade)
    std::map<std::string, std::map<std::string, std::pair<StudentInfo, std::map<std::string, int>>>> markBook;

    static GradeBook* getInstance() {
        if (!gradeBookInstance) {
            gradeBookInstance = new GradeBook();
        }
        return gradeBookInstance;
    }

    void initialize() {
        std::ifstream inputFile("information/information about group.txt");
        std::string instituteName, directionName, groupName, name, surName, middleName, creditCardID;

        while (inputFile >> instituteName >> directionName >> groupName >> name >> surName >> middleName >> creditCardID) {
            std::string filePath = "information about group/" + groupName + ".txt";
            std::ifstream studentFile(filePath);

            if (!studentFile.is_open()) {
                std::cerr << "Не удалось открыть файл для группы: " << groupName << std::endl;
                exit(1);
            }

            std::string line;
            std::getline(studentFile, line);
            std::stringstream ss(line);
            std::vector<std::string> grades;
            std::string gradeName;

            while (ss >> gradeName) {
                grades.push_back(gradeName);
            }

            // Создаем запись о студенте.
            StudentInfo studentInfo = {name, surName, middleName};
            markBook[groupName][creditCardID].first = studentInfo;
            markBook[groupName][creditCardID].second = {};  // Инициализируем map оценок

            while (studentFile >> creditCardID) {
                //для каждого студента в группе
                StudentInfo studentInfo_local = {name, surName, middleName};
                markBook[groupName][creditCardID].first = studentInfo_local;
                markBook[groupName][creditCardID].second = {};
                for (const auto& subj : grades) {
                    int analogMark;
                    studentFile >> analogMark;
                    markBook[groupName][creditCardID].second[subj] = analogMark;
                }
            }
            studentFile.close();
        }
        inputFile.close();
    }

    void addGrade(const std::string& groupName, const std::string& studentID, const std::string& subject, int mark) {
        markBook[groupName][studentID].second[subject] = mark;
    }

    void updateGrade(const std::string& groupName, const std::string& studentID, const std::string& subject, int newMark) {
        markBook[groupName][studentID].second[subject] = newMark;
    }

    double calculateAverageGrade(const std::string& groupName, const std::string& studentID) {
        double sum = 0.0;
        int count = 0;
        const auto& studentGrades = markBook[groupName][studentID].second;
        for (const auto& grade : studentGrades) {
            sum += grade.second;
            count++;
        }
        return count > 0 ? sum / count : 0.0;
    }

    StudentInfo getStudentInfo(const std::string& groupName, const std::string& studentID) {
        return markBook[groupName][studentID].first;
    }

    void saveToFile(const std::string& filename) {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
            return;
        }

        for (const auto& groupEntry : markBook) {
            outputFile << "Группа: " << groupEntry.first << std::endl;
            for (const auto& studentEntry : groupEntry.second) {
                const StudentInfo& studentInfo = studentEntry.second.first;
                outputFile << "  Студент (ID: " << studentEntry.first << "): "
                           << studentInfo.surname << " " << studentInfo.name << " " << studentInfo.middlename
                           << std::endl;

                for (const auto& grade : studentEntry.second.second) {
                    outputFile << "    " << grade.first << ": " << grade.second << std::endl;
                }
                outputFile << "  Средний балл: " << calculateAverageGrade(groupEntry.first, studentEntry.first) << std::endl;
            }
        }

        outputFile.close();
        std::cout << "Данные сохранены в файл " << filename << std::endl;
    }
};

GradeBook* GradeBook::gradeBookInstance = nullptr;
#endif //COURSEWORKOOP_MAGAZINERATINGS_H
