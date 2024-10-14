//
// Created by Diogo Sousa on 04/11/2023.
//

#include "Request.h"

Request::Request(std::string type_) : type(type_) {}

Request::Request(Class old, Class new_, Student student_, string uc_, string type_) :
oldClass(old), newClass(new_), student(student_), uc(uc_), type(type_) {
}

Request::Request(UC new_, Class newClass_, Student student_, std::string type_) : newUC(new_), newClass(newClass_),
student(student_), type(type_) {
    uc = newUC.getUCname();
}

Request::Request(Class oldClass_, UC old_, Student student_, std::string type_) :
oldClass(oldClass_), oldUC(old_), student(student_), type(type_) {
}

Request::Request(UC old, UC new_, Class oldClass_, Class newClass_, Student student_, std::string type_):
oldUC(old), newUC(new_), oldClass(oldClass_), newClass(newClass_), student(student_), type(type_) {}

/**
 * Adds the change log to the log file, containing the type of change and essential information for easy reference and in case changes need to be discarded
 */
void Request::addToLog() {
    ofstream log;
    log.open("../log.txt", std::ios::app);
    log << type + '-' + student.getUp() + '-';
    if (type == "ClassChange") log << uc + '-' + oldClass.getClassCode() + '-' + newClass.getClassCode() << '\n';
    if (type == "UCAdd") log << uc + '-' + newClass.getClassCode() << '\n';
    if (type == "UCRemove") log << oldUC.getUCname() + '-' + oldClass.getClassCode() << '\n';
    if (type == "UCChange") log << oldUC.getUCname() + '-' + oldClass.getClassCode() + '-'
                            + newUC.getUCname() + '-' + newClass.getClassCode() << '\n';
    log.close();
}

Class& Request::getOldClass(){
    return oldClass;
}

Class& Request::getNewClass(){
    return newClass;
}

Student& Request::getStudent(){
    return student;
}

string& Request::getUc(){
    return uc;
}

string Request::getType() {
    return type;
}

UC& Request::getOldUC() {
    return oldUC;
}

UC& Request::getNewUC() {
    return newUC;
}