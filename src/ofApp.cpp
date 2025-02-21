#include "ofApp.h"

// =================== Implémentation de Node ===================
Node::Node(int value, float posX, float posY) {
    data = value;
    size = 20 + (value % 30); // Taille entre 20 et 50
    x = posX;
    y = posY;
    oscillationPhase = ofRandom(0, TWO_PI);
    next = nullptr;
}

// =================== Implémentation de LinkedList ===================
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

void LinkedList::insertAtHead(int value) {
    Node* newNode = new Node(value, 100, ofGetHeight() / 2);
    newNode->next = head;
    head = newNode;
    if (!tail) tail = head;
}

void LinkedList::insertAtTail(int value) {
    Node* newNode = new Node(value, 100, ofGetHeight() / 2);
    if (!tail) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

void LinkedList::deleteHead() {
    if (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (!head) tail = nullptr;
    }
}

void LinkedList::deleteTail() {
    if (!head) return;
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }
    Node* temp = head;
    while (temp->next && temp->next != tail) {
        temp = temp->next;
    }
    delete tail;
    tail = temp;
    tail->next = nullptr;
}

void LinkedList::update(float amplitude) {
    Node* current = head;
    float xOffset = 100;
    while (current) {
        current->x = xOffset;
        current->y = (ofGetHeight() / 2) + amplitude * sin(ofGetElapsedTimef() + current->oscillationPhase);
        xOffset += 80;
        current = current->next;
    }
}

void LinkedList::draw() {
    Node* current = head;
    while (current) {
        if (current->next) {
            ofSetColor(255);
            ofDrawLine(current->x, current->y, current->next->x, current->next->y);
        }
        ofSetColor(100, 200, 255);
        ofDrawCircle(current->x, current->y, current->size);
        ofSetColor(0);
        ofDrawBitmapString(ofToString(current->data), current->x - 5, current->y + 5);
        current = current->next;
    }
}

// =================== Implémentation de ofApp ===================
void ofApp::setup() {
    ofSetFrameRate(60);
    oscillationAmplitude = 10;
    scrollX = 0;
}

void ofApp::update() {
    list.update(oscillationAmplitude);
}

void ofApp::draw() {
    ofTranslate(scrollX, 0);
    list.draw();
}

void ofApp::keyPressed(int key) {
    if (key == 'q') list.insertAtHead(ofRandom(10, 99));
    if (key == 'w') list.insertAtTail(ofRandom(10, 99));
    if (key == 'a') list.deleteHead();
    if (key == 's') list.deleteTail();
    if (key == 'z') oscillationAmplitude += 2;
    if (key == 'x') oscillationAmplitude = max(0.0f, oscillationAmplitude - 2);
    if (key == OF_KEY_LEFT) scrollX += 20;
    if (key == OF_KEY_RIGHT) scrollX -= 20;
}
