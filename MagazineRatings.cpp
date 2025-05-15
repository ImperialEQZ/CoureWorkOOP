#include "MagazineRatings.h"

void GradeBook::loadData() {
    std::ifstream f("data.json");
    if (f.peek() == std::ifstream::traits_type::eof()) {
        data = json{{"institutes", json::array()}};
    } else {
        try {
            f >> data;
            // Преобразование данных из JSON в объекты Institute, Department, Group, Student
            for (const auto& instData : data["institutes"]) {
                Institute institute(instData["name"].get<std::string>());
                for (const auto& depData : instData["departments"]) {
                    Department department(depData["name"].get<std::string>());
                    for (const auto& groupData : depData["groups"]) {
                        Group group(groupData["name"].get<std::string>());
                        for (const auto& studentData : groupData["students"]) {
                            Student student(
                                    instData["name"].get<std::string>(),
                                    depData["name"].get<std::string>(), // Используем название кафедры как направление
                                    studentData["id"].get<std::string>(),
                                    groupData["name"].get<std::string>(),
                                    studentData["name"].get<std::string>(),
                                    studentData["surname"].get<std::string>(),
                                    studentData["middlename"].get<std::string>()
                            );
                            // Загрузка оценок для студента
                            for (const auto& [subjectName, gradeData] : studentData["grades"].items()) {
                                WorkloadType type;
                                std::string typeStr = gradeData["type"].get<std::string>();
                                if (typeStr == "exam") type = WorkloadType::EXAM;
                                else if (typeStr == "laboratory") type = WorkloadType::LAB;
                                else if (typeStr == "coursework") type = WorkloadType::COURSE_PROJECT;
                                else type = WorkloadType::CREDIT;
                                int mark = gradeData["mark"].get<int>();
                                Grade grade(subjectName, type, mark);
                                student.grades.push_back(grade);
                            }
                            group.addStudent(student);
                        }
                        department.addGroup(group);
                    }
                    institute.addDepartment(department);
                }
                addInstitute(institute);
            }
        } catch (json::parse_error& e) {
            std::cerr << "Error JSON file parsing: " << e.what() << std::endl;
            data = json{{"institutes", json::array()}};
        }
    }
}
//Реализация паттерна одиночка (синглтон)
GradeBook* GradeBook::getInstance() {
    if (!instance) instance = new GradeBook();
    return instance;
}

void GradeBook::saveData() {
    // Преобразование объектов Institute, Department, Group, Student обратно в JSON
    data["institutes"] = json::array();
    for (const auto& institute : institutes) {
        json instData;
        instData["name"] = institute.name;
        instData["departments"] = json::array();
        for (const auto& department : institute.departments) {
            json depData;
            depData["name"] = department.name;
            depData["groups"] = json::array();
            for (const auto& group : department.groups) {
                json groupData;
                groupData["name"] = group.name;
                groupData["students"] = json::array();
                for (const auto& student : group.students) {
                    json studentData;
                    studentData["id"] = student.NumberCreditBook;
                    studentData["surname"] = student.SurName;
                    studentData["name"] = student.Name;
                    studentData["middlename"] = student.MiddleName;
                    studentData["grades"] = json::object();
                    for (const auto& grade : student.grades) {
                        std::string typeStr;
                        switch(grade.type) {
                            case WorkloadType::EXAM: typeStr = "exam"; break;
                            case WorkloadType::LAB: typeStr = "laboratory"; break;
                            case WorkloadType::COURSE_PROJECT: typeStr = "coursework"; break;
                            case WorkloadType::CREDIT: typeStr = "credit"; break;
                        }
                        studentData["grades"][grade.subjectName] = {{"type", typeStr}, {"mark", grade.mark}};
                    }
                    groupData["students"].push_back(studentData);
                }
                depData["groups"].push_back(groupData);
            }
            instData["departments"].push_back(depData);
        }
        data["institutes"].push_back(instData);
    }
    std::ofstream("data.json") << data.dump(4);
    std::cout << "Data saved in data.json.\n";
}
//Добавление оценки студенту (+ тип нагрузки предмета)
void GradeBook::addGrade(const std::string& instituteName,
                         const std::string& departmentName,
                         const std::string& groupName,
                         const std::string& studentId,
                         const std::string& subjectName,
                         WorkloadType workloadType,
                         int mark) {
    for (auto& institute : institutes) {
        if (institute.name == instituteName) {
            for (auto& department : institute.departments) {
                if (department.name == departmentName) {
                    for (auto& group : department.groups) {
                        if (group.name == groupName) {
                            for (auto& student : group.students) {
                                if (student.NumberCreditBook == studentId) {
                                    // Обновляем оценку или добавляем новую
                                    bool found = false;
                                    for (auto& grade : student.grades) {
                                        if (grade.subjectName == subjectName) {
                                            grade.mark = mark;
                                            grade.type = workloadType;
                                            found = true;
                                            break;
                                        }
                                    }
                                    if (!found) {
                                        Grade newGrade(subjectName, workloadType, mark);
                                        student.grades.push_back(newGrade);
                                    }
                                    saveData(); // Сохраняем после изменения оценки
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cerr << "Error: Student or subject not found!\n";//Если не найдено что-либо
}

double GradeBook::calculateAverage(const std::string& studentId) {
    for (const auto& institute : institutes) {
        for (const auto& department : institute.departments) {
            for (const auto& group : department.groups) {
                for (const auto& student : group.students) {
                    if (student.NumberCreditBook == studentId) {
                        return student.getAverageRating();//В функции реализовано игнорирование зачета
                    }
                }
            }
        }
    }
    return 0.0;
}
// Метод для получения списка studentId
std::vector<std::string> GradeBook::getStudentIds(const std::string& instituteName, const std::string& departmentName, const std::string& groupName) {
    std::vector<std::string> studentIds;
    for (const auto& institute : institutes) {
        if (institute.name == instituteName) {
            for (const auto& department : institute.departments) {
                if (department.name == departmentName) {
                    for (const auto& group : department.groups) {
                        if (group.name == groupName) {
                            for (const auto& student : group.students) {
                                studentIds.push_back(student.NumberCreditBook);
                            }
                            return studentIds;
                        }
                    }
                }
            }
        }
    }
    return studentIds;
}
// Метод для получения информации о студенте
json GradeBook::getStudentInfo(const std::string& instituteName, const std::string& departmentName, const std::string& groupName, const std::string& studentId) {
    for (const auto& institute : institutes) {
        if (institute.name == instituteName) {
            for (const auto& department : institute.departments) {
                if (department.name == departmentName) {
                    for (const auto& group : department.groups) {
                        if (group.name == groupName) {
                            for (const auto& student : group.students) {
                                if (student.NumberCreditBook == studentId) {
                                    json studentInfo;
                                    studentInfo["surname"] = student.SurName;
                                    studentInfo["name"] = student.Name;
                                    studentInfo["middlename"] = student.MiddleName;
                                    studentInfo["grades"] = json::object();
                                    for (const auto& grade : student.grades) {
                                        std::string typeStr = grade.getWorkloadTypeString(grade.type);
                                        studentInfo["grades"][grade.subjectName] = {{"type", typeStr}, {"mark", grade.mark}};
                                    }
                                    return studentInfo;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return json{};
}
//Добавление интитута в файл
void GradeBook::addInstitute(const Institute& institute) {
    institutes.push_back(institute);
}