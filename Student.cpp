//
// Created by miguel-duarte on 01-11-2023.
//

#include "Student.h"
#include <iostream>

void Student::addClass(string uc, string classcode){
    for (int i = 0; i < student_classes.size(); i++) {
        if (student_classes[i].first == uc) return;
    }
    student_classes.push_back(make_pair(uc, classcode));
    ucs++;
}

void Student::removeClass(std::string uc) {
    for (int i = 0; i < student_classes.size(); i++) {
        if (student_classes[i].first == uc)
        {
            student_classes.erase(student_classes.begin() + i);
            ucs--;
        }
    }
}

Student::Student(std::string up, std::string name) {
    this->up = up;
    this->name= name;
}

std::string Student::getUp() {
    return this->up;
}

std::string Student::getName() {
    return this->name;
}

std::vector<pair<string,string>> Student::getStudent_classes(){
    return this->student_classes;
}

void Student::setYear() {
    int y = 0;
    for (int i = 0; i < student_classes.size(); i++) {
        y = student_classes[i].second[0] - '0';
    }
    year = y;
}

int Student::getYear() { return this->year;}

int Student::getUcsNumber() { return this->ucs; }

bool Student::operator==(const Student& other) const{
    return(up == other.up);
}

