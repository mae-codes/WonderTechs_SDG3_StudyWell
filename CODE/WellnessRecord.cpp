#include "WellnessRecord.h"

//for creating ng records
WellnessRecord::WellnessRecord(int h, int w, int s, std::string p) {
    studyHours = h;
    wellbeing = w;
    stress = s;
    studyPlan = p;
}
//getters is used for reading the data na naka store
int WellnessRecord::getStudyHours()const{return studyHours;}
int WellnessRecord::getWellbeing()const{return wellbeing;}
int WellnessRecord::getStress()const{return stress;}
std::string WellnessRecord::getStudyPlan()const{return studyPlan;}

//for updating the records
void WellnessRecord::setData(int h, int w, int s, std::string p) {
    studyHours = h;
    wellbeing = w;
    stress = s;
    studyPlan = p;
}