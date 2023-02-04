#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "parser/wrl.h"

// uv map

int main(){
    Scene * scene = WRL::Parser::parse("subject020.wrl");
    // Scene * scene = WRL::Parser::parse("wrl/2017141061049.wrl");
    // Scene * scene = WRL::Parser::parse("wrl/face.wrl");
    // WRL::Parser::store( "face1.txt" , scene );

    // delete scene;
    
}