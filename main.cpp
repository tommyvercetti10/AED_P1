#include <iostream>
#include "UC.h"
#include "ReadFiles.h"
#include "Interface.h"
using namespace std;

int main() {
    ReadFiles dataReader;
    Interface interface(dataReader);
    dataReader.classes_reader();
    dataReader.students_classes_reader();
    dataReader.createClasses(); // cria turmas com o q extraiu
    dataReader.loadRequests();
    interface.mainMenu();
    return 0;
}
