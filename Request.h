//
// Created by Diogo Sousa on 04/11/2023.
//

#ifndef UNTITLED_REQUEST_H
#define UNTITLED_REQUEST_H

#include <fstream>
#include "Class.h"
#include "UC.h"

class Request {
    private:
        Class oldClass = Class("1", 0);
        Class newClass = Class("1", 0);
        UC oldUC = UC("0");
        UC newUC = UC("0");
        Student student = Student("", "");
        string uc;
        string type;
    public:
        Request(string type_);
        Request(Class old, Class new_, Student student_, string uc_, string type_); // Class change
        Request(UC new_, Class newClass_, Student student_, string type_); // UC add
        Request(Class oldClass_, UC old_, Student student_, string type_); // UC remove
        Request(UC old, UC new_, Class oldClass_, Class newClass_, Student student_, string type_); // UC change
        Class& getOldClass();
        Class& getNewClass();
        UC& getOldUC();
        UC& getNewUC();
        Student& getStudent();
        string& getUc();
        string getType();
        void addToLog();

};


#endif //UNTITLED_REQUEST_H
