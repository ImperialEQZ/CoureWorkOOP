#ifndef COURSEWORKOOP_WORKLOAD_H
#define COURSEWORKOOP_WORKLOAD_H
#include <string>
#include <memory>
//Перечисление типов учебной нагрузки
enum class WorkloadType { LAB, EXAM, COURSE_PROJECT, CREDIT /*зачет*/ };
//Учебная нагрузка
class Workload {
public:
    virtual ~Workload() = default;
    virtual WorkloadType getType() const = 0;
    virtual int getMark() const = 0;
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
//Реализация Абстрактной фабрики
class WorkloadFactory {
public:
    virtual ~WorkloadFactory() = default;
    virtual std::unique_ptr<Workload> createLab(int mark) = 0;
    virtual std::unique_ptr<Workload> createExam(int mark) = 0;
    virtual std::unique_ptr<Workload> createCourseProject(int mark) = 0;
    virtual std::unique_ptr<Workload> createCredit() = 0;
};

class TechnicalWorkloadFactory : public WorkloadFactory {
public:
    //Создание лабораторной
    std::unique_ptr<Workload> createLab(int mark) override {
        return std::make_unique<LabWork>(mark);
    }
    //Создание экзамена
    std::unique_ptr<Workload> createExam(int mark) override {
        return std::make_unique<ExamWork>(mark);
    }
    //Создание курсовой работы
    std::unique_ptr<Workload> createCourseProject(int mark) override {
        return std::make_unique<CourseProject>(mark);
    }
    //Создание зачета
    std::unique_ptr<Workload> createCredit() override {
        return std::make_unique<CreditWork>();
    }
};
#endif //COURSEWORKOOP_WORKLOAD_H
