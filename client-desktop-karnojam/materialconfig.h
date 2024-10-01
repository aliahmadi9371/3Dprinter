#ifndef MATERIALCONFIG_H
#define MATERIALCONFIG_H

#include "iostream"

#define MAXMATERIALS 24

using namespace std;

struct MaterialConfig {
    string Name;
    unsigned int LayerThickness;
    unsigned int BurnInLayers;
    float BurnInCureTime;
    float NormalCureTime;
    float BurnIntensity;
    float Intensity;
    uint16_t id;
};


#endif // MATERIALCONFIG_H
