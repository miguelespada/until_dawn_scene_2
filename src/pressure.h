//
//  pressure.h
//  until_dawn_screen_2
//
//  Created by miguel on 22/08/15.
//
//

#ifndef __until_dawn_screen_2__pressure__
#define __until_dawn_screen_2__pressure__
#include "ofMain.h"
#include "assets.h"

#include "App.h"


class Pressure
{
    
    App *app;
    
    ofVideoPlayer video;
    Assets *assets;
    void drawVideo();
    void drawMeasures();
    void updateMeasures();
    void drawStress();
    
    float mean;
    int max;
    int peaks;
    float last;
    
public:
    Pressure(App *a);
    ~Pressure();
    void draw();
    void update();
    
};

#endif /* defined(__until_dawn_screen_2__pressure__) */
