//
//  index.h
//  until_dawn_screen_1
//
//  Created by miguel on 19/08/15.
//
//

#ifndef __until_dawn_screen_1__index__
#define __until_dawn_screen_1__index__

#include <State.h>
#include "ofxJSON.h"

class Index: public State
{
    
    ofVideoPlayer video;
    

public:
    Index(App *g);
    ~Index(){
        video.stop();
    };
    std::string toString() { return "index"; }
    void update();
    void draw();
    void next();
    void clear();
    
    ofVideoPlayer computeIndiceVideo(ofxJSONElement top);
    
    ofxJSONElement user;
};


#endif /* defined(__until_dawn_screen_1__index__) */
