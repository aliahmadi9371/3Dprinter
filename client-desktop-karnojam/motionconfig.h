#ifndef MOTIONCONFIG_H
#define MOTIONCONFIG_H

#include "iostream"

#define MAXMOTIONS 12

using namespace std;

struct MotionConfig {
    string Name;
    unsigned int Layer_Z_Raise[2];
    unsigned int Layer_Z_Lower[2];
    unsigned int Layer_Tilt_Raise[2];
    unsigned int Layer_Tilt_Lower[2];
    unsigned int Layer_Overlift[2];
    unsigned int Layer_Breathe[2];
    unsigned int Layer_Settle[2];
    unsigned int Layer_Tilt_Percent[2];
    unsigned int Cut_Off_Layers;
    unsigned int Final_OverLift;
    unsigned int Base_Layer_settle;
    uint16_t id;
};


#endif // MOTIONCONFIG_H
