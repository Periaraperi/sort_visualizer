#pragma once

#include "bubble_sort.h"
#include "graphics.h"
#include <vector>
#include <algorithm>

class Bubble_Sort {
public:
    Bubble_Sort();
    ~Bubble_Sort();
    void algorithm_step();
    bool finished();
    void reset(int elem_count);
    void draw();
private:
    Graphics* m_graphics;
    SDL_Rect m_drawable_area;
    bool m_finished;
    bool m_swapped;
    float m_bar_width;
    int m_max_element;
    std::vector<int> m_nums;
    // iterators for bubble sort step
    int m_i;
    int m_j;
};