//
//  galvanic.cpp
//  until_dawn_screen_2
//
//  Created by miguel on 22/08/15.
//
//

#include "galvanic.h"
#include "ofxJSON.h"


Galvanic::Galvanic(App *a){
    
    app = a;
    
    assets = Assets::getInstance();
    video = assets->galvanic;
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
 
    for(int i = 0; i < SIZE; i ++){
        voltage.push_back(0.5);
    }
}


Galvanic::~Galvanic(){
    video.stop();
}


void Galvanic::update(){
    video.update();
    updateMeasures();
    
    
}

void Galvanic::draw(){
    if(video.isLoaded())
        drawVideo();
    
    drawMeasures();
}

void Galvanic::drawVideo(){
    ofPushStyle();
    ofSetColor(assets->blue);
    video.draw(550, 845);
    ofPopStyle();
}

void Galvanic::updateMeasures(){
    ofxJSONElement response = app->data["galvanicVoltage"];
    conductance = response[response.size() - 1].asFloat();
    response = app->data["galvanicVoltage"];
    for(int i = 0; i < SIZE; i ++){
        voltage[i] = response[response.size() - 1 - i].asFloat() / 100.;
    }

    
}

void Galvanic::drawMeasures(){
    ofTrueTypeFont *font = assets->getFont(12);
    
    string msg = "CONDICTIVIDAD GALVANICA";
    font->drawStringAsShapes(msg, 605,  890 + font->getLineHeight() / 1.5);
    
    msg = "RESULTADO";
    font->drawStringAsShapes(msg, 1000 - font->stringWidth(msg),  890 + font->getLineHeight() / 1.5);
    
    
    font = assets->getFont(26);
    
    int v = conductance;
    msg = ofToString(v) + " %";
    font->drawStringAsShapes(msg, 1000 - font->stringWidth(msg),  916 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(18);
    
    msg = "S/m";
    font->drawStringAsShapes(msg, 1000 - font->stringWidth(msg),  956 + font->getLineHeight() / 1.5);
    
    
    font = assets->getFont(12);
    
    msg = "VOLTAGE";
    font->drawStringAsShapes(msg, 1000 - font->stringWidth(msg),  1256 + font->getLineHeight() / 1.5);
    
    ofPushMatrix();
    ofTranslate(600, 1250) ;
    ofScale(2, 1);
    int N =  voltage.size();
    for(int i = 1; i < N; i ++){
        float v0 = ofClamp(50 - voltage[N - i-1] * 100, 0, 50);
        float v1 = ofClamp(50 - voltage[N - i] * 100, 0, 50);
        ofLine(i - 1 , v0, i, v1);
        if(i == 200) break;
    }
    
    ofPopStyle();
    ofPopMatrix();

}