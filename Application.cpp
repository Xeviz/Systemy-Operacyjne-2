//
// Created by linuxarc on 06.04.24.
//

#include "Application.h"
#include "Ball.h"
#include "Square.h"
#include <iostream>
#include <pthread.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <mutex>
#include <random>
std::vector<Application::BallThreadData*> Application::ballThreads;
std::mutex mtx;
std::random_device rd;
std::mt19937 gen(rd());



void Application::startApplication() {

    if (!glfwInit()) {
        std::cerr << "Nie można zainicjować GLFW" << std::endl;
        return;
    }

    GLFWwindow* window = glfwCreateWindow(700, 700, "balls", nullptr, nullptr);
    if (!window) {
        std::cerr << "Nie można utworzyć okna GLFW" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    pthread_t generatorThread = 0;
    pthread_t squareThread = 0;
    auto* square = new Square(-0.7, 0.0, 0.35, 0.25, gen);

    GeneratorThreadData generatorThreadData{&keepGenerating, generatorThread};
    SquareThreadData squareThreadData{&keepGenerating, square, squareThread};

    pthread_create(&generatorThreadData.thread, nullptr, generatorThreadRoutine, &generatorThreadData);
    pthread_create(&squareThreadData.thread, nullptr, squareThreadRoutine, &squareThreadData);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            keepGenerating = false;
        }
        for (auto& ballThreadData : ballThreads) {
            ballThreadData->ball->drawBall();
        }
        square->drawSquare();
        glfwSwapBuffers(window);

        if(!keepGenerating && ballThreads.empty()) {
            break;
        }



    }

    pthread_join(generatorThreadData.thread, nullptr);
    pthread_join(squareThreadData.thread, nullptr);

    std::cout << "rysowanie zakonczone" << std::endl;
    glfwTerminate();
}

void *Application::ballThreadRoutine(void* arg) {
    auto* data = static_cast<BallThreadData*>(arg);
    std::cout << "jestem piłeczką " << data->ball->getNumber() << std::endl;
    while (data->ball->getTimeToLive() > 0) {
        data->ball->moveBall();
        data->ball->drawBall();
        glfwPostEmptyEvent();
        usleep(10000);
    }
    mtx.lock();
    std::cout << "Wątek pileczki o numerze " << data->ball->getNumber() << " zakończył pracę." << std::endl;
    auto it = std::find_if(ballThreads.rbegin(), ballThreads.rend(),
                           [data](const BallThreadData* ballThreadData) { return ballThreadData == data; });
    if (it != ballThreads.rend()) {
        ballThreads.erase(std::next(it).base());
    }
    mtx.unlock();
    delete data;
    pthread_exit(nullptr);
}

void *Application::generatorThreadRoutine(void* arg) {
    auto* data = static_cast<GeneratorThreadData*>(arg);
    std::uniform_real_distribution<float> delay_distribution(1.0f, 2.5f);
    float currentDelay = delay_distribution(gen);
    double lastCheckedTime = glfwGetTime();
    int curNumber = 1;


    while (*data->keepGenerating){

        if(glfwGetTime()>lastCheckedTime+currentDelay){
            mtx.lock();
            Ball* newBall = new Ball(0.0, -0.8, curNumber, 0.1, gen);
            pthread_t ballThread = 0;
            auto* newBallThreadData = new BallThreadData{newBall, ballThread};
            pthread_create(&newBallThreadData->thread, nullptr, ballThreadRoutine, newBallThreadData);
            ballThreads.emplace_back(newBallThreadData);
            mtx.unlock();

            currentDelay = delay_distribution(gen);
            lastCheckedTime = glfwGetTime();
            curNumber++;

            glfwPostEmptyEvent();
        }
    }
    std::cout << "watek generujacy zakonczony" << std::endl;
    pthread_exit(nullptr);
}

void *Application::squareThreadRoutine(void* arg) {
    auto* data = static_cast<SquareThreadData*>(arg);
    while (*data->keepGenerating || !ballThreads.empty()) {
        data->square->moveSquare();
        glfwPostEmptyEvent();
        usleep(10000);
    }
    std::cout << "watek prostokata zakonczony" << std::endl;
    pthread_exit(nullptr);
}

Application::Application() = default;

Application::~Application() = default;