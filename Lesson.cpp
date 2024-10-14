//
// Created by Diogo Sousa on 25/10/2023.
//

#include <string>
#include <iostream>
#include "Lesson.h"
using namespace std;

Lesson::Lesson(string classCode) {
    this->classCode = classCode;
}

Lesson::Lesson(string classCode, string ucCode, string type, string weekday, double duration, double startHour) {
    this->classCode = classCode;
    this->ucCode = ucCode;
    this->type = type;
    setDay(weekday);
    this->Duration = duration;
    this->StartHour = startHour;
    setEndHour();
}

void Lesson::printCode() {
    cout << this->classCode << " ";
}

week Lesson::convert(string day) {
    if(day == "Monday") return Monday;
    else if(day == "Thursday") return Thursday;
    else if(day == "Wednesday") return Wednesday;
    else if(day == "Tuesday") return Tuesday;
    else if(day == "Friday") return Friday;
    else if(day == "Saturday") return Saturday;
    else if(day == "Sunday") return Sunday;
}

void Lesson::setDay(string day) {
    this->day = day;
    this->day_ = convert(day);
}

string Lesson::getDay() {
    return this->day;
}

week Lesson::getDay_() {
    return this->day_;
}

void Lesson::setType(string type) {
    this->type = type;
}

string Lesson::getType() {
    return this->type;
}

void Lesson::setDuration(double duration) {
    this->Duration = duration;
}

double Lesson::getDuration() {
    return this->Duration;
}

void Lesson::setStartHour(double starthour) {
    this->StartHour = starthour;
}

double Lesson::getStartHour() {
    return this->StartHour;
}

void Lesson::setEndHour() {
    this->endHour = StartHour + Duration;
}

double Lesson::getEndHour() {
    return this->endHour;
}

string Lesson::getClasscode(){
    return classCode;
}

string Lesson::getUcCode() {
    return ucCode;
}

vector<Student>& Lesson::getStudents(){
    return students;
}

void Lesson::addStudent(Student student) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getName() == student.getName()) return;
    }
    this->students.push_back(student);
    cap++;
}

void Lesson::removeStudent(Student student) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getUp() == student.getUp())
        {
            students.erase(students.begin() + i);
            cap--;
        }
    }
}

int Lesson::getMaxCap() { return this->maxCap; }

bool Lesson::operator== (const Lesson& other) const {
    return (classCode == other.classCode);
}