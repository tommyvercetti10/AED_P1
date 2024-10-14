//
// Created by miguel-duarte on 01-11-2023.
//

#include "ReadFiles.h"
#include "UC.h"
#include "Lesson.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

/*void ReadFiles::class_per_uc_reader(){
    string line, uc, classcode;
    string compare = "x";
    ifstream in("../schedule/classes_per_uc.csv");
    getline(in, line);
    cout << uc;
    while(getline(in, line)){
        stringstream iss(line);
        getline(iss, uc, ',');
        getline(iss, classcode, '\r');
        if(uc != compare){
            compare = uc;
            UC subject(uc);
            ucS.push_back(subject);
            //cout << '\n' << subject.getUCname() << ": ";
        }
        ucS.at(ucS.size()-1).addClass(classcode); //usar o metodo da class UC addClass para adiconar uma turma ao vetor da UC
        //cout << Lesson(classcode).getClasscode() << " ";
    }
    //cout << '\n' << '\n';
}*/

/**
 *@brief This function reads the csv file that provides the information about a lesson.
 *We remove the existing UCs, create an object for each one and store them in an array. We also create an object for the lessons, which are stored in their UC.
 */
void ReadFiles::classes_reader(){
    string line,uc,classcode, weekday, starthour, duration, type;
    ifstream in("../schedule/classes.csv");
    getline(in, line);
    string compare = "x";
    int j=0;
    while(getline(in, line)){
        stringstream iss(line);
        getline(iss, classcode, ',');
        getline(iss, uc, ',');
        getline(iss, weekday, ',');
        getline(iss, starthour, ',');
        getline(iss, duration, ',');
        getline(iss, type, '\r');

        if(uc != compare){
            j=0;
            compare = uc;
            UC subject(uc);
            ucS.push_back(subject);
        }

        ucS.at(ucS.size()-1).addLesson(classcode, uc, type, weekday, stod(duration), stod(starthour));
        j++;
    }
    cout << '\n' << '\n';
}

/**
 * @brief This function reads the csv file that provides the information about the students.
 *
 */
void ReadFiles::students_classes_reader() {
    string line, up, name, uc, classcode;
    ifstream in("../schedule/students_classes.csv");
    getline(in, line);
    Student student("0","0");
    int j=0;
    while(getline(in, line)) {
        stringstream iss(line);
        getline(iss, up, ',');
        getline(iss, name, ',');
        getline(iss, uc, ',');
        getline(iss, classcode, '\r');
        Student laststudent(up,name);
        auto its = find(students.begin(), students.end(), laststudent);
        if(its == students.end()){
            student = laststudent;
            students.push_back(student);
            j++;
        }
        for(int i=0; i< ucS.size(); i++){
            if(ucS[i].getUCname() == uc){
                for(int k=0; k<ucS[i].getLessons().size(); k++){
                    if(ucS[i].getLessons()[k].getClasscode() == classcode){
                        ucS[i].getLessons()[k].addStudent(student);
                    }
                }
                break;
            }
        }
        students.at(students.size()-1).addClass(uc, classcode);
    }
    setYearStudents();
}


vector<UC> ReadFiles::getUcs() {
    return this->ucS;
}

UC& ReadFiles::getUC(std::string ucName) {
    for (int i = 0; i < ucS.size(); i++) {
        if (ucS[i].getUCname() == ucName) return ucS[i];
    }
}

void ReadFiles::createClasses() {
    for (int i = 0; i < ucS.size(); i++) {
        for (int b = 0; b < ucS[i].getLessons().size(); b++) {
            if (!hasClass(ucS[i].getLessons()[b].getClasscode())) {
                Class newClass(ucS[i].getLessons()[b].getClasscode(), (int)ucS[i].getLessons()[b].getClasscode().at(0) - 48);
                classes.push_back(newClass);
            }
            Lesson newLesson = ucS[i].getLessons()[b];
            getClass(ucS[i].getLessons()[b].getClasscode()).addLesson(newLesson);
        }
    }
}

vector<Student> ReadFiles::getStudents() {return students;}

bool ReadFiles::hasClass(std::string classCode) {
    for (int i = 0; i < classes.size(); i++) {
        if (classCode == classes[i].getClassCode()) return true;
    }
    return false;
}

Class& ReadFiles::getClass(std::string classCode) {
    for (int i = 0; i < classes.size(); i++) {
        if (classCode == classes[i].getClassCode()) return classes[i];
    }
}

vector<Class>& ReadFiles::getClasses() {
    return this->classes;
}

vector<Lesson> ReadFiles::lessonsForStudent(Student student) {
    vector<Lesson> lessons;
    for (int i = 0; i < student.getStudent_classes().size(); i++) {
        vector<Lesson> lessonsToAdd = getUC(student.getStudent_classes()[i].first).getLessons(student.getStudent_classes()[i].second);
        for (Lesson lesson : lessonsToAdd) lessons.push_back(lesson);
    }
    return lessons;
}

vector<Lesson> ReadFiles::sortLessonsByDay(vector<Lesson> lessons) {
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

/**
 * This function obtains the classes of the chosen UC that the student can change to
 * @param uc
 * @param currentClass
 * @param student
 * @param addUC
 * @return classes of the chosen UC that the student can change to
 */
vector<Class> ReadFiles::getClassChances(std::string uc, std::string currentClass, Student student, bool addUC) {
    vector<Class> classes_ = classes;
    int year = currentClass[0] - '0';
    if (addUC) year = getUC(uc).getYear();
    // Remove the current class and all the classes from a year different than the current UC
    classes_.erase(remove_if(classes_.begin(), classes_.end(), [currentClass, year](Class& elem) {
        return elem.getClassCode() == currentClass || elem.getYear() != year;
    }), classes_.end());
    // Get the current schedule, removing the UC we want to trade
    vector<Lesson> lessons = lessonsForStudent(student);
    if (!addUC) {
        lessons.erase(remove_if(lessons.begin(), lessons.end(), [currentClass, uc](Lesson& elem) {
            return elem.getClasscode() == currentClass && elem.getUcCode() == uc;
        }), lessons.end());
    }
    int i = 0;
    bool overlap = false;
    // Compare the current schedule with all the different classes of the UC
    while (i < classes_.size()) {
        vector<Lesson> classLessons = classes_[i].getLessons(uc);
        if (classLessons.size() == 0) overlap = true;
        for (int i = 0; i < lessons.size(); i++) {
            for (int c = 0; c < classLessons.size(); c++) {
                if (lessonsOverlap(lessons[i], classLessons[c])) {
                    overlap = true;
                    break;
                }
            }
            if (overlap) break;
        }
        if (overlap)
        {
            classes_.erase(classes_.begin() + i);
            overlap = false;
        }
        else i++;
    }
    i = 0;
    // Check the balance
    if (classes_.size() > 1) {
        int max = max_(classes_);
        int min = min_(classes_);
        if (max - min > 4) {
            while (i < classes_.size()) {
                if (classes_[i].getLessons()[0].getStudents().size() != min)
                    classes_.erase(classes_.begin() + i);
                else i++;
            }
        }
        else if (max - min == 4) {
            while (i < classes_.size()) {
                if (classes_[i].getLessons()[0].getStudents().size() == max)
                    classes_.erase(classes_.begin() + i);
                else i++;
            }
        }
    }
    // Check the occupation
    int maxOccupation;
    if (!classes_.empty()) maxOccupation = classes_[0].getLessons()[0].getMaxCap();
    classes_.erase(remove_if(classes_.begin(), classes_.end(), [maxOccupation](Class& elem) {
        return elem.getLessons()[0].getStudents().size() == maxOccupation;
    }), classes_.end());
    return classes_;
}

/**
 * @brief This function obtains which classes the student can change to.
 *  The function receives the student, the class they are currently in and the class's UC. Taking into account criteria such as class balance, occupancy and class overlap, it returns the classes in which the change is possible.
 *
 */
vector<Class> ReadFiles::getClassChances(std::string oldUC, std::string oldClass, std::string newUC, Student student) {
    vector<Class> classes_ = classes;
    int year = getUC(newUC).getYear();
    // Remove all the classes from a year different than the current UC
    classes_.erase(remove_if(classes_.begin(), classes_.end(), [year](Class& elem) {
        return elem.getYear() != year;
    }), classes_.end());
    // Get the current schedule, removing the UC we want to trade
    vector<Lesson> lessons = lessonsForStudent(student);
    lessons.erase(remove_if(lessons.begin(), lessons.end(), [oldUC](Lesson& elem) {
        return elem.getUcCode() == oldUC;
    }), lessons.end());
    int i = 0;
    bool overlap = false;
    // Compare the current schedule with all the different classes of the UC
    while (i < classes_.size()) {
        vector<Lesson> classLessons = classes_[i].getLessons(newUC);
        if (classLessons.size() == 0) overlap = true;
        for (int i = 0; i < lessons.size(); i++) {
            for (int c = 0; c < classLessons.size(); c++) {
                if (lessonsOverlap(lessons[i], classLessons[c])) {
                    overlap = true;
                    break;
                }
            }
            if (overlap) break;
        }
        if (overlap)
        {
            classes_.erase(classes_.begin() + i);
            overlap = false;
        }
        else i++;
    }
    i = 0;
    // Check the balance
    if (classes_.size() > 1) {
        int max = max_(classes_);
        int min = min_(classes_);
        if (max - min > 4) {
            while (i < classes_.size()) {
                if (classes_[i].getLessons()[0].getStudents().size() != min)
                    classes_.erase(classes_.begin() + i);
                else i++;
            }
        }
        else if (max - min == 4) {
            while (i < classes_.size()) {
                if (classes_[i].getLessons()[0].getStudents().size() == max)
                    classes_.erase(classes_.begin() + i);
                else i++;
            }
        }
    }
    // Check the occupation
    int maxOccupation;
    if (!classes_.empty()) maxOccupation = classes_[0].getLessons()[0].getMaxCap();
    classes_.erase(remove_if(classes_.begin(), classes_.end(), [maxOccupation](Class& elem) {
        return elem.getLessons()[0].getStudents().size() == maxOccupation;
    }), classes_.end());
    return classes_;
}

bool ReadFiles::lessonsOverlap(Lesson l1, Lesson l2) {
    if (l1.getDay_() == l2.getDay_()) {
        return l1.getEndHour() > l2.getStartHour() && (l2.getEndHour() > l1.getStartHour());
    }
    else return false;
}

void ReadFiles::setYearStudents() {
    for (int i = 0; i < students.size(); i++) {
        students[i].setYear();
    }
}

int ReadFiles::max_(vector<Class> classes) {
    int max = 0;
    for (int i = 0; i < classes.size(); i++) {
        if (classes[i].getLessons()[0].getStudents().size() > max)
            max = classes[i].getLessons()[0].getStudents().size();
    }
    return max;
}

int ReadFiles::min_(vector<Class> classes) {
    int min = 10000;
    for (int i = 0; i < classes.size(); i++) {
        if (classes[i].getLessons()[0].getStudents().size() < min)
            min = classes[i].getLessons()[0].getStudents().size();
    }
    return min;
}

Student& ReadFiles::getStudent(std::string up) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getUp() == up) return students[i];
    }
}

/**
 * @brief Function to change class.
 *
 * Class changes are made by removing the student from the old class and adding them to the new one.
 *
 * @param old class
 * @param new_ class
 * @param uc
 * @param student
 * @param addToLog
 */
void ReadFiles::changeClass(Class old, Class new_, string uc, Student student, bool addToLog) {
    Request request(old, new_, student, uc, "ClassChange");
    if (addToLog) request.addToLog();
    requests.push_back(request);
    getUC(uc).removeStudent(old.getClassCode(), student); // remove student from UC lessons
    getUC(uc).addStudent(new_.getClassCode(), student); // add student to UC lessons
    getClass(old.getClassCode()).removeStudent(uc, student); // remove student from the class in the UC
    getClass(new_.getClassCode()).addStudent(uc, student); // add student to a new class in the UC
    auto it = find(students.begin(), students.end(), student);
    it->removeClass(uc); // update Student
    it->addClass(uc, new_.getClassCode()); // update Student
}

void ReadFiles::addUC(UC new_, Class newClass, Student student, bool addToLog) {
    Request request(new_, newClass, student, "UCAdd");
    if (addToLog) request.addToLog();
    requests.push_back(request);
    getUC(new_.getUCname()).addStudent(newClass.getClassCode(), student); // add student to UC lessons
    getClass(newClass.getClassCode()).addStudent(new_.getUCname(), student); // add student to a new class in the UC
    auto it = find(students.begin(), students.end(), student);
    it->addClass(new_.getUCname(), newClass.getClassCode()); // update Student
}

void ReadFiles::removeUC(UC old_, Class oldClass, Student student, bool addToLog) {
    Request request(oldClass, old_, student, "UCRemove");
    if (addToLog) request.addToLog();
    requests.push_back(request);
    getUC(old_.getUCname()).removeStudent(oldClass.getClassCode(), student); // remove student from UC lessons
    getClass(oldClass.getClassCode()).removeStudent(old_.getUCname(), student); // remove student from the class in the UC
    auto it = find(students.begin(), students.end(), student);
    it->removeClass(old_.getUCname()); // update Student
}

void ReadFiles::changeUC(UC old_, Class oldclass, UC new_, Class newClass, Student student, bool addToLog) {
    Request request(old_, new_, oldclass, newClass, student, "UCChange");
    if (addToLog) request.addToLog();
    requests.push_back(request);
    getUC(old_.getUCname()).removeStudent(oldclass.getClassCode(), student); // remove student from UC lessons
    getUC(new_.getUCname()).addStudent(newClass.getClassCode(), student); // add student to UC lessons
    getClass(oldclass.getClassCode()).removeStudent(old_.getUCname(), student); // remove student from the class in the UC
    getClass(newClass.getClassCode()).addStudent(new_.getUCname(), student); // add student to a new class in the UC
    auto it = find(students.begin(), students.end(), student);
    it->removeClass(old_.getUCname()); // update Student
    it->addClass(new_.getUCname(), newClass.getClassCode()); // update Student
}


void ReadFiles::loadRequests() {
    ifstream in("../log.txt");
    string line, type, up, uc, oldClass, newClass, oldUc, newUc;
    while(getline(in, line)) {
        stringstream iss(line);
        getline(iss, type, '-');
        getline(iss, up, '-');
        if (type == "ClassChange" || type == "UCAdd" || type == "UCRemove") getline(iss, uc, '-');
        if (type == "ClassChange") getline(iss, oldClass, '-');
        if (type == "UCChange") {
            getline(iss, oldUc, '-');
            getline(iss, oldClass, '-');
            getline(iss, newUc, '-');
        }
        getline(iss, newClass, '\r');
        if (type == "ClassChange") changeClass(getClass(oldClass), getClass(newClass), uc, getStudent(up), false);
        if (type == "UCAdd") addUC(getUC(uc), getClass(newClass), getStudent(up), false);
        if (type == "UCRemove") removeUC(getUC(uc), getClass(newClass), getStudent(up), false);
        if (type == "UCChange") changeUC(getUC(oldUc), getClass(oldClass), getUC(newUc), getClass(newClass), getStudent(up), false);
    }
}

vector<Request>& ReadFiles::getRequests() {
    return requests;
}
