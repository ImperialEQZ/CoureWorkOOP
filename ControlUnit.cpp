#include "ControlUnit.h"
#include <iostream>
#include <limits>
#include <vector>
#include "json.hpp"
#include "WorkLoad.h"

using json = nlohmann::json;

void ControlUnit::run() {
    int choice;
    do {
        printMainMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //очистка буфера

        switch (choice) {
            case 1: // Выбрать институт
                selectInstitute();
                break;
            case 2: // Сохранить данные
                gradeBook->saveData();
                break;
            case 3: // Выход
                std::cout << "Exiting the programm.\n";
                gradeBook->saveData(); // Сохраняем данные при выходе
                break;
            default:
                std::cout << "Incorrect input.\n";
        }
    } while (choice != 3);
}
//Будет 2 института: ИИТУС и ИЭИЭ
void ControlUnit::selectInstitute() {
    instituteMenu();
    int instChoice;
    std::cin >> instChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (instChoice == 3) return;

    std::string instituteName;
    if (instChoice == 1) instituteName = "IITUS";
    else if (instChoice == 2) instituteName = "IEIE";
    else {
        std::cout << "Incorrect input.\n";
        return;
    }

    selectDepartment(instituteName);
}
//В сумме 4 кафедры: ПОВТАС, ИТ, Электроэнергетика и электротехника, Теплоэнергетика и теплотехника
void ControlUnit::selectDepartment(const std::string& instituteName) {
    departmentMenu(instituteName);
    int depChoice;
    std::cin >> depChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (depChoice == 3) return;

    std::string departmentName;
    if (instituteName == "IITUS") {
        if (depChoice == 1) departmentName = "POVTAS";
        else if (depChoice == 2) departmentName = "IT";
        else {
            std::cout << "Incorrect input.\n";
            return;
        }
    } else if (instituteName == "IEIE") {
        if (depChoice == 1) departmentName = "Electricity and electrical engineering";
        else if (depChoice == 2) departmentName = "Heat power engineering and heat engineering";
        else {
            std::cout << "Incorrect input.\n";
            return;
        }
    } else {
        std::cout << "Incorrect input.\n";
        return;
    }

    selectGroup(instituteName, departmentName);
}
//Выбор групп в разных институтах и кафедрах
void ControlUnit::selectGroup(const std::string& instituteName, const std::string& departmentName) {
    std::cout << "\nGroups:\n";
    std::vector<std::string> groupNames;
    if (instituteName == "IITUS") {
        if (departmentName == "POVTAS") {
            std::cout << "1. VT-232\n2. PV-233\n";
            groupNames = {"VT-232", "PV-233"};
        } else if (departmentName == "IT") {
            std::cout << "1. IST-231\n2. IST-232\n";
            groupNames = {"IST-231", "IST-232"};
        } else {
            std::cout << "No groups for this department.\n";
            return;
        }
    } else if (instituteName == "IEIE") {
        if (departmentName == "Electricity and electrical engineering") {
            std::cout << "1. EiE-231\n2. EiE-232\n";
            groupNames = {"EiE-231", "EiE-232"};
        } else if (departmentName == "Heat power engineering and heat engineering") {
            std::cout << "1. TiT-231\n2. TiT-232\n";
            groupNames = {"TiT-231", "TiT-232"};
        } else {
            std::cout << "No groups for this department.\n";
            return;
        }
    } else {
        std::cout << "Incorrect input.\n";
        return;
    }
    std::cout << "3. Back\n";

    int groupChoice;
    std::cin >> groupChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (groupChoice == 3) return;

    if (groupChoice < 1 || groupChoice > groupNames.size()) {
        std::cout << "Incorrect input.\n";
        return;
    }

    std::string groupName = groupNames[groupChoice - 1];
    selectStudent(instituteName, departmentName, groupName);
}
//Выбор студента из группы (в группе может быть несколько студентов)
void ControlUnit::selectStudent(const std::string& instituteName, const std::string& departmentName, const std::string& groupName) {
    std::vector<std::string> studentIds = gradeBook->getStudentIds(instituteName, departmentName, groupName);

    if (studentIds.empty()) {
        std::cout << "No students in the group.\n";
        return;
    }

    std::cout << "\nStudents:\n";
    for (size_t i = 0; i < studentIds.size(); ++i) {
        json studentInfo = gradeBook->getStudentInfo(instituteName, departmentName, groupName, studentIds[i]);
        if (!studentInfo.empty()) {
            std::cout << i + 1 << ". " << studentInfo["surname"].get<std::string>() << " "
                      << studentInfo["name"].get<std::string>() << " "
                      << studentInfo["middlename"].get<std::string>()
                      << " (ID: " << studentIds[i] << ")" << "\n";
        } else {
            std::cout << i + 1 << ". (Error: Student information not found) (ID: " << studentIds[i] << ")\n";
        }
    }

    int studentChoice;
    std::cout << "Select a student (1-" << studentIds.size() << "): ";
    std::cin >> studentChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (studentChoice < 1 || studentChoice > studentIds.size()) {
        std::cout << "Incorrect input.\n";
        return;
    }

    std::string studentId = studentIds[studentChoice - 1];
    studentOperations(instituteName, departmentName, groupName, studentId);
}
//Операция над студентом (изменить оценку, посчитать средний балл, получить всю информацию о студенте)
void ControlUnit::studentOperations(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId) {
    while (true) {
        std::cout << "\nStudent operations (ID: " << studentId << "):\n";
        std::cout << "1. Change grade\n2. Get grade average\n3. Get information about student\n4. Back\n";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                changeGrade(institute, department, group, studentId);
                break;
            case 2:
                displayAverageGrade(studentId);
                break;
            case 3:
                displayStudentInfo(institute, department, group, studentId);
                break;
            case 4:
                return;
            default:
                std::cout << "Incorrect input.\n";
        }
    }
}
//Изменение оценок по предмету
//Модернизировано - возможность изменять у предмета тип учебной нагрузки
//Сделано под фабричный метод, а не абстрактную фабрику
void ControlUnit::changeGrade(const std::string& institute,
                              const std::string& department,
                              const std::string& group,
                              const std::string& studentId) {
    // Получаем информацию о студенте
    json studentInfo = gradeBook->getStudentInfo(institute, department, group, studentId);

    // Проверяем, найден ли студент
    if (studentInfo.empty()) {
        std::cout << "Error: Student not found!\n";
        return;
    }

    // Выводим список предметов студента
    std::cout << "\nCurrent subjects and grades:\n";
    for (auto& [subject, grade] : studentInfo["grades"].items()) {
        std::cout << "- " << subject << ": "
                  << grade["mark"].get<int>()
                  << " (" << grade["type"].get<std::string>() << ")\n";
    }

    // Запрашиваем у пользователя предмет для изменения
    std::string subject;
    std::cout << "\nEnter subject name to change: ";
    std::getline(std::cin, subject);

    // Проверяем существование предмета
    if (!studentInfo["grades"].contains(subject)) {
        std::cout << "Error: Subject not found!\n";
        return;
    }

    // Получаем текущий тип нагрузки
    std::string currentType = studentInfo["grades"][subject]["type"].get<std::string>();
    int currentMark = studentInfo["grades"][subject]["mark"].get<int>();

    // Запрашиваем новый тип нагрузки (если пользователь хочет изменить)
    std::cout << "\nCurrent workload type: " << currentType
              << "\nDo you want to keep the current type? (y/n): ";//y - оставить тип, n - поменять на другой
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    //Новый тип
    WorkloadType newType;
    if (choice == 'n' || choice == 'N') {
        std::cout << "Select new workload type:\n"
                  << "1. exam\n2. laboratory\n3. coursework\n4. credit\n";
        int typeChoice;
        std::cin >> typeChoice;
        std::cin.ignore();

        switch (typeChoice) {
            case 1: newType = WorkloadType::EXAM; break;
            case 2: newType = WorkloadType::LAB; break;
            case 3: newType = WorkloadType::COURSE_PROJECT; break;
            case 4: newType = WorkloadType::CREDIT; break;
            default:
                std::cout << "Invalid choice. Keeping current type.\n";//Если неверный тип - сохраняем старый
                newType = static_cast<WorkloadType>(studentInfo["grades"][subject]["type"].get<int>());
        }
    } else {
        // Преобразуем строковый тип в enum
        if (currentType == "exam") newType = WorkloadType::EXAM;
        else if (currentType == "laboratory") newType = WorkloadType::LAB;
        else if (currentType == "coursework") newType = WorkloadType::COURSE_PROJECT;
        else newType = WorkloadType::CREDIT;
    }

    // Запрашиваем новую оценку (не на зачет, его игнорируем)
    int newMark = currentMark;
    if (newType != WorkloadType::CREDIT) {
        std::cout << "Enter new grade (2-5): ";
        std::cin >> newMark;
        std::cin.ignore();

        if (newMark < 2 || newMark > 5) {
            std::cout << "Invalid grade. Keeping current grade.\n";//если некорректная оценка - оставляем старую
            newMark = currentMark;
        }
    } else {
        newMark = 0; // Для зачета оценка всегда 0
    }

    // Создаем объект нагрузки через фабричный метод
    std::unique_ptr<Workload> workload = Workload::createWorkload(newType, newMark);

    // Обновляем оценку в журнале
    gradeBook->addGrade(institute, department, group, studentId,
                        subject, newType, workload->getMark());

    std::cout << "Grade has been changed!\n";
}
//Вывод среднего арифметического оценок
void ControlUnit::displayAverageGrade(const std::string& studentId) {
    double average = gradeBook->calculateAverage(studentId);
    std::cout << "Average score: " << average << "\n";
}
//Вывод полной информации о студенте
void ControlUnit::displayStudentInfo(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId) {
    json studentInfo = gradeBook->getStudentInfo(institute, department, group, studentId);

    if (studentInfo.empty()) {
        std::cout << "Student not found.\n";
        return;
    }

    std::cout << "FULL NAME: " << studentInfo["surname"].get<std::string>() << " "
              << studentInfo["name"].get<std::string>() << " "
              << studentInfo["middlename"].get<std::string>() << "\n";
    std::cout << "Group: " << group << "\n";
    std::cout << "Credit book number: " << studentId << "\n";
    std::cout << "\nGrades:\n";

    for (auto it = studentInfo["grades"].begin(); it != studentInfo["grades"].end(); ++it) {
        std::string subject = it.key();
        json gradeData = it.value();
        std::cout << "  " << subject << ": " << gradeData["mark"].get<int>() << " (" << gradeData["type"].get<std::string>() << ")\n";
    }
}