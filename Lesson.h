//
// Created by Diogo Sousa on 25/10/2023.
//

#ifndef UNTITLED_LESSON_H
#define UNTITLED_LESSON_H

#include <vector>
#include "Student.h"
#include <string>
using namespace std;

enum week { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

class Lesson {
private:
    string classCode;
    string ucCode;
    string type;
    double Duration;
    double StartHour;
    double endHour;
    string day;
    week day_;
    int cap;
    int maxCap = 30;
    vector<Student> students;
public:
    Lesson(string classCode);
    Lesson(string classCode, string ucCode, string type, string weekday, double duration, double startHour);
    week convert(string day);
    void printCode();
    void setType (string type);
    string getType();
    void setDuration(double duration);
    void setStartHour(double starthour);
    void setEndHour();
    void setDay(string day);
    string getDay();
    week getDay_();
    double getDuration();
    double getStartHour();
    double getEndHour();
    string getClasscode();
    string getUcCode();
    int getMaxCap();
    bool operator== (const Lesson& other) const;
    vector<Student>& getStudents();
    void addStudent(Student student);
    void removeStudent(Student student);
};

#endif