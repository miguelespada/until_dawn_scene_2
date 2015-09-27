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
    max = app->data["max_temp"].asInt() / 100.;
    min = app->data["min_temp"].asInt() / 100.;
}

void Thermal::drawMeasures(){
    
    
    ofTrueTypeFont *font = assets->getFont(12);
    
    string msg = "TEMPERATURA";
    font->drawStringAsShapes(msg, 85,  890 + font->getLineHeight() / 1.5);
    
    msg = "CURRENT";
    font->drawStringAsShapes(msg, 480 - font->stringWidth(msg),  890 + font->getLineHeight() / 1.5);
    
    
    font = assets->getFont(26);
    
    msg = ofToString(temperature);
    font->drawStringAsShapes(msg, 480 - font->stringWidth(msg),  916 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(18);
    
    msg = "ºC";
    font->drawStringAsShapes(msg, 480 - font->stringWidth("CC"),  956 + font->getLineHeight() / 1.5);

    float x = ofMap(temperature, 26., 42., 86., 480.);
    
    ofLine(x, 1278, x, 1283);
    
    
    font = assets->getFont(12);
    
    
    msg = "MAX: " + ofToString(max);
    font->drawStringAsShapes(msg, 85, 916 + font->getLineHeight() / 1.5);
    
    msg = "MIN: " + ofToString(min);
    font->drawStringAsShapes(msg, 85,  940 + font->getLineHeight() / 1.5);
    
    msg = "TEMP";
    font->drawStringAsShapes(msg, 480 - font->stringWidth(msg),  1150 + font->getLineHeight() / 1.5);
    
    
    ofPushMatrix();
    
    ofxJSONElement data = app->data["temp"];

    ofTranslate(85, 1200) ;
    ofScale(2, 1);
    int N = data.size();
    for(int i = 1; i < N; i ++){
        float v0 = 50 - data[N - i].asInt() / 100.;
        float v1 = 50 - data[N - i - 1].asInt() / 100.;
        ofLine(i - 1 , v0, i, v1);
        if(i == 200) break;
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}