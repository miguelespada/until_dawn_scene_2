//
//  eye.cpp
//  until_dawn_screen_2
//
//  Created by miguel on 16/07/15.
//
//

#include "optical.h"


Optical::Optical(App *a){
    
    app = a;
    assets = Assets::getInstance();
    video = assets->optical;
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
    
    for(int i = 0; i < FLOW_SIZE; i ++){
        flow.push_back(0);
    }

    peaks = 0;
    mean = 0;
    var = 0;
}


Optical::~Optical(){
}


void Optical::update(){
    video.update();
    
    if(ofGetFrameNum() % 15 == 0)
        updateMeasures();
}

void Optical::draw(){
    if(video.isLoaded())
        drawVideo();
    
    drawMeasures();
}

void Optical::drawVideo(){
    ofPushStyle();
    ofSetColor(assets->green);
    video.draw(40, 1380);
    ofPopStyle();
}

void Optical::updateMeasures(){
    ofxJSONElement response = app->data["flow"];
    
    peaks = 0;
    mean = 0;
    var = 0;
    max = 0;
    
    if(response.size() >= FLOW_SIZE){
        for(int i = 0; i < FLOW_SIZE; i ++){
            flow[i] = response[response.size() - 1 - i].asFloat();
            
            if(flow[i] > max)
                max = flow[i];
            
            mean += flow[i];
            if(i >= 1){
                var += abs(flow[i] - flow[i - 1]);
                if(flow[i] > flow[i - 1] * 1.5)
                    peaks += 1;
            }
        }
        mean /= FLOW_SIZE;
        var /= FLOW_SIZE;
        mean *= 1000;
        var *= 1000;
        max *= 1000;
    }
}

void Optical::drawMeasures(){
    ofTrueTypeFont *font = assets->getFont(12);
    
    string msg = "OPTICAL FLOW";
    font->drawStringAsShapes(msg, 85,  1360 + font->getLineHeight() / 1.5);
    
    msg = "RESULTADO";
    font->drawStringAsShapes(msg, 480 - font->stringWidth(msg),  1360 + font->getLineHeight() / 1.5);
    ;
    
    font = assets->getFont(26);
    
    msg = ofToString(peaks);
    font->drawStringAsShapes(msg, 480 - font->stringWidth(msg),  1387 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(18);
    
    msg = "PEAKS/SEC";
    font->drawStringAsShapes(msg, 480 - font->stringWidth(msg),  1425 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(12);
    
    msg = "MEAN";
    font->drawStringAsShapes(msg, 85,  1773 + font->getLineHeight() / 1.5);
    
    msg = ofToString(int(mean));
    font->drawStringAsShapes(msg, 248 - font->stringWidth(msg),  1773 + font->getLineHeight() / 1.5);
    
    msg = "MAX";
    font->drawStringAsShapes(msg, 85, 1796 + font->getLineHeight() / 1.5);
    
    
    msg = ofToString(int(max));
    font->drawStringAsShapes(msg, 248 - font->stringWidth(msg),  1796 + font->getLineHeight() / 1.5);
    
    msg = "VAR";
    font->drawStringAsShapes(msg, 85,  1821 + font->getLineHeight() / 1.5);
    
    msg = ofToString(int(var));
    font->drawStringAsShapes(msg, 248 - font->stringWidth(msg),  1821 + font->getLineHeight() / 1.5);
    
    
    int s = 150;
    
    ofPushMatrix();
    ofTranslate(85, 1750) ;
    
    ofScale(2, 1);
    for(int i = 1; i < flow.size(); i ++)
        ofLine(i - 1 , - flow[i - 1] * s, i, - flow[i] * s);
    
    ofPopStyle();
    ofPopMatrix();
}