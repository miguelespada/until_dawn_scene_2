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

Data::~Data(){
    delete optical;
    delete thermal;
    delete galvanic;
    delete presure;
    delete heart;
}

void Data::draw(){
    
    presure->draw();
    galvanic->draw();
    
    heart->draw();
    thermal->draw();
    optical->draw();
    
    ofTrueTypeFont *font = assets->getFont(36);
    
    string msg = app->data["name"].asString();
    font->drawStringAsShapes(msg, 85,  220 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(12);
    msg = "NOMBRE";
    font->drawStringAsShapes(msg, 85,  175 + font->getLineHeight() / 1.5);
    
    msg = "INDICE UNTIL DAWN";
    font->drawStringAsShapes(msg, 770,  143 + font->getLineHeight() / 1.5);
    
    
    font = assets->getFont(12);
    msg = "TIEMPO";
    font->drawStringAsShapes(msg, 770,  175 + font->getLineHeight() / 1.5);
    
    drawElapsedTime();
    
    
    assets->wireframe.draw(0, 0);
};

void Data::drawElapsedTime(){
    
    ofTrueTypeFont *font = assets->getFont(36);
    int elapsed_seconds = app->data["runningTime"].asInt();
    int elapsed_minutes = elapsed_seconds / 60;
    elapsed_seconds %= 60;
    string leading_minutes = "";
    if(elapsed_minutes < 10)
        leading_minutes = "0";
    
    string leading_seconds = "";
    if(elapsed_seconds < 10)
        leading_seconds = "0";
    string msg;
    msg = leading_minutes + ofToString(elapsed_minutes) + ":" + leading_seconds + ofToString(elapsed_seconds);
    
    font->drawStringAsShapes(msg, 990 - font->stringWidth(msg),  220 + font->getLineHeight() / 1.5);
}

void Data::update(){
    optical->update();
    thermal->update();
    heart->update();
    
    galvanic->update();
    presure->update();
    
}


void Data::next(){
};

void Data::addBeat(int b){
    heart->beats_values.push_back(b);

    if(heart->beats_values.size() > 180){
        heart->beats_values.erase(heart->beats_values.begin());
    }
}

void Data::clear(){
    delete optical;
    delete thermal;
    delete galvanic;
    delete presure;
    delete heart;
};