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

Data::Data(App *a){
    assets = Assets::getInstance();
    app = a;
    ofLogNotice() << "State: " << toString();
    optical = new Optical(app);
    thermal = new Thermal(app);
    galvanic = new Galvanic(app);
    presure = new Pressure(app);
    heart = new Heart(app);
};

void Data::draw(){
    
    presure->draw();
    galvanic->draw();
    
    heart->draw();
    thermal->draw();
    optical->draw();
    
    assets->wireframe.draw(0, 0);
};

void Data::update(){
    optical->update();
    thermal->update();
    heart->update();
    
    galvanic->update();
    presure->update();
    
    processOsc();
}


void Data::next(){
    app->setCurrentState(new Standby(app));
    delete this;
};

void Data::processOsc(){
    ofxOscMessage m;
    app->receiver->getNextMessage(&m);
    if(m.getAddress() == "/heart"){
        heart->beats_values.push_back(m.getArgAsInt32(0));

        if(heart->beats_values.size() > 180){
            heart->beats_values.erase(heart->beats_values.begin());
        }
    }

}
