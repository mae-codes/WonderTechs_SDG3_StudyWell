#include <iostream>
#include <fstream> //for file handling
#include <iomanip>//for formatting
#include <limits> //numeric input and input handling (specifically ginamit toh for invalid inputs)
#include <cctype> //for character checking 
#include <sstream>//for string stream para ma check yung each line ng string
#include "StudyWell.h"

//for validation of input ng users' name if may characters na hindi letters
// this code is with the help / guide of gemini
bool nameValidation(const std::string& name) {
    bool hasLetter = false;

    for (char c: name) {
        if(!std::isalpha(c) && c !=' ') {
            return false;
        }
        if (std::isalpha(c)) {
            hasLetter = true;
        }
    }
    return hasLetter;
}

//for validation of input ng users in every int inputs (age, menu choices, answers, etc..). Checking if may character/letter yung every int inputs
// this code is with the help / guide of gemini
int inputValidation(int min, int max) {
    int value;

    while(true) {
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            std::cout << "| Invalid input. Input must be numbers only.\n";
            std::cout << "| Please try again: ";
            continue;
        }
        if(value < min || value > max) {
            std::cout << "| Input must be from " << min << " to " << max << ".\n";
            std::cout << "| Please try again: ";
            continue;
        }
        
        if(std::cin.peek() != '\n'){
            std::cin.ignore(1000, '\n');

            std::cout << "| Invalid input. Characters are not allowed.\n";
            std::cout << "| Please try again: ";
            continue;
        }
        std::cin.ignore(1000, '\n');
        return value;
    }
}

//for logging in of every users with boolean conditions para ma support yung users' input validations
bool login(std::string &name, int &age) {
    std::cout << "===================================================================================\n";
    std::cout << "                          --- WELCOME TO THE SYSTEM ---                            \n";
    std::cout << "===================================================================================\n";
    while (true) {

        std::cout << "| Enter Your Name  : ";
        std::getline(std::cin, name);

        if (!nameValidation(name)) {

            std::cout << "| Invalid name. Alphabets or letter only.\n";
            continue;
        }

        std::cout << "| Enter Your Age   : ";
        age = inputValidation(18, 28);

        break;
    }

    std::cout << "| Successfully Logged In!\n";

    return true;
}

//for file handling, para i-read ng loadData yung "data.txt" file para maibalik yung mga na save na records once na nag save and exit ka.
// this code is with the help / guide of gemini
void loadData(std::vector<WellnessRecord>& records, const std::string& currentUser) {
    records.clear();
    std::ifstream file("data.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, '|');

        if (name == "EDITED_MARKER") {
            int targetIndex, h, w, s;
            std::string plan;
            ss >> targetIndex; ss.ignore();
            ss >> h; ss.ignore();
            ss >> w; ss.ignore();
            ss >> s; ss.ignore();
            std::getline(ss, plan);

            if (targetIndex - 1 < records.size()) {
                records[targetIndex - 1].setData(h, w, s, plan);
            }
        }
        else if (name == "DELETED_MARKER") {
            int targetIndex;
            ss >> targetIndex; 
            
            if (targetIndex - 1 < records.size()) {
                records.erase(records.begin() + (targetIndex - 1));
            }
        }     
        else {
            int age, h, w, s;
            std::string plan;
            ss >> age; ss.ignore();
            ss >> h; ss.ignore();
            ss >> w; ss.ignore();
            ss >> s; ss.ignore();
            std::getline(ss, plan);

            if (name == currentUser) {
                records.push_back(WellnessRecord(h, w, s, plan));
            }
        }
    }
    file.close();
}
//this is for transferring naman lahat ng naka store na records sa vector papunta "data.txt" file
// this code is with the help / guide of gemini
void saveData(std::vector<WellnessRecord>& records, const std::string& name, int age) {
    int existingRecordsCount = 0;
    std::ifstream fileCheck("data.txt");
    if (fileCheck.is_open()) {
        std::string line;
        while (std::getline(fileCheck, line)) {
            std::stringstream ss(line);
            std::string savedName;
            std::getline(ss, savedName, '|');
            if (savedName == name) {
                existingRecordsCount++;
            }
        }
        fileCheck.close();
    }
    if (records.size() <= existingRecordsCount) {
        std::cout << "| No new sessions to save.\n";
        return;
    }

    std::ofstream file("data.txt", std::ios::app);
    if (!file.is_open()) {
        std::cout << "| Error saving file.\n";
        return;
    }
    for (int i = existingRecordsCount; i < records.size(); i++) {
        file << name << "|"  << age << "|"  << records[i].getStudyHours() << "|"  << records[i].getWellbeing() << "|" << records[i].getStress() << "|"  << records[i].getStudyPlan() << "\n";
    }

    file.close();
    std::cout << "| Data saved successfully.\n";
}
//for the wellness check session where lahat ng records is dito nanggagaling (Overall wellbeing scores (JL+AE+TM), Perceived stress scores, Study hours)
//records are based on their results
void checkWellness(std::vector<WellnessRecord>& records) {
    int answers[10], total = 0;

    std::cout << "-----------------------------------------------------------------------------------\n";
    std::cout << "                               DISCLAIMER!\n";
    std::cout << "             This System is just a support for wellness tracking. \n";
    std::cout << "            It is NOT a substitute for professional medical advice.\n";
    std::cout << "===================================================================================\n";
    std::cout << "                               WELLNESS CHECKER\n";
    std::cout << "===================================================================================\n";
    std::cout << "Read each of the statements carefully and rate yourself\n";
    std::cout << "using the scale below:\n";
    std::cout << "\n1 = Strongly Disagree | 2 = Disagree | 3 = Agree | 4 = Strongly Agree\n\n";
    std::cout << "===================================================================================\n";

    std::string questions[10] = {
        "1. I looked forward to studying.",
        "2. I enjoyed learning new topics.",
        "3. I was able to focus even on difficult subjects.",
        "4. I felt confident in completing my schoolwork.",
        "5. I was able to keep up with my study tasks.",
        "6. I managed my study time effectively.",
        "7. I avoided procrastinating and distractions.",
        "8. I felt overwhelmed by schoolwork.",
        "9. I felt anxious about deadlines or exams.",
        "10. I felt mentally exhausted after studying."
    };

    for (int i = 0; i < 10; i++) {

            std::cout << questions[i] << "\nYour Answer (Choose From 1 to 4 only)  | (Input 0 to exit): ";
            answers[i] = inputValidation(0, 4);

            if (answers[i] == 0) {
                std::cout << "| Wellness Check Cancelled\n";
            std::cout << "----------------------------------------------------------------------------------\n";   
                return;
            }
        
    }

    int JL = answers[0] + answers[1];
    int AE = answers[2] + answers[3] + answers[4];
    int TM = answers[5] + answers[6];
    int PS = answers[7] + answers[8] + answers[9];

    total = JL + AE + TM;

    std::cout << "\n=========================== TODAY'S WELLNESS RESULTS ===========================\n";
    std::cout << "| Joy of Learning Score     : " << JL << std::endl;
    std::cout << "| Time Management Score     : " << TM << std::endl;
    std::cout << "| Academic Efficacy Score   : " << AE << std::endl;
    std::cout << "| Overall Wellbeing Score   : " << total << std::endl;
    std::cout << "| Perceived Stress Score    : " << PS << std::endl;

    
    if (total >= 10 && total <= 13) {
        std::cout << "===================================================================================\n";
        std::cout << "IMPROVE - Lower well-being is linked to reduced motivation and engagement.\n";
        std::cout << "Start with simple study routines and minimize distractions to improve!.\n";
        std::cout << ".  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .\n";
    }
    else if (total >= 14 && total <= 18) {
        std::cout << "===================================================================================\n";
        std::cout << "DEVELOP - Build consistency. Structured routines and setting small goals\n";
		std::cout << "can improve your focus and stability.\n";
        std::cout << ".  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .\n";
    }
    else if (total >= 19 && total <= 23) {
        std::cout << "===================================================================================\n";
        std::cout << "STRENGTHEN - Maintain momentum. Continue effective study habits and\n";
		std::cout << "active learning strategies. Keep up the good work!\n";
        std::cout << ".  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .\n";
    }
    else if (total >= 24 && total <= 28) {
        std::cout << "===================================================================================\n";
        std::cout << "MAINTAIN - Keep it up! Maintain your habits while also challenging yourself\n";
		std::cout << "with deeper learning and leadership roles.\n";
        std::cout << ".  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .\n";
    }
    else {
        std::cout << "===================================================================================\n";
        std::cout << "IMPROVE - Lower well-being is linked to reduced motivation and engagement.\n";
        std::cout << "Start with simple study routines and minimize distractions to improve!.\n";
        std::cout << ".  .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .\n";

    }


    if (PS >= 3 && PS <= 5) {
        std::cout << "Balanced Stress - Manageable stress can enhance alertness,\n";
		std::cout << "motivation, and performance. You're doing great! d^-^b\n";
        std::cout << "===================================================================================\n";
    }
    else if (PS >= 6 && PS <= 8) {
        std::cout << "Moderate Stress - May affect focus and memory. Improve time management, take \n";
		std::cout << "breaks, and practice relaxation techniques to reduce stress! d>_<b\n";
        std::cout << "===================================================================================\n";
    }
    else if (PS >= 9 && PS <= 12) {
        std::cout << "High Stress - Risk of burnout and low performance. Let's take one step at a time.\n";
		std::cout << "Rest, seek support, and consider reducing workload! dToTb\n";
        std::cout << "===================================================================================\n";
    }

    int hours;
    do{
        std::cout << "| Input Study Hours (From 1 to 8 only) | (Input 0 to exit): ";
        hours = inputValidation(0, 8);

        if (hours == 0) return;

        if (hours < 1 || hours > 8) {
            std::cout << "| Invalid hours. Please try again.\n";
        }
    } while (hours < 1 || hours > 8);

    std::string plan = studyPlanProvider(total, PS);
    records.push_back(WellnessRecord(hours, total, PS, plan));
}
//for viewing of their session study history and summary of results
void viewHistory(const std::vector<WellnessRecord>& records) {
    if (records.empty()) {
        std::cout << "| No Study History yet. Please proceed to Wellness Check Session.\n";
        return;
    }

    double totalTime = 0, totalWell = 0, totalStress = 0;

    std::cout << "============================ STUDY HISTORY AND SUMMARY ============================\n";

    for (int i = 0; i < records.size(); i++) {
        int stress = records[i].getStress();
        std::string stressLabel;

        if (stress >= 9) {
            stressLabel = "High Stress";
        }
        else if (stress >= 6) {
            stressLabel = "Moderate Stress";
        }
        else {
            stressLabel = "Balanced Stress";
        }
        
        std::cout << "| Session " << i + 1 << "\n";
        std::cout << "| Study Hours   : " << records[i].getStudyHours() << " hour(s)\n";
        std::cout << "| Wellbeing     : " << records[i].getWellbeing() << "\n";
        std::cout << "| Stress Score  : " << stress << " (" << stressLabel << ")\n";
        std::cout << "| Study Plan    : " << records[i].getStudyPlan() << "\n";
        std::cout << "------------------------------------------------------------------------------\n";

        totalTime += records[i].getStudyHours();
        totalWell += records[i].getWellbeing();
        totalStress += stress;

    }  
    std::cout << "\n=============================== SUMMARY OF RESULTS ===============================\n";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "| Average Study Hours: " << totalTime / records.size() << " hour(s)\n";
    std::cout << "| Average Well-Being : " << totalWell / records.size() << std::endl;
    std::cout << "| Average Stress     : " << totalStress / records.size() << std::endl;
}

//for editing the sessions / records where they 3 choices to edit if 1. wellness and stress(Wellness check session again without study hour)
//2. study hours lang 3. All (Wellness check session again and with study hours)
void editSession(std::vector<WellnessRecord>& records) {
    int index;

    if (records.empty()) {
        std::cout << "| No sessions available.\n";
        return;
    }

    viewHistory(records);
    std::cout << "=============================== SESSION EDITOR ===============================\n";
    std::cout << "| Input which session you want to edit (Input 0 to exit): ";
    index = inputValidation(0, records.size());

    if (index == 0) return;

    std::cout << "\n| Choose what you want to edit: \n";
    std::cout << "| [1] Wellness and Stress\n";
    std::cout << "| [2] Study Hours\n";
    std::cout << "| [3] All\n";
    std::cout << "| [0] Exit\n";
    std::cout << "| Input choice: ";
    int choice = inputValidation(0, 3);

    if (choice == 0) return;

    int h = records[index - 1].getStudyHours();
    int w = records[index - 1].getWellbeing();
    int s = records[index - 1].getStress();
    std::string p = records[index - 1].getStudyPlan();

    // Kapag pinili ang Choice 1 (Wellness/Stress) o Choice 3 (All), dadaan sa re-checker questions
    if (choice == 1 || choice == 3) {
        int answers[10], total = 0;

        std::cout << "-----------------------------------------------------------------------------------\n";
        std::cout << "                               DISCLAIMER!\n";
        std::cout << "             This System is just a support for wellness tracking. \n";
        std::cout << "            It is NOT a substitute for professional medical advice.\n";
        std::cout << "===================================================================================\n";
        std::cout << "                               WELLNESS RE-CHECKER\n";
        std::cout << "===================================================================================\n";
        std::cout << "Read each of the statements carefully and rate yourself\n";
        std::cout << "using the scale below:\n";
        std::cout << "\n1 = Strongly Disagree | 2 = Disagree | 3 = Agree | 4 = Strongly Agree\n\n";
        std::cout << "===================================================================================\n";

        std::string questions[10] = {
            "1. I looked forward to studying.",
            "2. I enjoyed learning new topics.",
            "3. I was able to focus even on difficult subjects.",
            "4. I felt confident in completing my schoolwork.",
            "5. I was able to keep up with my study tasks.",
            "6. I managed my study time effectively.",
            "7. I avoided procrastinating and distractions.",
            "8. I felt overwhelmed by schoolwork.",
            "9. I felt anxious about deadlines or exams.",
            "10. I felt mentally exhausted after studying."
        };

        for (int i = 0; i < 10; i++) {
            std::cout << questions[i] << "\nYour Answer (Choose From 1 to 4 only)  | (Input 0 to exit): ";
            answers[i] = inputValidation(0, 4);

            if (answers[i] == 0) {
                std::cout << "| Wellness Check Cancelled\n";
                std::cout << "----------------------------------------------------------------------------------\n";   
                return;
            }
        }

        int JL = answers[0] + answers[1];
        int AE = answers[2] + answers[3] + answers[4];
        int TM = answers[5] + answers[6];
        int PS = answers[7] + answers[8] + answers[9];

        total = JL + AE + TM;
        w = total;
        s = PS;
        p = studyPlanProvider(w, s);
    }
    
    // Kapag pinili ang Choice 2 (Study Hours lang), tatanungin ang bagong study hours
    if (choice == 2) {
        std::cout << "| New Study Hours (1-8): ";
        h = inputValidation(1, 8);
        p = studyPlanProvider(w, s);
    }
    
    // Kapag Choice 3 (All), hihingi rin ng bagong Study Hours pagkatapos ng questionnaire
    if (choice == 3) {
        std::cout << "| Input Study Hours (From 1 to 8 only) | (Input 0 to exit): ";
        h = inputValidation(0, 8);
        if (h == 0) return;
        p = studyPlanProvider(w, s);
    }

    // I-update ang records gamit ang mga bagong data sa memory list natin
    records[index - 1].setData(h, w, s, p);

    // FIX: Isusulat na ang EDITED_MARKER log sa data.txt para sa kahit anong choice
    std::ofstream file("data.txt", std::ios::app);
    if (file.is_open()) {
        file << "EDITED_MARKER|" << index << "|" << h << "|" << w << "|" << s << "|" << p << "\n";
        file.close();
    }

    std::cout << "| Session Updated Successfully.\n";
}
//for deleting sessions naman toh where they will just choose which session yung gsuto nila i-delete  
void deleteSession(std::vector<WellnessRecord>& records) {
    int index;

    if (records.empty()) {
        std::cout << "| No sessions available.\n";
        return;
    }

    viewHistory(records);
    std::cout << "================================= SESSION DELETE ==================================\n";
    std::cout << "| Input which day you want to delete | (Input 0 to exit): ";
    index = inputValidation(0, records.size());

    if (index == 0) return;

    std::ofstream file("data.txt", std::ios::app);
    if (file.is_open()) {
        file << "DELETED_MARKER|" << index << "|0|0|0|Deleted\n";
        file.close();
    }

    records.erase(records.begin() + index - 1);
    std::cout << "| Session is deleted successfully.\n";
}
//for viewing / displaying lang ng study guide so that users can properly guided in the provided study plan that is based on their check wellness results
void studyPlanGuide() {
    std::cout << "=============================== STUDY PLAN GUIDES ==================================\n";
    std::cout << "| NOTE: Follow these guides based on the provided Study Plan for you. Thank you.    \n";
    std::cout << "....................................................................................\n";
    std::cout << "| Plan for 1 to 2 hours(Light Plan): \n";
    std::cout << "| FOCUS: Perfect for baseline daily maintenance, quick reviews, or light homework.  \n";
    std::cout << "| STRATEGY: Use a single 50-minute study block followed by a 10-minute break.\n";
    std::cout << "....................................................................................\n";
    std::cout << "| Plan for up to 4 hours(Moderate Plan): \n";
    std::cout << "| FOCUS: Great for regular exam preparation and mastering steady course concepts.   \n";
    std::cout << "| STRATEGY: Split this into two separate 2-hour blocks (e.g., one in the afternoon, \n";
    std::cout << "| one in the evening). Take a 15-minute walk or screen-free break between blocks to \n";
    std::cout << "| refresh your eyes.\n";
    std::cout << "....................................................................................\n";
    std::cout << "| Plan for 4 to 6 hours(Optimal Plan): \n";
    std::cout << "| FOCUS: Statistically proven by research (Zubair et al., 2024) to yield the highest\n";
    std::cout << "| concentration of peak grades (70 percent to 90 percent plus).\n";
    std::cout << "| STRATEGY: This must be divided to remain effective! Try 2 hours in the morning, 2 \n";
    std::cout << "| in the afternoon, and 1 to 2 in the evening. Use the Pomodoro technique (25 mins  \n";
    std::cout << "| study / 5 mins break) to protect your focus.                                      \n";
    std::cout << "....................................................................................\n";
    std::cout << "| Plan for up to 8 hours(Intensive Plan): \n";
    std::cout << "| FOCUS: Reserved for extreme workloads only (e.g., major finals week or complex    \n";
    std::cout << "| project crunching).                                                               \n";
    std::cout << "| STRATEGY: Treat it like a full-time job. Take a hard 1-hour lunch break in the    \n";
    std::cout << "| middle.                                                                           \n";
    std::cout << "| Focus entirely on active recall and practice testing, as passive reading will     \n";
    std::cout << "| quickly cause your brain to tune out.\n";
    std::cout << "....................................................................................\n";
    std::cout << "| CAUTION: Research shows sharp diminishing returns and severe burnout risks past 6 \n";
    std::cout << "| hours. Do not run this plan multiple days in a row. Your mental health and        \n";
    std::cout << "| cognitive recovery always come first.\n";
}
//for viewing / displaying lang ng about us
void displayAboutUs() {
    std::cout << "=================================== ABOUT US =========================================\n";
    std::cout << "|            Hey there! We re WONDERTECHS, the team behind StudyWell!                |\n";
    std::cout << "| Driven by UN Sustainable Development Goal 3: Good Health and Well-Being, we made   |\n";
    std::cout << "| StudyWell lightweight, terminal-based application built entirely in C++.           |\n";
    std::cout << "|              ...................................................                   |\n";
    std::cout << "| We noticed a major flaw in academic culture: the toxic cycle of cramming, burnout, |\n";
    std::cout << "| and late-night study sessions that leave students completely drained.              |\n";
    std::cout << "| Finding a way to balance high grades and mental health felt nearly impossible.     |\n";
    std::cout << "|              ...................................................                   |\n";
    std::cout << "| And as fellow students, we believe productivity shouldn't cost you your wellness.  |\n";
    std::cout << "| So, study smart and StudyWell!                                                     |\n";
    std::cout << "======================================================================================\n";
    std::cout << "| CREATORS OF STUDYWELL: \n";
    std::cout << "| [1.] Capablanca, Dimple Ann Mae S.\n";
    std::cout << "| [2.] Del Prado, Jade Louis S.\n";
    std::cout << "| [3.] Florendo, Allysa Anne D.\n";
    std::cout << "| [4.] Villena, Aiden Johann K.\n";
}
//for viewing / displaying lang references on how we carefully and safely get those wellness reocrds
void displayReferences() {                                                                       
    std::cout << "============================== SOURCES / REFERENCES ===============================\n";
    std::cout << "| LIST: \n";
    std::cout << "| [1.] https://doi.org/10.54660/.ijmrge.2024.5.3.720-728\n";
    std::cout << "| The impact of study hours on academic performance: A statistical analysis of students\n";
    std::cout << "| grades.\n ";
    std::cout << "...................................................................................\n";
    std::cout << "| [2.] https://doi.org/10.4103/jehp.jehp_600_20\n";
    std::cout << "| Relation between stress, time management, and academic achievement in preclinical\n";
    std::cout << "| medical education: A systematic review and meta-analysis.\n";
    std::cout << "...................................................................................\n";
    std::cout << "| [3.] https://doi.org/10.3389/feduc.2024.1119110\n";
    std::cout << "| Student wellbeing and academic support in higher education.\n";
    std::cout << "...................................................................................\n";
    std::cout << "| [4.] https://doi.org/10.17226/26015\n";
    std::cout << "| Mental health, substance use, and wellbeing in higher education\n";
}
//for poviding ng study plan na merong conditional statements na magbebase don sa result nila for stress and wellbeing
std::string studyPlanProvider(int wellbeing, int stress) {
    std::string plan;

    std::cout << "============================= RECOMMENDED STUDY PLAN ==============================\n";

    if (stress >= 9) {
        plan = "High stress - 1 to 2 hours only with rest. Remember that mental health matters.";
        std::cout << "| " << plan << " :)\n";
    }
    else if (wellbeing <= 13) {
        plan = "Light Plan - 1 to 2 hours is recommended for you.";
        std::cout << "| " << plan << " :)\n";
    }
    else if (wellbeing <= 18) {
        plan = "Moderate Plan - 4 hours is recommended for you, but it will still depend on you.";
        std::cout << "| " << plan << " :)\n";
    }
    else if (wellbeing <= 23) {
        plan = "Optimal Plan - 4 to 6 hours. Do it if you can for better outcomes.";
        std::cout << "| " << plan << " :)\n";
    }
    else {
        plan = "Intensive Plan - Up to 8 hours. Only do this if it is a must.";
        std::cout << "| " << plan << " :)\n";
    }

    return plan;
}