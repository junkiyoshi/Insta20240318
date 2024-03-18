#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
	ofSetLineWidth(2);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 50, true, true, true);
	//this->word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	this->word = "0123456789";

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->noise_param += 0.001;
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	ofSeedRandom(39);
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int z = 150; z < 280; z += 1) {

		ofPushMatrix();
		ofRotateZ(ofMap(ofNoise(noise_seed.x, z * 0.008 + ofGetFrameNum() * 0.0015), 0, 1, -360, 360));
		ofRotateY(ofMap(ofNoise(noise_seed.y, z * 0.008 + ofGetFrameNum() * 0.0015), 0, 1, -360, 360));
		ofRotateX(ofMap(ofNoise(noise_seed.z, z * 0.008 + ofGetFrameNum() * 0.0015), 0, 1, -360, 360));

		auto base_location = glm::vec3(-25, 25, z);

		ofPath chara_path = this->font.getCharacterAsPoints(this->word[(int)ofMap(ofNoise(ofRandom(1000), this->noise_param), 0, 1, 0, this->word.size())], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofFill();
		ofSetColor(239);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getResampledByCount(100).getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex + base_location);
			}
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(0);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getResampledByCount(100).getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex + base_location);
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();

	/*
	int start = 400;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}