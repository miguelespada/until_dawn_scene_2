#include "App.h"
#include "standby.h"
#include "index.h"
#include "calculandoIndex.h"


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
    
    if(ofGetFrameNum() % 15 == 0){
        data.open("http://192.168.1.42:3000/last.json");
    }
    
    while(receiver->hasWaitingMessages()){
        ofxOscMessage m;
        receiver->getNextMessage(&m);
        
        if(m.getAddress() == "/standby"){
            current_state->clear();
            setCurrentState(new Standby(this));
        }
        
        if(m.getAddress() == "/next"){
            current_state->next();
        }
        
        if(m.getAddress() == "/index"){
            current_state->clear();
            setCurrentState(new Index(this));
        }
        
        if(m.getAddress() == "/calculandoIndex"){
            current_state->clear();
            setCurrentState(new calculandoIndex(this));
        }
        
        if(m.getAddress() == "/save"){
            bSave = bool(m.getArgAsInt32(0));
            save();
        }
        if(m.getAddress() == "/heart"){
            current_state->addBeat(m.getArgAsInt32(0));
        }
        
        if(m.getAddress() == "/flow"){
            current_state->addFlow(m.getArgAsFloat(0));
        }
        
        
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

void App::save(){
    ofLogNotice() << "Saving ---> " << bSave;
    dir = "images/" + data["_id"]["$oid"].asString();
    if(bSave && !ofDirectory::doesDirectoryExist(dir)){
        ofDirectory::createDirectory(dir, true);
        ofLogNotice() << "Creating directory: " << dir << endl;
    }
}