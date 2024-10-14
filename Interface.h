//
// Created by Diogo Sousa on 02/11/2023.
//

#ifndef UNTITLED_INTERFACE_H
#define UNTITLED_INTERFACE_H

#include "ReadFiles.h"

class Interface {
    private:
        ReadFiles& rf;
    public:
        Interface(ReadFiles& rf_);
        void mainMenu();
        void scheduleMenu();
        void setReadFiles(ReadFiles& rf);
        void information();
        void UCInformation();
        void LessonInformation();
        void yearInformation();
        void requestsMenu();
        string UCLauncher();
        string HourstoString(double hour);
        void printSchedule(vector<Lesson> sorted, bool showUC, bool showClass);
        void BackMainMenu();
};


#endif //UNTITLED_INTERFACE_H
