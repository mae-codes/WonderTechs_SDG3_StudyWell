#ifndef WELLNESSRECORD_H
#define WELLNESSRECORD_H
#include <string>

class WellnessRecord {
private:
    int studyHours;
    int wellbeing;
    int stress;
    std::string studyPlan;

public:
    //constructor
    WellnessRecord(int h = 0, int w = 0, int s = 0, std::string p = " "); //initialization of values ng parameters ng each data
    //getters - for reading the private data
    int getStudyHours() const;
    int getWellbeing() const;
    int getStress() const;
    std::string getStudyPlan() const;

    //for updating the records
    void setData(int h, int w, int s, std::string p);
};

#endif