#pragma once
#include "ofMain.h"

// Classe pour un nœud de la liste chaînée
class Node {
public:
    int data;
    float x, y;
    float size;
    float oscillationPhase;
    Node* next;

    Node(int value, float posX, float posY);
};

// Classe pour la liste chaînée
class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList();
    void insertAtHead(int value);
    void insertAtTail(int value);
    void deleteHead();
    void deleteTail();
    void draw();
    void update(float amplitude);
};

class ofApp : public ofBaseApp {
public:
    LinkedList list;
    float oscillationAmplitude;
    float scrollX;

    void setup();
    void update();
    void draw();
    void keyPressed(int key);
};
