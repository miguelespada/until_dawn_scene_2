//
//  pressure.cpp
//  until_dawn_screen_2
//
//  Created by miguel on 22/08/15.
//
//

#include "heart.h"
#include "ofxJSON.h"

Heart::Heart(App *a){
    
    app = a;
    
    assets = Assets::getInstance();
    video = assets->heart;
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
    
    
    for(int i = 0; i < SIZE; i ++){
        beats.push_back(0);
    }
    
    beat = 0;
}


Heart::~Heart(){
    cout << "STOP" << endl;
    video.stop();
}


void Heart::update(){
    
    video.update();
    updateMeasures();
    
    
}

void Heart::draw(){
    if(video.isLoaded())
        drawVideo();
    
    drawMeasures();
}

void Heart::drawVideo(){
    ofPushStyle();
    ofSetColor(assets->red);
    video.draw(85, 308);
    ofPopStyle();
}

void Heart::updateMeasures(){
    ofxJSONElement response = app->data["heartRate"];
    
    int M = response.size();
    if (M < 2) return; 
    if(M > 50)
        M = 50;
    
    beat = 0;
    
    for(int i = 0; i < M; i ++){
        beat += response[response.size() - i - 1].asInt();
    }
    beat /= M;
    beats.push_back(beat);
    
    if(beats.size() > 100)
        beats.erase(beats.begin());
    
}

void Heart::drawMeasures(){
    ofTrueTypeFont *font = assets->getFont(12);
    
    string msg = "RITMO CARDIACO";
    font->drawStringAsShapes(msg, 85,  392 + font->getLineHeight() / 1.5);
    
    msg = "RESULTADO";
    font->drawStringAsShapes(msg, 728 - font->stringWidth(msg),  392 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(26);
    
    msg = ofToString(beat) + " BPM";
    font->drawStringAsShapes(msg, 728 - font->stringWidth(msg),  420 + font->getLineHeight() / 1.5);
    
    font = assets->getFont(12);
    
    msg = "TIME";
    font->drawStringAsShapes(msg, 539,  709 + font->getLineHeight() / 1.5);
    
    msg = ofToString(float(beat / 600.)) + " mS";
    font->drawStringAsShapes(msg, 732 - font->stringWidth(msg),  709 + font->getLineHeight() / 1.5);
    
    
    ofPushMatrix();
    ofTranslate(540, 800) ;
    ofScale(1, 0.5);
    if(beats_values.size() > 2){
        for(int i = 1; i < beats_values.size(); i ++)
            ofLine(i - 1 , -beats_values[beats_values.size() - i - 1], i, -beats_values[beats_values.size() - i]);
    }
    ofPopStyle();
    ofPopMatrix();
    
}