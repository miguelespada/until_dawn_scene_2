//
//  thermal.cpp
//  until_dawn_screen_2
//
//  Created by miguel on 22/08/15.
//
//

#include "thermal.h"
#include "ofxJSON.h"


Thermal::Thermal(App *a){
    
    app = a;
    
    assets = Assets::getInstance();
    video = assets->thermal;
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
    
}


Thermal::~Thermal(){
    video.stop();
}


void Thermal::update(){
    video.update();
    updateMeasures();
    
}

void Thermal::draw(){
    if(video.isLoaded())
        drawVideo();
    
    drawMeasures();
}

void Thermal::drawVideo(){
    ofPushStyle();
    ofSetColor(assets->orange);
    video.draw(40, 879);
    ofPopStyle();
}

void Thermal::updateMeasures(){
    ofxJSONElement response = app->data["temp"];
    temperature = response[response.size() - 1].asFloat() / 100.;


}

void Thermal::drawMeasures(){
    
    
    ofTrueTypeFont *font = assets->getFont(12);
    
    string msg = "TEMPERATURA";
    font->drawStringAsShapes(msg, 85,  890 + font->getLineHeight() / 1.5);
    
    msg = "RESULTADO";
    font->drawStringAsShapes(msg, 480 - font->stringWidth(msg),  890 + font->getLineHeight() / 1.5);
    
    
    font = assets->getFont(26);
    
    msg = ofToString(temperature);
    font->drawStringAsShapes(msg, 480 - font->stringWidth(msg),  916 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(18);
    
    msg = "ºC";
    font->drawStringAsShapes(msg, 480 - font->stringWidth("CC"),  956 + font->getLineHeight() / 1.5);

    float x = ofMap(temperature, 26., 42., 86., 480.);
    
    ofLine(x, 1278, x, 1283);
}