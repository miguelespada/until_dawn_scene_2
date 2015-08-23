//
//  optical.h
//  until_dawn_screen_2
//
//  Created by miguel on 21/08/15.
//
//

#ifndef __until_dawn_screen_2__optical__
#define __until_dawn_screen_2__optical__
#include "ofMain.h"
#include "assets.h"

#include "App.h"

#define FLOW_SIZE 200


class Optical
{
    ofVideoPlayer video;
    Assets *assets;
    void drawVideo();
    void drawMeasures();
    void updateMeasures();
    
    
    vector<float> flow;
    
    float mean;
    int peaks;
    float var;
    float max;
    App *app;
    
public:
    Optical(App *a);
    ~Optical();
    void draw();
    void update();

};

#endif /* defined(__until_dawn_screen_2__optical__) */
