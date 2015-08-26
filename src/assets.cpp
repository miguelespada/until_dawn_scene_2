//
//  assets.cpp
//  until_dawn_screen_2
//
//  Created by miguel on 16/07/15.
//
//

#include "assets.h"
Assets::Assets(){
}

Assets* Assets::instance = 0;

Assets* Assets::getInstance(){
    if (instance == 0){
        instance = new Assets();
        instance->load();
    }
    return instance;
};


void Assets::load(){
    
    
    string filename = "wireframe.png";
    wireframe.loadImage(filename);
    ofLogNotice() << "Loading: " << filename;
    
    
    filename = "optical.mov";
    optical.loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    
    
    filename = "thermal.mov";
    thermal.loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    
    
    filename = "galvanic.mov";
    galvanic.loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    
    filename = "pressure.mov";
    pressure.loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    
    filename = "heart.mov";
    heart.loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    
    
    filename = "calculando.mov";
    calculando.loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    
    filename = "1_Indiferencia.mov";
    indices[0].loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    filename = "2_Inquietud.mov";
    indices[1].loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    filename = "3_Miedo.mov";
    indices[2].loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    filename = "4_Espanto.mov";
    indices[3].loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    filename = "5_Panico.mov";
    indices[4].loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    
    filename = "standby.mov";
    standby.loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    
    
    for(int i = 0; i < 64; i++)
        fonts[i] = NULL;
}

ofTrueTypeFont *Assets::getFont(int size){
    if(fonts[size] == NULL){
        fonts[size] = new ofTrueTypeFont();
        fonts[size]->loadFont("Akkurat-Mono.ttf", size, true, true, true);
        fonts[size]->setLetterSpacing(1.1);
        fonts[size]->setSpaceSize(0.3);
        
        ofLogNotice() << "Loading: " << "Akkurat-Mono.ttf " << size;
    }
    return fonts[size];
}
