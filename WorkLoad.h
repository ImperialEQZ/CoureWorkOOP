#ifndef COURSEWORKOOP_WORKLOAD_H
#define COURSEWORKOOP_WORKLOAD_H
#include <string>
#include <memory>
#include <stdexcept>
//Перечисление типов учебной нагрузки
enum class WorkloadType { LAB, EXAM, COURSE_PROJECT, CREDIT };

// Предварительное объявление классов, для корректной работы
class LabWork;
class ExamWork;
class CourseProject;
class CreditWork;

//Учебная нагрузка (базовый класс)
class Workload {
public:
    virtual ~Workload() = default;
    virtual WorkloadType getType() const = 0;
    virtual int getMark() const = 0;

    // Паттерн - фабричный метод
    static std::unique_ptr<Workload> createWorkload(WorkloadType type, int mark = 0);
};

//Лабораторная (имеет оценку, тип работы LAB, влияет на средний балл)
class LabWork : public Workload {
    int mark;
public:
    LabWork(int m) : mark(m) {}
    WorkloadType getType() const override { return WorkloadType::LAB; }
    int getMark() const override { return mark; }
};
//Экзамен (имеет оценку, тип работы EXAM, влияет на средний балл)
class ExamWork : public Workload {
    int mark;
public:
    ExamWork(int m) : mark(m) {}
    WorkloadType getType() const override { return WorkloadType::EXAM; }
    int getMark() const override { return mark; }
};
//Курсовая (имеет оценку, тип работы COURSE_PROJECT, влияет на средний балл)
class CourseProject : public Workload {
    int mark;
public:
    CourseProject(int m) : mark(m) {}
    WorkloadType getType() const override { return WorkloadType::COURSE_PROJECT; }
    int getMark() const override { return mark; }
};
//Зачет (не имеет оценки (0), тип работы CREDIT, не влияет на средний балл (при подсчете средней оценки не считается колличеством)
class CreditWork : public Workload {
public:
    WorkloadType getType() const override { return WorkloadType::CREDIT; }
    int getMark() const override { return 0; }
};

// Реализация фабричного метода (после объявления всех классов)
inline std::unique_ptr<Workload> Workload::createWorkload(WorkloadType type, int mark) {
    switch (type) {
        case WorkloadType::LAB:
            return std::make_unique<LabWork>(mark);
        case WorkloadType::EXAM:
            return std::make_unique<ExamWork>(mark);
        case WorkloadType::COURSE_PROJECT:
            return std::make_unique<CourseProject>(mark);
        case WorkloadType::CREDIT:
            return std::make_unique<CreditWork>();
        default:
            throw std::invalid_argument("Error: Incorrect workload type");//некорректный тип рабочей нагрузки
    }
}
#endif //COURSEWORKOOP_WORKLOAD_H
