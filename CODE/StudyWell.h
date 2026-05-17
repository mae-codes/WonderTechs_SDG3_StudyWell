#ifndef STUDYWELL_H
#define STUDYWELL_H

#include <vector>
#include <string>
#include "WellnessRecord.h"

bool login(std::string &name, int &age);

void loadData(std::vector<WellnessRecord>& records, const std::string& currentUser);
void saveData(std::vector<WellnessRecord>& records, const std::string& name, int age);

void checkWellness(std::vector<WellnessRecord>& records);
void viewHistory(const std::vector<WellnessRecord>& records);

void studyPlanGuide();
void displayAboutUs();
void displayReferences();

void editSession(std::vector<WellnessRecord>& records);
void deleteSession(std::vector<WellnessRecord>& records);

std::string studyPlanProvider(int wellbeing, int stress);
int inputValidation(int min, int max);
bool nameValidation(const std::string& name);

#endif