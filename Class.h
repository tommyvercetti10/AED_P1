//
// Created by Diogo Sousa on 02/11/2023.
//

#ifndef UNTITLED_CLASS_H
#define UNTITLED_CLASS_H

#include <string>
#include "Lesson.h"
using namespace std;

class Class {
    private:
        string classCode;
        int year;
        vector<Lesson> lessons;
    public:
        Class();
        Class(string classCode, int year);
        void setClassCode(string classCode);
        string getClassCode();
        void addLesson(Lesson lesson);
        vector<Lesson> getLessons();
        vector<Lesson> getLessons(string ucCode);
        vector<Lesson> getLessonsbyDay();
        void setYear(int year);
        int getYear();
        void removeStudent(string uc, Student student);
        void addStudent(string uc, Student student);
};


#endif //UNTITLED_CLASS_H
