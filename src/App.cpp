#include "App.h"


App::App(){
    // Register events and actions
    ofAddListener(ofEvents().keyPressed, this, &App::keyPressed);
    ofAddListener(ofEvents().update, this, &App::update);
    
    receiver = new ofxOscReceiver;
    receiver->setup(12342);
    data.open("http://192.168.1.42:3000/last.json");
}

void App::setCurrentState(State *s){
    current_state = s;
}

void App::next(){
    current_state->next();
}

void App::jump(){
    current_state->jump();
}

void App::cancel(){
    current_state->cancel();
}

void App::draw(){
    ofPushStyle();
    ofPushMatrix();
    current_state->draw();
    ofPopMatrix();
    ofPopStyle();
}

void App::update(){
    current_state->update();
    current_state->processOsc();
    
    if(ofGetFrameNum() % 15 == 0){
        data.open("http://192.168.1.42:3000/last.json");
    }
}

void App::update(ofEventArgs &args){
    update();
}

void App::keyPressed (ofKeyEventArgs& eventArgs){
    ofxJSONElement response;
    switch (eventArgs.key) {
        case 'n':
            next();
            break;
        default:
            break;
    }
}