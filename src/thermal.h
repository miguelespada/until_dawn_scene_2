//
//  thermal.h
//  until_dawn_screen_2
//
//  Created by miguel on 22/08/15.
//
//

#ifndef __until_dawn_screen_2__thermal__
#define __until_dawn_screen_2__thermal__
#include "ofMain.h"
#include "assets.h"

#include "App.h"


class Thermal
{
    ofVideoPlayer video;
    Assets *assets;
    void drawVideo();
    void drawMeasures();
    void updateMeasures();
    
    float temperature;
    
    App *app;
    
public:
    Thermal(App *a);
    ~Thermal();
    void draw();
    void update();
    
};

#endif /* defined(__until_dawn_screen_2__thermal__) */
