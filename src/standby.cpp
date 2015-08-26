//
//  standby.cpp
//  until_dawn_screen_1
//
//  Created by miguel on 20/08/15.
//
//

#include "standby.h"
#include "App.h"
#include "Assets.h"
#include "data.h"

Standby::Standby(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    
    video = Assets::getInstance()->standby;
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
};

void Standby::draw(){
    if(video.isLoaded())
        video.draw(0, 0);
};

void Standby::update(){
    
    video.update();

}


void Standby::next(){
    app->setCurrentState(new Data(app));
    delete this;
};


void Standby::clear(){
    video.stop();
};