//
//  galvanic.h
//  until_dawn_screen_2
//
//  Created by miguel on 22/08/15.
//
//

#ifndef __until_dawn_screen_2__galvanic__
#define __until_dawn_screen_2__galvanic__

#include "ofMain.h"
#include "assets.h"

#include "App.h"

#define SIZE 200

class Galvanic
{
    ofVideoPlayer video;
    Assets *assets;
    void drawVideo();
    void drawMeasures();
    void updateMeasures();
    
    float conductance;
    
    App *app;
    
    
    vector<float> voltage;
    
public:
    Galvanic(App *a);
    ~Galvanic();
    void draw();
    void update();
    
};


#endif /* defined(__until_dawn_screen_2__galvanic__) */
