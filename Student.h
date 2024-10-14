//
// Created by miguel-duarte on 01-11-2023.
//

#ifndef UNTITLED_STUDENT_H
#define UNTITLED_STUDENT_H

#include <string>
#include <vector>
using namespace std;

class Student {
private:
    string up;
    string name;
    int year;
    int ucs = 0; // number of UCs
    vector<pair<string, string>> student_classes;
public:
    Student(std::string up, std::string name);
    void addClass(string uc, string classcode);
    void removeClass(string uc);
    string getUp();
    string getName();
    vector<pair<string, string>> getStudent_classes();
    void setYear();
    int getYear();
    int getUcsNumber();
    bool operator== (const Student& other) const;
};


#endif //UNTITLED_STUDENT_H
