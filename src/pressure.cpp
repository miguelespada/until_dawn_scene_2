//
//  pressure.cpp
//  until_dawn_screen_2
//
//  Created by miguel on 22/08/15.
//
//

#include "pressure.h"
#include "ofxJSON.h"


Pressure::Pressure(App *a){
    app = a;
    
    assets = Assets::getInstance();
    video = assets->pressure;
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
    
 
}


Pressure::~Pressure(){
}


void Pressure::update(){
    video.update();
    updateMeasures();
    
    
}

void Pressure::draw(){
    if(video.isLoaded())
        drawVideo();
    
    drawMeasures();
    drawStress();
}

void Pressure::drawVideo(){
    ofPushStyle();
    ofSetColor(assets->yellow);
    video.draw(480, 1280);
    ofPopStyle();
}

void Pressure::updateMeasures(){
    ofxJSONElement stress = app->data["stress"];
    ofxJSONElement flow = app->data["flow"];
    
    if(flow.size() < 100 || stress.size() < 100)
    mean = 0;
    peaks = 0;
    max = 0;
    last = stress[stress.size() - 1].asFloat();
    
    int M = stress.size();
    if(stress.size() > flow.size())
        M = flow.size();
    
    if(M > 100)
        M = 100;
    
    float prev = 0;
    for(int i = 0; i < M; i ++){
        float v1 = stress[stress.size() - i - 1].asFloat() * .7;
        float v2 = flow[flow.size() - i - 1].asFloat() * 100 * .3;
        float v = v1 + v2;
        
        mean += v;
        if(v > max)
            max = v;
        
        if(v > prev * 1.4)
            peaks ++;
        prev = v;
        
        
    }
    mean /=  M;
    
}

void Pressure::drawMeasures(){
    ofTrueTypeFont *font = assets->getFont(12);
    
    string msg = "STRESS";
    font->drawStringAsShapes(msg, 605,  1360 + font->getLineHeight() / 1.5);
    
    msg = "RESULTADO";
    font->drawStringAsShapes(msg, 1000 - font->stringWidth(msg),  1360 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(26);
    
    msg = ofToString(int(mean * 100) / 100.);
    font->drawStringAsShapes(msg, 1000 - font->stringWidth(msg),  1387 + font->getLineHeight() / 1.5);

    font = assets->getFont(18);
    
    msg = "%";
    font->drawStringAsShapes(msg, 1000 - font->stringWidth(msg),  1425 + font->getLineHeight() / 1.5);
    
    
    font = assets->getFont(12);
    
    msg = "CURRENT";
    font->drawStringAsShapes(msg, 592,  1773 + font->getLineHeight() / 1.5);
    
    msg = ofToString(int(last * 100) / 100);
    font->drawStringAsShapes(msg, 756 - font->stringWidth(msg),  1773 + font->getLineHeight() / 1.5);
    
    msg = "PEAKS";
    font->drawStringAsShapes(msg, 592, 1796 + font->getLineHeight() / 1.5);
    
    msg = ofToString(int(peaks));
    font->drawStringAsShapes(msg, 756 - font->stringWidth(msg),  1796 + font->getLineHeight() / 1.5);
    
    msg = "MAX";
    font->drawStringAsShapes(msg, 592,  1821 + font->getLineHeight() / 1.5);
    
    msg = ofToString(int(max));
    font->drawStringAsShapes(msg, 756 - font->stringWidth(msg),  1821 + font->getLineHeight() / 1.5);
    
    

    
}

void Pressure::drawStress(){
    ofTrueTypeFont *font = assets->getFont(12);
    
    string msg = "ZONAS DE STRESS";
    font->drawStringAsShapes(msg, 996 - font->stringWidth(msg),  526 + font->getLineHeight() / 1.5);
    
    ofxJSONElement stress = app->data["stress"];
    ofxJSONElement flow = app->data["flow"];
    
    int M = stress.size();
    if(stress.size() > 100)
        M = 100;
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(812, 650);
    ofScale(1.9, 1);
    
    ofSetColor(assets->yellow);
    
    for(int i = 0; i < M; i += 1){
        float v1 = stress[stress.size() - i - 1].asFloat() * .7;
        float v2 = flow[flow.size() - i - 1].asFloat() * 100 * .3;
        float v = v1 + v2;
        ofLine(i, 0, i, v);
        ofLine(i, 0, i, -v);
    }
    ofPopStyle();
    ofPopMatrix();
    
}