//
//  heart.h
//  until_dawn_screen_2
//
//  Created by miguel on 22/08/15.
//
//

#ifndef __until_dawn_screen_2__heart__
#define __until_dawn_screen_2__heart__
#include "ofMain.h"
#include "assets.h"

#include "App.h"

#define SIZE 200


class Heart
{
    
    App *app;
    
    ofVideoPlayer video;
    Assets *assets;
    void drawVideo();
    void drawMeasures();
    void updateMeasures();
    
    int beat;
    int max;
    
    vector<float> beats;
    
public:
    Heart(App *a);
    ~Heart();
    void draw();
    void update();
    vector<float> beats_values;
};
#endif /* defined(__until_dawn_screen_2__heart__) */
