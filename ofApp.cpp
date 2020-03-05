#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(0);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->cap.open("D:\\Pexels Videos 2441067.mp4");
	this->cap_size = cv::Size(1280, 720);
	this->cap.set(cv::CAP_PROP_POS_FRAMES, 90 * 24); // Sec * FrameRate

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 5, true, true, true);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	cv::Mat src;
	this->cap >> src;
	if (src.empty()) {

		this->cap.set(cv::CAP_PROP_POS_FRAMES, 1);
		return;
	}

	cv::resize(src, this->frame, this->cap_size);
	cv::cvtColor(this->frame, this->frame, cv::COLOR_BGR2GRAY);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	char moji[11] = { ' ', '#', 'M', 'W', 'A', 'B', 'G', 'C', 'L', 'I', 'T' };
	int value;
	for (int y = 0; y < this->frame.rows; y += 5) {

		for (int x = 0; x < this->frame.cols; x += 5) {
			
			value = this->frame.at<unsigned char>(y, x);
			if (value < 150) {

				this->font.drawStringAsShapes(string{ moji[(int)ofMap(value, 0, 150, 0, 11)] }, x - 640, 360 - y);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}