//
// Created by Diogo Sousa on 25/10/2023.
//

#include "UC.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

UC::UC(std::string UCname){
    this->UCname = UCname;
}

vector<Lesson> UC::getLessonsbyDay() {
    return getLessonsbyDay(lessons);
}

/**
 * Sorts UC lessons by day using a customised comparator
 * @param lessons_
 * @return Chronologically ordered lessons
 */

vector<Lesson> UC::getLessonsbyDay(vector<Lesson>& lessons_) {
    vector<Lesson> sortedLessons = lessons_;
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

void UC::addLesson(string classCode, string ucCode, string type, string weekday, double duration, double startHour) {
    lessons.push_back(Lesson(classCode, ucCode, type, weekday, duration, startHour));
}
string UC::getUCname(){
    return this->UCname;
}

bool UC::operator== (const UC& other) const {
    return (UCname == other.UCname);
}

std::vector<Lesson>& UC::getLessons(){
    return this->lessons;
}

double UC::UChours() {
    double counter= 0;
    for(int i= 0; i < lessons.size(); i++) {
        counter += lessons[i].getDuration();
    }
    return counter;
}

vector<Lesson> UC::getLessons(string lessonName) {
    vector<Lesson> lessons_;
    for (int i = 0; i < lessons.size(); i++) {
        if (lessons[i].getClasscode() == lessonName) lessons_.push_back(lessons[i]);
    }
    return getLessonsbyDay(lessons_);
}

void UC::removeStudent(std::string classCode, Student student) {
    for (int i = 0; i < lessons.size(); i++) {
        if (lessons[i].getClasscode() == classCode)
            lessons[i].removeStudent(student);
    }
}

void UC::addStudent(std::string classCode, Student student) {
    for (int i = 0; i < lessons.size(); i++) {
        if (lessons[i].getClasscode() == classCode) {
            lessons[i].addStudent(student);
        }
    }
}

int UC::getYear() {
    string year = lessons[0].getClasscode().substr(0, 1);
    return stoi(year);
}