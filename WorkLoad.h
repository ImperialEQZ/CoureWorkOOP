#ifndef COURSEWORKOOP_WORKLOAD_H
#define COURSEWORKOOP_WORKLOAD_H
#include <string>
#include <memory>

// Типы учебных нагрузок
enum class WorkloadType {
    LAB,
    EXAM,
    COURSE_PROJECT,
    CREDIT
};

// Абстрактный класс учебной нагрузки
class Workload {
public:
    virtual ~Workload() = default;
    virtual WorkloadType getType() const = 0;
    virtual int getMark() const = 0;
};

// Конкретные реализации работ - лаба
class LabWork : public Workload {
    int mark;
public:
    LabWork(int m) : mark(m) {}
    WorkloadType getType() const override { return WorkloadType::LAB; }
    int getMark() const override { return mark; }
};
//Экзамен
class ExamWork : public Workload {
    int mark;
public:
    ExamWork(int m) : mark(m) {}
    WorkloadType getType() const override { return WorkloadType::EXAM; }
    int getMark() const override { return mark; }
};
//курсовая
class CourseProject : public Workload {
    int mark;
public:
    CourseProject(int m) : mark(m) {}
    WorkloadType getType() const override { return WorkloadType::COURSE_PROJECT; }
    int getMark() const override { return mark; }
};
//Зачет
class CreditWork : public Workload {
public:
    WorkloadType getType() const override { return WorkloadType::CREDIT; }
    int getMark() const override { return 0; } // Зачет не влияет на оценку
};

// Абстрактная фабрика
class WorkloadFactory {
public:
    virtual ~WorkloadFactory() = default;
    virtual std::unique_ptr<Workload> createLab(int mark) = 0;
    virtual std::unique_ptr<Workload> createExam(int mark) = 0;
    virtual std::unique_ptr<Workload> createCourseProject(int mark) = 0;
    virtual std::unique_ptr<Workload> createCredit() = 0;
};

// Фабрика для технических специальностей (Только ИИТУС к примеру)
class TechnicalWorkloadFactory : public WorkloadFactory {
public:
    std::unique_ptr<Workload> createLab(int mark) override {
        return std::make_unique<LabWork>(mark);
    }
    std::unique_ptr<Workload> createExam(int mark) override {
        return std::make_unique<ExamWork>(mark);
    }
    std::unique_ptr<Workload> createCourseProject(int mark) override {
        return std::make_unique<CourseProject>(mark);
    }
    std::unique_ptr<Workload> createCredit() override {
        return std::make_unique<CreditWork>();
    }
};
#endif //COURSEWORKOOP_WORKLOAD_H
