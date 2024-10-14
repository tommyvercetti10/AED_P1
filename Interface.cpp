//
// Created by Diogo Sousa on 02/11/2023.
//

#include <iostream>
#include <algorithm>
#include "Interface.h"
using namespace std;

static const char *index_to_string[] ={
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday",
};

Interface::Interface(ReadFiles& rf_) : rf(rf_) {}

void Interface::setReadFiles(ReadFiles& rf) { this->rf = rf;}

/**
 * @brief Programme menu.
 *
 * This function is the starting point for obtaining the programme's features. It calls up the function for consulting Schedules, the one for obtaining information on students, years and UC's and the Requests menu.
 *
 */
void Interface::mainMenu() {
    string uc, button;
    cout << "============╬ Menu ╬============\n";
    cout << "1. Schedules\n";
    cout << "2. Information\n";
    cout << "3. Requests\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
    int option;
    do {
        cin >> option;
        switch (option) {
            case 1:
                scheduleMenu();
                break;
            case 2:
                information();
                break;
            case 3:
                requestsMenu();
                break;
            case 4:
                cout << "Leaving the program, Thank you!\n";
                break;
            default:
                cout << "Invalid Option. Try Again.\n";
        }
    } while(option != 4);
}

// region Schedule
/**
 * @brief Menu for Schedule.
 *
 * This allows you to obtain information on years, classes and courses in order to print schedules.
 *
 */
void Interface::scheduleMenu() {
    cout << "=========╬ Schedules ╬==========\n";
    cout << "1. -- UC\n";
    cout << "2. -- Class\n";
    cout << "3. -- Student\n";
    cout << "4. Go Back\n";
    cout << "Choose an option: ";
    int option, day = 0, year;
    string uc, class_, button, studentUP, studentName;
    vector<Lesson> sorted;
    do {
        cin >> option;
        switch (option) {
            case 1:
                uc = UCLauncher();
                sorted = rf.getUC(uc).getLessonsbyDay();
                printSchedule(sorted, false, true);
                BackMainMenu();
                break;
            case 2:
                cout << "Choose a year: ";
                cin >> year;
                cout << "=========== Year " << year << " ===========\n";
                for (int i = 0; i < rf.getClasses().size(); i++) {
                    if (rf.getClasses()[i].getYear() == year) {
                        cout << rf.getClasses()[i].getClassCode() << " ";
                    }

                }
                cout << "\nWrite the name of the Class you want:  ";
                cin >> class_;
                sorted = rf.getClass(class_).getLessonsbyDay();
                printSchedule(sorted, true, false);
                year = 0;
                BackMainMenu();
                break;
            case 3:
                cout << "Write the number of the Student:  ";
                cin >> studentUP;
                for (int i = 0; i < rf.getStudents().size(); i++) {
                    if (studentUP == rf.getStudents()[i].getUp())
                    {
                        studentName = rf.getStudents()[i].getName();
                        vector<Lesson> lessons = rf.lessonsForStudent(rf.getStudents()[i]);
                        sorted = rf.sortLessonsByDay(lessons);
                    }
                }
                cout << "\n===== " << "Schedule of " + studentName + " (" + studentUP + ')' + " =====";
                printSchedule(sorted, true, true);
                BackMainMenu();
                break;
            case 4:
                mainMenu();
                break;
            default:
                cout << "Invalid Option. Try Again.\n";
        }
    } while (option != 5);
}
//endregion

//region Information
/**
 * Information menu.
 *
 * This calls up the functions for information about the UCs, years and lessons. Information about students is read and printed here.
 *
 */
void Interface::information() {
    cout << "==========╬ Informations ╬==========\n";
    cout << "1. -- About a UC\n";
    cout << "2. -- About a Lesson\n";
    cout << "3. -- About a Year\n";
    cout << "4. -- About a Student\n";
    cout << "5. Go Back\n";
    cout << "Choose an option: ";
    int option, ucsNumber;
    string studentUP, studentName;
    vector<pair<string,string>> student_classes;
    do {
        cin >> option;
        switch (option) {
            case 1:
                UCInformation();
                break;
            case 2:
                LessonInformation();
                break;
            case 3:
                yearInformation();
                break;
            case 4:
                cout << "Write the number of the Student:  ";
                cin >> studentUP;
                for (int i = 0; i < rf.getStudents().size(); i++) {
                    if (studentUP == rf.getStudents()[i].getUp())
                    {
                        studentName = rf.getStudents()[i].getName();
                        ucsNumber = rf.getStudents()[i].getUcsNumber();
                        student_classes = rf.getStudents()[i].getStudent_classes();
                    }
                }
                cout << "\n===== " << "Informations about " + studentName + " (" + studentUP + ')' + " =====\n";
                cout << "- Enrolled in " << ucsNumber << " UCs. -> ";
                for (int i = 0; i < student_classes.size(); i++) {
                    cout << student_classes[i].first;
                    if (i != student_classes.size() - 1) cout << " | ";
                }
                cout << '\n';
                BackMainMenu();
                break;
            case 5:
                mainMenu();
                break;
        }
    } while (option != 6);
}

/**
 * You can see how many hours this subject has per week and the students enrolled.
 */
void Interface::UCInformation() {
    int option;
    string uc, lesson, button;
    double duration;
    vector<pair<string, string>> students;
    cout << "==========╬ About a UC ╬==========\n";
    cout << "1. Number of hours per week\n";
    cout << "2. Students\n";
    cout << "3. Occupation\n";
    cout << "4. Go Back\n";
    cout << "Choose an option: ";
    do {
        cin >> option;
        switch (option) {
            case 1:
                uc = UCLauncher();
                lesson = rf.getUC(uc).getLessons()[0].getClasscode();
                duration = rf.getUC(uc).getLessons()[0].getDuration();
                for (int i = 1; i < rf.getUC(uc).getLessons().size(); i++) {
                    if (lesson == rf.getUC(uc).getLessons()[i].getClasscode()) {
                        duration += rf.getUC(uc).getLessons()[i].getDuration();
                    }
                }
                cout << "===== " << "Hours per week of " + uc + " =====\n";
                cout << "                 " << duration << "\n";
                BackMainMenu();
                break;
            case 2:
                uc = UCLauncher();
                for (int i = 0; i < rf.getStudents().size(); i++) { //percorrer os estudantes
                    for (int j = 0; j < rf.getStudents()[i].getStudent_classes().size(); j++) { //ver as ucs que eles estão
                        if (rf.getStudents()[i].getStudent_classes()[j].first == uc) {
                            students.push_back(make_pair(rf.getStudents()[i].getName(), rf.getStudents()[i].getUp()));
                        }
                    }
                }
                sort(students.begin(), students.end());
                cout << "===== " << "Students of " + uc + " =====\n";
                for (int x= 0; x < students.size(); x++) {
                    cout << students[x].second + " - " + students[x].first << '\n';
                }
                cout << "===========================\n";
                cout << "This UC has " << students.size() << " students.\n";
                BackMainMenu();
                break;
            case 3:
                uc = UCLauncher();
                students.clear();
                for (int i = 0; i < rf.getStudents().size(); i++) { //percorrer os estudantes
                    for (int j = 0; j < rf.getStudents()[i].getStudent_classes().size(); j++) { //ver as ucs que eles estão
                        if (rf.getStudents()[i].getStudent_classes()[j].first == uc) {
                            students.push_back(make_pair(rf.getStudents()[i].getName(), rf.getStudents()[i].getUp()));
                        }
                    }
                }
                cout << "\n===== " << "Occupation of " + uc + " =====\n";
                cout << "             " << students.size() << " / 400\n";
                BackMainMenu();
            case 4:
                information();
                break;
            case 5:
                break;
        }
    }while (option != 5);
}

/**
 * Allows you to see the students in a lesson
 */
void Interface::LessonInformation(){
    int option, ucnumber, lessonnumber;
    string uc, lesson;
    cout << "1. Lesson's Students \n";
    //cout << "2" ....
    cout << "Choose an option: ";
    do{
        cin >> option;
        switch (option) {
            case 1:
                //UCLauncher();
                for (int i = 0; i < rf.getUcs().size(); i++) {
                    cout << rf.getUcs()[i].getUCname() << " ";
                }
                cout << "\nWrite the name of the UC: ";
                cin >> uc;
                for (int j = 0; j < rf.getUC(uc).getLessons().size(); j++) {
                    cout << j+1 << ". " << rf.getUC(uc).getLessons()[j].getDay() << ":" <<rf.getUC(uc).getLessons()[j].getClasscode() << "-" << rf.getUC(uc).getLessons()[j].getType()<< "   ";
                }
                cout << "\nChoose a Lesson: ";
                cin >> lessonnumber;
                cout << "\n===== " << "Lesson Informations" << " =====";
                cout << "\nThis Lesson has " << rf.getUC(uc).getLessons()[lessonnumber-1].getStudents().size() << " students.\n";
                for(int k=0; k < rf.getUC(uc).getLessons()[lessonnumber-1].getStudents().size(); k++){
                    cout << rf.getUC(uc).getLessons()[lessonnumber-1].getStudents()[k].getUp() << " - " << rf.getUcs()[ucnumber-1].getLessons()[lessonnumber-1].getStudents()[k].getName() << "\n";
                }
                cout << "\n1. Go Back" << '\n' << "2. Exit";
                cout << "\nChoose an option: ";
                cin >> option;
            case 2:
                break;
            case 4:
                break;
        }
    }while(option != 5);
}

/**
 * Allows you to see the students of a year
 */
void Interface::yearInformation() {
    int option, year;
    string uc, lesson;
    string button;
    cout << "1. Year's Students \n";
    cout << "Choose an option: ";
    vector<pair<string, string>> students;
    do{
        cin >> option;
        switch (option) {
            case 1:
                cout << "\nWrite the Year (number): ";
                cin >> year;
                for (int i = 0; i < rf.getStudents().size(); i++) {
                    if (rf.getStudents()[i].getYear() == year)
                        students.push_back(make_pair(rf.getStudents()[i].getName(), rf.getStudents()[i].getUp()));
                }
                sort(students.begin(), students.end());
                cout << "===== " << "Students of Year " << year << " =====\n";
                for(int k=0; k < students.size(); k++){
                    cout << students[k].first << " - " << students[k].second << "\n";
                }
                cout << "===========================\n";
                cout << "This year has " << students.size() << " students.\n";
                cout << "\nPress E to exit:  ";
                cin >> button;
                if (button == "E") {
                    mainMenu();
                }
                break;
        }
    }while(option != 5);
}
//endregion

//region Requests
/**
 * @brief Menu for requests.
 *
 * This function allows students to change their classes and UCs, as well as enter a UC if they don't exceed the maximum limit. A record of all changes is also kept here, so that you can go back on your decision.
 *
 */
void Interface::requestsMenu() {
    cout << "===========╬ Requests ╬===========\n";
    cout << "1. -- Class Change\n";
    cout << "2. -- UC Change\n";
    cout << "3. -- UC Add\n";
    cout << "4. -- UC Remove\n";
    cout << "5. Log Status\n";
    cout << "6. Go Back\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
    int option, ucsNumber, ucNumber, classNumber, prevUcNumber;
    string studentUP, studentName, uc, class_, studentYear, prevUC;
    vector<pair<string,string>> student_classes;
    vector<Lesson> ucLessons;
    vector<UC> UCchances;
    vector<Class> classes;
    Student student("", "");
    Request request("");
    do {
        cin >> option;
        switch (option) {
            case 1:
                cout << "Write the number of the Student:  ";
                cin >> studentUP;
                for (int i = 0; i < rf.getStudents().size(); i++) {
                    if (studentUP == rf.getStudents()[i].getUp())
                    {
                        studentName = rf.getStudents()[i].getName();
                        ucsNumber = rf.getStudents()[i].getUcsNumber();
                        student_classes = rf.getStudents()[i].getStudent_classes();
                        student = rf.getStudents()[i];
                    }
                }
                cout << "\n===== " << "Class change for " + studentName + " (" + studentUP + ')' + " =====\n";
                cout << "- Enrolled in " << ucsNumber << " UCs. -> ";
                for (int i = 0; i < student_classes.size(); i++) {
                    cout << i+1 << ". " << student_classes[i].first;
                    if (i != student_classes.size() - 1) cout << " | ";
                }
                cout << "\nChoose the UC:  ";
                cin >> ucNumber;
                uc = student_classes[ucNumber - 1].first;
                for (int i = 0; i < student_classes.size(); i++) {
                    if (student_classes[i].first == uc) class_ = student_classes[i].second;
                }
                cout << "\n-- Currently -> Class: " << class_ + '\n';
                classes = rf.getClassChances(uc, class_, student);
                if (!classes.empty()) {
                    cout << "-- Possible Changes: \n";
                    for (int i = 0; i < classes.size(); i++) {
                        cout << i+1 << ". " << "Class: " << classes[i].getClassCode() << " - Students: " << classes[i].getLessons()[0].getStudents().size() << '\n';
                    }
                    cout << "\nChoose the Class:  ";
                    cin >> classNumber;
                    rf.changeClass(rf.getClass(class_), classes[classNumber - 1], uc, student, true);
                    cout << "\n===== CHANGE SUCCESSFUL =====\n";
                    cout << "The student " + studentName + " (" + studentUP + ") "
                            + "changed the class of the UC " + uc + " from " + rf.getClass(class_) .getClassCode() +
                            " to " + classes[classNumber - 1].getClassCode() + ".";
                }
                else cout << "- It was not possible to find a compatible change. Try other UC!\n";
                BackMainMenu();
                break;
            case 2:
                cout << "Write the number of the Student: ";
                cin >> studentUP;
                for (int i = 0; i < rf.getStudents().size(); i++) {
                    if (studentUP == rf.getStudents()[i].getUp()) {
                        studentName = rf.getStudents()[i].getName();
                        ucsNumber = rf.getStudents()[i].getUcsNumber();
                        student_classes = rf.getStudents()[i].getStudent_classes();
                        student = rf.getStudents()[i];
                    }
                }
                cout << "\n===== " << "UC change for " + studentName + " (" + studentUP + ")" + " =====\n";
                cout << "- Enrolled in " << ucsNumber << " UCs. -> ";
                for (int i = 0; i < student_classes.size(); i++) {
                    cout << i + 1 << ". " << student_classes[i].first;
                    if (i != student_classes.size() - 1) cout << " | ";
                }
                cout << "\n\nChoose the UC that you want to change: ";
                cin >> prevUcNumber;
                prevUC = student_classes[prevUcNumber - 1].first;
                UCchances = rf.getUcs();
                for (int i = 0; i < UCchances.size(); i++) {
                    for (int j = 0; j < student_classes.size(); j++) {
                        if (UCchances[i].getUCname() == student_classes[j].first) {
                            UCchances.erase(UCchances.begin() + i);
                        }
                        //cout << student_classes[j].first << '\n';
                    }
                }
                cout << "\n- Possible UCs to change: \n";
                for (int x= 0; x < UCchances.size(); x++) {
                    cout << x+1 << ". " << UCchances[x].getUCname();
                    if (x != UCchances.size() - 1 && x!= UCchances.size() / 2) cout << " | ";
                    if (x == UCchances.size() / 2) cout << '\n';
                }
                cout << "\n\nChoose the UC:  ";
                cin >> ucNumber;
                uc = UCchances[ucNumber - 1].getUCname();
                for (int i = 0; i < student_classes.size(); i++) {
                    if (student_classes[i].first == prevUC) class_ = student_classes[i].second;
                }
                classes = rf.getClassChances(prevUC, class_, uc, student);
                if (!classes.empty()) {
                    cout << "-- Possible Classes: \n";
                    for (int i = 0; i < classes.size(); i++) {
                        cout << i+1 << ". " << "Class: " << classes[i].getClassCode() << " - Students: " << classes[i].getLessons()[0].getStudents().size() << '\n';
                    }
                    cout << "\nChoose the Class:  ";
                    cin >> classNumber;
                    rf.changeUC(rf.getUC(prevUC), rf.getClass(class_), rf.getUC(uc), classes[classNumber - 1], student, true);
                    cout << "\n===== CHANGE SUCCESSFUL =====\n";
                    cout << "The student " + studentName + " (" + studentUP + ") "
                            + "changed the UC from " + prevUC + " (" + class_ + ") " +
                            "to " + uc + " (" + classes[classNumber - 1].getClassCode() + ")" + ".";
                }
                else cout << "- It was not possible to find a compatible change. Try other UC!\n";
                BackMainMenu();
                break;
            case 3:
                cout << "Write the number of the Student:  ";
                cin >> studentUP;
                for (int i = 0; i < rf.getStudents().size(); i++) {
                    if (studentUP == rf.getStudents()[i].getUp()) {
                        studentName = rf.getStudents()[i].getName();
                        ucsNumber = rf.getStudents()[i].getUcsNumber();
                        student_classes = rf.getStudents()[i].getStudent_classes();
                        student = rf.getStudents()[i];
                        studentYear = rf.getStudents()[i].getYear();
                    }
                }
                cout << "\n===== " << "UC Add for " + studentName + " (" + studentUP + ')' + " =====\n";
                cout << "- Enrolled in " << ucsNumber << " UCs. -> ";
                for (int i = 0; i < student_classes.size(); i++) {
                    cout << i+1 << ". " << student_classes[i].first;
                    if (i != student_classes.size() - 1) cout << " | ";
                }
                if (ucsNumber == 7) {
                    cout << "\n- The student cannot enroll in more UC's (reached the maximum of 7 UC's)\n";
                    BackMainMenu();
                    break;
                }
                else {
                    UCchances = rf.getUcs();
                    for (int i = 0; i < UCchances.size(); i++) {
                        for (int j = 0; j < student_classes.size(); j++) {
                            if (UCchances[i].getUCname() == student_classes[j].first) {
                                UCchances.erase(UCchances.begin() + i);
                            }
                            //cout << student_classes[j].first << '\n';
                        }
                    }
                    cout << "\n- Possible UCs to Add: \n";
                    for (int x= 0; x < UCchances.size(); x++) {
                        cout << x+1 << ". " << UCchances[x].getUCname();
                        if (x != UCchances.size() - 1 && x!= UCchances.size() / 2) cout << " | ";
                        if (x == UCchances.size() / 2) cout << '\n';
                    }
                    cout << "\n\nChoose the UC:  ";
                    cin >> ucNumber;
                    uc = UCchances[ucNumber - 1].getUCname();
                    classes = rf.getClassChances(uc, "", student, true);
                    if (!classes.empty()) {
                        cout << "-- Possible Classes: \n";
                        for (int i = 0; i < classes.size(); i++) {
                            cout << i+1 << ". " << "Class: " << classes[i].getClassCode() << " - Students: " << classes[i].getLessons()[0].getStudents().size() << '\n';
                        }
                        cout << "\nChoose the Class:  ";
                        cin >> classNumber;
                        rf.addUC(uc, classes[classNumber - 1], student, true);
                        cout << "\n===== ADDITION SUCCESSFUL =====\n";
                        cout << "The student " + studentName + " (" + studentUP + ") "
                                + "was registered in the UC " + uc +
                                " in the class " + classes[classNumber - 1].getClassCode() + ".";
                    }
                    else cout << "- It was not possible to find a compatible change. Try other UC!\n";
                    BackMainMenu();
                }
            case 4:
                cout << "Write the number of the Student:  ";
                cin >> studentUP;
                for (int i = 0; i < rf.getStudents().size(); i++) {
                    if (studentUP == rf.getStudents()[i].getUp()) {
                        studentName = rf.getStudents()[i].getName();
                        ucsNumber = rf.getStudents()[i].getUcsNumber();
                        student_classes = rf.getStudents()[i].getStudent_classes();
                        student = rf.getStudents()[i];
                        studentYear = rf.getStudents()[i].getYear();
                    }
                }
                cout << "\n===== " << "UC Remove for " + studentName + " (" + studentUP + ')' + " =====\n";
                cout << "- Enrolled in " << ucsNumber << " UCs. -> ";
                if (ucsNumber == 0) cout << "- Impossible to remove more UCs. ";
                else {
                    for (int i = 0; i < student_classes.size(); i++) {
                        cout << i+1 << ". " << student_classes[i].first;
                        if (i != student_classes.size() - 1) cout << " | ";
                    }
                    cout << "\n\nChoose the UC to remove:  ";
                    cin >> ucNumber;
                    uc = student_classes[ucNumber-1].first;
                    class_ = student_classes[ucNumber-1].second;
                    rf.removeUC(rf.getUC(uc), rf.getClass(class_), student, true);
                    cout << "\n===== REMOVE SUCCESSFUL =====\n";
                    cout << "The student " + studentName + " (" + studentUP + ") "
                            + "was removed in the UC " + uc +
                            " in the class " + class_ + ".";
                    BackMainMenu();
                    break;
                }
            case 5:
                cout << "\n=============================== " << "Log List" << " ===============================\n";
                if (rf.getRequests().size()==0){
                    cout << "\nYou haven't done any requests yet.";
                    BackMainMenu();
                }
                cout << "      Type        " << " Student        ";
                cout <<"     UC                  " << " Class                  \n";
                for(int i=0; i< rf.getRequests().size(); i++){
                    if (rf.getRequests()[i].getType() == "UCChange") {
                        cout << i+1 << ". " << rf.getRequests()[i].getType() << "       " << rf.getRequests()[i].getStudent().getUp();
                        cout << "    " << rf.getRequests()[i].getOldUC().getUCname()
                             << " -> " << rf.getRequests()[i].getNewUC().getUCname();
                        cout << "   " << rf.getRequests()[i].getOldClass().getClassCode()
                             << " -> " << rf.getRequests()[i].getNewClass().getClassCode();
                    }
                    else if (rf.getRequests()[i].getType() == "ClassChange") {
                        cout << i+1 << ". " << rf.getRequests()[i].getType() << "    " << rf.getRequests()[i].getStudent().getUp();
                        cout << "         " << rf.getRequests()[i].getUc();
                        cout << "          " << rf.getRequests()[i].getOldClass().getClassCode()
                             << " -> " << rf.getRequests()[i].getNewClass().getClassCode();
                    }
                    else if (rf.getRequests()[i].getType() == "UCAdd") {
                        cout << i+1 << ". " << rf.getRequests()[i].getType() << "          " << rf.getRequests()[i].getStudent().getUp();
                        cout << "         " << rf.getRequests()[i].getUc();
                        cout << "               " << rf.getRequests()[i].getNewClass().getClassCode();
                    }
                    else if (rf.getRequests()[i].getType() == "UCRemove") {
                        cout << i+1 << ". " << rf.getRequests()[i].getType() << "       " << rf.getRequests()[i].getStudent().getUp();
                        cout << "         " << rf.getRequests()[i].getOldUC().getUCname();
                        cout << "               " << rf.getRequests()[i].getOldClass().getClassCode();
                    }
                    cout << '\n';
                }
                cout << "\n1. Undo a Request\n2. Go Back\nChoose an Option: ";
                cin >> option;
                if(option==1){
                    if (rf.getRequests().size() == 0){
                        cout << "\nThere are no requests to undo.";
                        BackMainMenu();
                    }
                    cout << "Choose the Request to undo: ";
                    cin >> option;
                    request = rf.getRequests()[option-1];
                    if (request.getType() == "ClassChange")
                        rf.changeClass(request.getNewClass(), request.getOldClass(), request.getUc(), request.getStudent(), true);
                    else if (request.getType() == "UCChange")
                        rf.changeUC(request.getNewUC(), request.getNewClass(), request.getOldUC(), request.getOldClass(), request.getStudent(), true);
                    else if (request.getType() == "UCAdd")
                        rf.removeUC(request.getNewUC(), request.getNewClass(), request.getStudent(), true);
                    else if (request.getType() == "UCRemove")
                        rf.addUC(request.getOldUC(), request.getOldClass(), request.getStudent(), true);
                    cout << "Request done. Moved " << rf.getRequests()[option-1].getStudent().getUp() << " in " << rf.getRequests()[option-1].getUc()
                         << " from " << rf.getRequests()[option-1].getNewClass().getClassCode() << " to " << rf.getRequests()[option-1].getOldClass().getClassCode() << " sucessfully!";
                    BackMainMenu();
                }
                else if(option == 2){
                    requestsMenu();
                }
                break;
            case 6:
                mainMenu();
                break;
            case 7:
                cout << "Leaving the program, Thank you!\n";
                break;
            default:
                cout << "Invalid Option. Try Again.\n";
        }
    } while (option != 7);
}


//endregion
/**
 * This function gives a printout of all the UCs and allows the user to choose them.
 *
 * @return
 */
string Interface::UCLauncher() {
    int uc;
    for (int i = 0; i < rf.getUcs().size() /2; i++) {
            cout << i+1 << ". " << rf.getUcs()[i].getUCname() << "  ";
    }
    cout << "\n";
    for (int j = rf.getUcs().size() /2; j< rf.getUcs().size(); j++) {
            cout << j+1 << ". " << rf.getUcs()[j].getUCname() << "  ";
    }
    cout << "\nChoose a UC: ";
    cin >> uc;
    return rf.getUcs()[uc-1].getUCname();
}

/**
 * @brief Function that prints Schedules.
 * This function receives information about lessons and organises it in chronological order so that it is easy to read and interpret
 * @param sorted Lessons
 * @param showUC
 * @param showClass
 */
void Interface::printSchedule(vector<Lesson> sorted, bool showUC, bool showClass) {
    int day = 0;
    string spaces(25 - strlen(index_to_string[day]), ' ');
    while (day != 7) {
        cout << '\n' << "================ " << index_to_string[day] << " ================" << '\n';
        if (showUC) cout << " UC             ";
        if (showClass) cout << " Class          ";
        cout <<" Time             ";
        //cout <<" Start Time       ";
        cout <<" Type     \n";
        for (int i = 0; i < sorted.size(); i++) {
            if (sorted[i].getDay_() == day) {
                if (showUC) {
                    string spaces(15 - sorted[i].getUcCode().size(), ' ');
                    cout << " " << sorted[i].getUcCode() << spaces;
                }
                if (showClass) {
                    string spaces( 15- sorted[i].getClasscode().size(), ' ');
                    cout << " " << sorted[i].getClasscode() << spaces;
                }
                string EndHour = HourstoString(sorted[i].getStartHour() + sorted[i].getDuration());
                string spaces( 16- HourstoString(sorted[i].getStartHour()).size() - EndHour.size(), ' ');
                cout << " " << HourstoString(sorted[i].getStartHour()) << "-" << EndHour << spaces;
                cout << " " << sorted[i].getType() <<'\n';
            }
        }
        day++;
    }
}

string Interface::HourstoString(double hour){
    int IntHour = static_cast<int>(hour);
    double DecimalMinutes = (hour - IntHour) * 60;
    int IntMin = static_cast<int>(DecimalMinutes);
    string StrHour = to_string(IntHour) + ":" + to_string(IntMin);
    if (IntMin == 0) StrHour += '0';
    return StrHour;
}

void Interface::BackMainMenu() {
    string button;
    cout << "\nPress E to return to the main menu:  ";
    cin >> button;
    if (button == "E") mainMenu();
}