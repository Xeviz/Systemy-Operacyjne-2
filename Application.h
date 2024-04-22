//
// Created by linuxarc on 06.04.24.
//

#ifndef UNTITLED_APPLICATION_H
#define UNTITLED_APPLICATION_H

#include <vector>
#include <pthread.h>
#include <GLFW/glfw3.h>
#include <csignal>
#include "Ball.h"
#include "Square.h"

class Application {

private:
    struct BallThreadData {
        bool* keepGenerating;
        Ball* ball;
        pthread_t thread;
    };
    struct GeneratorThreadData {
        bool* keepGenerating;
        pthread_t thread;
    };
    struct SquareThreadData {
        bool* keepGenerating;
        Square* square;
        pthread_t thread;
    };


    static void* ballThreadRoutine(void* arg);
    static void* generatorThreadRoutine(void* arg);
    static void* squareThreadRoutine(void* arg);
    bool keepGenerating = true;

public:
    Application();
    ~Application();
    static std::vector<BallThreadData*> ballThreads;
    void startApplication();


};


#endif //UNTITLED_APPLICATION_H
