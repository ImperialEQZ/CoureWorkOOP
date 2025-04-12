#include <iostream>
#include "Student.h"
#include "Grade.h"
#include <windows.h>
//ТЕстики
int main() {
    SetConsoleOutputCP(CP_UTF8);
    Grade grade1("Математика", 5);
    grade1.outputGrade();

    // Student Example
    Student student("БГТУ", "ФОПИ", "88005553535", "ВТ-232", "Санек", "Александров", "Александрович");
    student.outputStudentInfo();

    Grade grade2("Информатика", 4);
    Grade grade3("ООП", 3);
    Grade grade4("Вычмат", 5);//по итогу - 5+4+3+5 = 17\4 = 4.25 = 4
    student.grades.push_back(grade1);
    student.grades.push_back(grade2);
    student.grades.push_back(grade3);
    student.grades.push_back(grade4);
    student.outputGrades();

    double avg = student.getAverageRating();
    std::cout << "Средний балл: " << avg << std::endl;
    return 0;
}