#ifndef __until_dawn_screen_1__data__
#define __until_dawn_screen_1__data__

#include <State.h>
#include "optical.h"
#include "thermal.h"
#include "galvanic.h"
#include "pressure.h"
#include "heart.h"

class Data: public State
{
    
    Assets *assets;
    
public:
    Data(App *g);
    ~Data(){};
    std::string toString() { return "Data"; }
    void update();
    void draw();
    void next();
    void processOsc();
    
    Optical *optical;
    
    Thermal *thermal;
    Galvanic *galvanic;
    Pressure *presure;
    Heart *heart;
};

#endif /* defined(__until_dawn_screen_1__standby__) */