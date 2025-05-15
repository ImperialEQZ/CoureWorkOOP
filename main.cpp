#include "ControlUnit.h"
#include "MagazineRatings.h"
#include "Student.h"
#include "StudentFactory.h"

int main() {
    GradeBook* gradeBook = GradeBook::getInstance();

    // Создание институтов (ИИТУС, ИЭИЭ)
    Institute IITUS("IITUS");
    Institute IEIE("IEIE");

    // Создание кафедр
    Department POVTAS("POVTAS");
    Department IT("IT");
    Department Energy("Electricity and electrical engineering");
    Department Heat("Heat power engineering and heat engineering");

    // Создание групп
    Group VT232("VT-232");
    Group PV233("PV-233");
    Group EiE231("EiE-231");
    Group TiT232("TiT-232");

    // Создание студентов и добавление их в группы
    // Студент номер 1 ВТ-232
    Student BORCHENKO = StudentFactory::createStudent("IITUS", "POVTAS", "105233196", "VT-232", "Alexander", "Borchenko", "Sergeevich");
    BORCHENKO.grades.push_back(Grade("FOPI", WorkloadType::EXAM, 5));
    BORCHENKO.grades.push_back(Grade("VichMath", WorkloadType::LAB, 4));
    BORCHENKO.grades.push_back(Grade("OOP", WorkloadType::LAB, 3));
    BORCHENKO.grades.push_back(Grade("IO", WorkloadType::CREDIT, 0));
    BORCHENKO.grades.push_back(Grade("EEiS", WorkloadType::LAB, 5));
    BORCHENKO.grades.push_back(Grade("Gardening", WorkloadType::COURSE_PROJECT, 4));
    VT232.addStudent(BORCHENKO);
    // Студент номер 2 ВТ-232
    Student ABOBOVICH = StudentFactory::createStudent("IITUS", "POVTAS", "88005553535", "VT-232", "Petr", "Abobovich", "Vladimirovich");
    ABOBOVICH.grades.push_back(Grade("OP", WorkloadType::EXAM, 4));
    ABOBOVICH.grades.push_back(Grade("Astrology", WorkloadType::LAB, 3));
    ABOBOVICH.grades.push_back(Grade("computer science", WorkloadType::CREDIT, 0));
    ABOBOVICH.grades.push_back(Grade("OOP", WorkloadType::COURSE_PROJECT, 3));
    ABOBOVICH.grades.push_back(Grade("potions", WorkloadType::LAB, 3));
    VT232.addStudent(ABOBOVICH);
    // Студент номер 3 ПВ-233
    Student BOGDANYUS = StudentFactory::createStudent("IITUS", "POVTAS", "11111111", "PV-233", "Bogdan", "Bogdanyus", "Dimonovich");
    BOGDANYUS.grades.push_back(Grade("IO", WorkloadType::EXAM, 5));
    BOGDANYUS.grades.push_back(Grade("VichMath", WorkloadType::LAB, 4));
    BOGDANYUS.grades.push_back(Grade("FOPI", WorkloadType::LAB, 3));
    BOGDANYUS.grades.push_back(Grade("OOP", WorkloadType::CREDIT, 0));
    BOGDANYUS.grades.push_back(Grade("EEiS", WorkloadType::LAB, 5));
    PV233.addStudent(BOGDANYUS);
    // Кафедра: Электроэнергетика и электротехника группа ЭиЭ-231, студент номер 4
    Student PETROV = StudentFactory::createStudent("IEIE", "Electricity and electrical engineering", "67890569", "EiE-231", "Ivan", "Petrov", "Ivanovich");
    PETROV.grades.push_back(Grade("Electricity", WorkloadType::EXAM, 3));
    PETROV.grades.push_back(Grade("Welding", WorkloadType::COURSE_PROJECT, 4));
    EiE231.addStudent(PETROV);
    // Кафедра: Теплоэнергетика и теплотехника группа ТиТ-232, студент номер 5
    Student SIDOROV = StudentFactory::createStudent("IEIE", "Heat power engineering and heat engineering", "1357978936", "TiT-232", "Stepan", "Sidorovich", "Sergeevich");
    SIDOROV.grades.push_back(Grade("Ternod", WorkloadType::EXAM, 5));
    TiT232.addStudent(SIDOROV);

    // Добавление групп в кафедры
    //ПОВТАС
    POVTAS.addGroup(VT232);
    POVTAS.addGroup(PV233);
    //ЭиЭ
    Energy.addGroup(EiE231);
    //ТиТ
    Heat.addGroup(TiT232);

    // Добавление кафедр в институты
    //ИИТУС
    IITUS.addDepartment(POVTAS);
    IITUS.addDepartment(IT);
    //ИЭИЭ
    IEIE.addDepartment(Energy);
    IEIE.addDepartment(Heat);

    // Добавление институтов в журнал
    gradeBook->addInstitute(IITUS);
    gradeBook->addInstitute(IEIE);

    /* Вывод информации об институтах (демонстрация всех данных)
    std::cout << "\nInformation about institutions:\n";
    IITUS.displayInstituteInfo();
    IEIE.displayInstituteInfo();*/

    // Сохранение данных
    gradeBook->saveData();

    ControlUnit control;
    control.run();

    return 0;
}