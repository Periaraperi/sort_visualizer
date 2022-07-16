#pragma once

#include "graphics.h"
#include "bubble_sort.h"

class Engine {
public:
    Engine(std::string title, int width, int height);
    ~Engine();
    void start();
private:
    bool m_running;
    Graphics* m_graphics;
    bool m_paused;
    int m_count;
    
    Bubble_Sort* m_bs;

    void update();
    void render();

};