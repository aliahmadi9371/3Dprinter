#ifndef MATERIALCONFIG_H
#define MATERIALCONFIG_H

#include "iostream"

#define MAXMATERIALS 24

using namespace std;

struct MaterialConfig {
    uint16_t id;
    string Name;
    unsigned int LayerThickness;
    unsigned int BurnInLayers;
    float BurnInCureTime;
    float NormalCureTime;
    float BurnIntensity;
    float Intensity;
};


#endif // MATERIALCONFIG_H
