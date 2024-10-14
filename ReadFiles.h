//
// Created by miguel-duarte on 01-11-2023.
//

#ifndef UNTITLED_READFILES_H
#define UNTITLED_READFILES_H
#include <vector>
#include "UC.h"
#include "Class.h"
#include "Request.h"

class ReadFiles {
private:
    vector<UC> ucS;
    vector<Class> classes;
    vector<Student> students;
    vector<Request> requests;
public:
    void class_per_uc_reader();
    void classes_reader();
    void students_classes_reader();
    vector<UC> getUcs();
    UC& getUC(string ucName);
    vector<Student> getStudents();
    Student& getStudent(string up);
    bool hasClass(string classCode);
    Class& getClass(string classCode);
    vector<Class>& getClasses();
    vector<Lesson> lessonsForStudent(Student student);
    void setYearStudents();
    vector<Lesson> sortLessonsByDay(vector<Lesson> lessons);
    void createClasses();
    vector<Class> getClassChances(string uc, string currentClass, Student student, bool addUC = false);
    vector<Class> getClassChances(string oldUC, string oldClass, string newUC, Student student);
    bool lessonsOverlap(Lesson l1, Lesson l2);
    int max_(vector<Class> classes);
    int min_(vector<Class> classes);
    void changeClass(Class old, Class new_, string uc, Student student, bool addToLog);
    void addUC(UC new_, Class newClass, Student student, bool addToLog);
    void removeUC(UC old_, Class oldClass, Student student, bool addToLog);
    void changeUC(UC old_, Class oldclass, UC new_, Class newClass, Student student, bool addToLog);
    void loadRequests();
    vector<Request>& getRequests();
};


#endif //UNTITLED_READFILES_H