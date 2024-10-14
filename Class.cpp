//
// Created by Diogo Sousa on 02/11/2023.
//

#include "Class.h"
#include <iostream>
#include <algorithm>

Class::Class(std::string classCode, int year)
{
    this->classCode = classCode;
    this->year = year;
}

void Class::setClassCode(string classCode) { this->classCode = classCode; }

string Class::getClassCode() { return this->classCode; }

void Class::addLesson(Lesson lesson) { this->lessons.push_back(lesson); }

vector<Lesson> Class::getLessons() { return this->lessons; }

vector<Lesson> Class::getLessons(std::string ucCode) {
    vector<Lesson> lessonsUC;
    for (int i = 0; i < lessons.size(); i++) {
        if (lessons[i].getUcCode() == ucCode) lessonsUC.push_back(lessons[i]);
    }
    return lessonsUC;
}

vector<Lesson> Class::getLessonsbyDay() {
    vector<Lesson> sortedLessons = lessons;
    auto customComparator = [](Lesson a, Lesson b) {
        if ((int)a.getDay_() < (int)b.getDay_()) {
            return true;
        }
        if ((int)a.getDay_() == (int)b.getDay_()) {
            return a.getStartHour() < b.getStartHour();
        }
        return false;
    };
    sort(sortedLessons.begin(), sortedLessons.end(), customComparator);
    return sortedLessons;
}

void Class::setYear(int year) { this->year = year;}

int Class::getYear() { return this->year;}

void Class::removeStudent(std::string uc, Student student) {
    for (int i = 0; i < lessons.size(); i++) {
        if (lessons[i].getUcCode() == uc)
        {
            lessons[i].removeStudent(student);
        }
    }
}

void Class::addStudent(std::string uc, Student student) {
    for (int i = 0; i < lessons.size(); i++) {
        if (lessons[i].getUcCode() == uc)
        {
            lessons[i].addStudent(student);
        }
    }
}