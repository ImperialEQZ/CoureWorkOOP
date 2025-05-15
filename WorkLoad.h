#ifndef COURSEWORKOOP_WORKLOAD_H
#define COURSEWORKOOP_WORKLOAD_H
#include <memory>
#include <stdexcept>

// Перечисление типов учебной нагрузки
enum class WorkloadType { LAB, EXAM, COURSE_PROJECT, CREDIT };

// Базовый класс учебной нагрузки
class Workload {
public:
    virtual ~Workload() = default;
    virtual WorkloadType getType() const = 0;
    virtual int getMark() const = 0;

    // Фабричный метод
    static std::unique_ptr<Workload> createWorkload(WorkloadType type, int mark = 0);
};

//Лабораторная (имеет оценку, тип работы LAB, влияет на средний балл)
class LabWork : public Workload {
    int mark;
public:
    LabWork(int m);
    WorkloadType getType() const override;
    int getMark() const override;
};
//Экзамен (имеет оценку, тип работы EXAM, влияет на средний балл)
class ExamWork : public Workload {
    int mark;
public:
    ExamWork(int m);
    WorkloadType getType() const override;
    int getMark() const override;
};
//Курсовая (имеет оценку, тип работы COURSE_PROJECT, влияет на средний балл)
class CourseProject : public Workload {
    int mark;
public:
    CourseProject(int m);
    WorkloadType getType() const override;
    int getMark() const override;
};
//Зачет (не имеет оценки (0), тип работы CREDIT, не влияет на средний балл (при подсчете средней оценки не считается колличеством)
class CreditWork : public Workload {
public:
    WorkloadType getType() const override;
    int getMark() const override;
};
#endif //COURSEWORKOOP_WORKLOAD_H
