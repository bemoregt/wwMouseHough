#include "ofApp.h"

using namespace ofxCv;
using namespace std;
//--------------------------------------------------------------
void ofApp::setup(){

    threshold= 128;
    filePath = "/Users/kerbal/Desktop/image.jpg";
    before.load(filePath);
}

//--------------------------------------------------------------
void ofApp::update(){

    cv::Mat img = toCv(before);
    cv::cvtColor(img, img, CV_BGR2GRAY);
    cv::Mat img2, img3;


    cv::Mat dst, cdst;
    cv::Canny(img, dst, threshold-20, threshold+20);
    toOf(dst, after);
    after.update();
    cvtColor(dst, cdst, CV_GRAY2BGR);

    std::vector<cv::Vec2f> lines;
    cv::HoughLines(dst, lines, 1, CV_PI/180, threshold2);
    
    
    cv::Mat result(dst.rows, dst.cols, CV_8U, cv::Scalar(255));
    std::cout << "Lines detected: " << lines.size() << std::endl;
    
    
    std::vector<cv::Vec2f>::const_iterator it= lines.begin();
    while (it!=lines.end()) {
        float rho = (*it)[0]; 
        float theta = (*it)[1]; 
        if (theta < PI/4. || theta > 3.*PI/4.) { 
            cv::Point pt1(rho/cos(theta), 0); 
            cv::Point pt2((rho-result.rows*sin(theta))/cos(theta), result.rows);
            
            cv::line(cdst, pt1, pt2, cv::Scalar(255), 2); 
            
        } else { 
            cv::Point pt1(0,rho/sin(theta)); 
            cv::Point pt2(result.cols,(rho-result.cols*cos(theta))/sin(theta));
            
            cv::line(cdst, pt1, pt2, cv::Scalar(255), 2); 
        }
        std::cout << "line: (" << rho << "," << theta << ")\n";
        ++it;
    }
    
    toOf(cdst, third);
    third.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    // image
    ofSetColor(255,255,255);
    before.draw(0, 0, 512, 512);
    after.draw(512, 0, 512, 512);
    third.draw(1024, 0, 512, 512);
    
    // filled box
    ofSetColor(100, 100, 100);
    ofDrawRectangle(5, 5, 200, 60);
    
    // text
    ofSetColor(255);
    ofDrawBitmapString("Canny Threshold= " + ofToString(threshold), 20, 30);
    ofDrawBitmapString("Hough Threshold= " + ofToString(threshold2), 20, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    threshold= (int)(x/1536.0*255);
    if(threshold <= 21){
        threshold =21;
    }
    if(threshold >= 234){
        threshold =235;
    }
    
    threshold2= (int)(y/512.0*255);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
