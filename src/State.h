//
//  State.h
//  Game
//
//  Created by miguel on 12/10/14.
//
//

#ifndef __game__State__
#define __game__State__

#include "ofMain.h"
#include "ofxOsc.h"

class App;

class State
{
public:
    App *app;
    float timer;
    virtual void next()=0;
    virtual void jump(){};
    virtual void cancel(){};
    virtual std::string toString() {};
    virtual void draw() {};
    virtual void update() {};
    virtual void standby();
    virtual void index();
    virtual void clear() {};
    virtual void calculandoIndex();
    virtual void addBeat(int b){};
};


#endif /* defined(__planta__Idle__) */


