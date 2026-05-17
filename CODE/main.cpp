#include <iostream>
#include <vector>
#include "StudyWell.h"

int main() {
    std::vector<WellnessRecord> records;
    std::string name;
    int age, choice;

    if(!login(name, age))
    return 0;

    loadData(records, name);

    do{
        std::cout << "===================================================================================\n";
        std::cout << "                STUDYWELL: Student Wellness & Study Optimizer\n";
        std::cout << "                       SDG 3: Good Health and Well-Being\n";
        std::cout << "===================================================================================\n";
        std::cout << "User's Name: " << name << " | User's Age: " << age << std::endl;
        std::cout << "[1.] Start Wellness Check Session\n";
        std::cout << "[2.] View Study History and Summary\n";
        std::cout << "[3.] Edit Session\n";
        std::cout << "[4.] Delete Session\n";
        std::cout << "[5.] Study Plan Guides\n";
        std::cout << "[6.] About us\n";
        std::cout << "[7.] Sources / References\n";
        std::cout << "[8.] Save and Exit to the System\n";
        std::cout << "Enter Your Choice (From 1 to 8 only)   : ";
        choice = inputValidation(1, 8);
        
        switch (choice) {
            case 1:
                checkWellness(records);
                break;
            case 2:
                viewHistory(records);
                break;
            case 3:
                editSession(records);
                break;
            case 4:
                deleteSession(records);
                break;
            case 5:
                studyPlanGuide();
                break;
            case 6:
                displayAboutUs();
                break;
            case 7:
                displayReferences();
                break;
            case 8:
                saveData(records, name, age);
                break;
            default:
                std::cout<< "invalid choice. Please try again.\n";
        }
    } while (choice != 8);
    return 0;
}
