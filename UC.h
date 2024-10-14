//
// Created by Diogo Sousa on 25/10/2023.
//

#ifndef UNTITLED_UC_H
#define UNTITLED_UC_H
#include <list>
#include <string>
#include <vector>
#include "Lesson.h"
using namespace std;

class UC {
private:
    string UCname;
    vector<Lesson> lessons;
    int maxOccupation = 400;
public:
    UC();
    UC(std::string UCname);
    void getSchedule();
    void addLesson(string classCode, string ucCode, string type, string weekday, double duration, double startHour);
    bool customComparator(Lesson a, Lesson b);
    string getUCname();
    vector<Lesson>& getLessons();
    vector<Lesson> getLessons(string lessonName);
    vector<Lesson> getLessonsbyDay();
    vector<Lesson> getLessonsbyDay(vector<Lesson>& lessons_);
    int getYear();
    void removeStudent(string classCode, Student student);
    void addStudent(string classCode, Student student);
    double UChours();
    bool operator== (const UC& other) const;
};


#endif //UNTITLED_UC_H