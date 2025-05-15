#include "WorkLoad.h"

// Реализация LabWork
LabWork::LabWork(int m) : mark(m) {}
WorkloadType LabWork::getType() const { return WorkloadType::LAB; }
int LabWork::getMark() const { return mark; }

// Реализация ExamWork
ExamWork::ExamWork(int m) : mark(m) {}
WorkloadType ExamWork::getType() const { return WorkloadType::EXAM; }
int ExamWork::getMark() const { return mark; }

// Реализация CourseProject
CourseProject::CourseProject(int m) : mark(m) {}
WorkloadType CourseProject::getType() const { return WorkloadType::COURSE_PROJECT; }
int CourseProject::getMark() const { return mark; }

// Реализация CreditWork
WorkloadType CreditWork::getType() const { return WorkloadType::CREDIT; }
int CreditWork::getMark() const { return 0; }

// Реализация фабричного метода
std::unique_ptr<Workload> Workload::createWorkload(WorkloadType type, int mark) {
    switch (type) {
        case WorkloadType::LAB: return std::make_unique<LabWork>(mark);
        case WorkloadType::EXAM: return std::make_unique<ExamWork>(mark);
        case WorkloadType::COURSE_PROJECT: return std::make_unique<CourseProject>(mark);
        case WorkloadType::CREDIT: return std::make_unique<CreditWork>();
        default: throw std::invalid_argument("Invalid workload type");
    }
}
