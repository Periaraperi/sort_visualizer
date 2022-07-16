#include "bubble_sort.h"

Bubble_Sort::Bubble_Sort()
{
    m_graphics = Graphics::get_instance();
    m_drawable_area = {0,0,m_graphics->get_width(),(int)(m_graphics->get_height()*0.80f)};
    reset(200);
}

Bubble_Sort::~Bubble_Sort()
{
    m_graphics = nullptr;
}

void Bubble_Sort::reset(int elem_count)
{
    m_nums.clear();
    for(int i=0; i<elem_count; ++i) {
        m_nums.push_back(rand()%1000 + 5);
    }
    m_max_element = *max_element(m_nums.begin(),m_nums.end());
    m_i = 0;
    m_j = 0;
    m_bar_width = (float)m_graphics->get_width() / (int)m_nums.size();
    m_swapped = false;
    m_finished = false;
}

// at each frame we need to perform only one step
// m_i, m_j will store state of algorithm for next step
void Bubble_Sort::algorithm_step()
{
    if(m_i<m_nums.size()) {
        if(m_j+1<m_nums.size()-m_i) {
            if(m_nums[m_j]>m_nums[m_j+1]) {
                std::swap(m_nums[m_j],m_nums[m_j+1]);
                m_swapped = true;
            }
            ++m_j;
            return;
        }
        if(!m_swapped) {
            m_i = m_nums.size();
            m_j = m_nums.size();
            m_finished = true;
            return;
        }
        m_swapped = false;
        ++m_i;
        m_j = 0;
    } else {
        m_finished = true;
    }
}

void Bubble_Sort::draw()
{
    SDL_FRect bar = {0,0,0,0};
    bar.w = m_bar_width;
    for(int i=0; i<m_nums.size(); ++i) {
        bar.x = i*m_bar_width;
        bar.h = m_drawable_area.h*m_nums[i]/m_max_element;
        if(i==m_j)
            m_graphics->render_rectf(bar,{255,0,0,255},true);
        else if(i>=m_nums.size()-m_i)
            m_graphics->render_rectf(bar,{0,255,0,255},true);
        else
            m_graphics->render_rectf(bar,{255,255,255,255},true);
    }
}

bool Bubble_Sort::finished()
{
    return m_finished;
}
