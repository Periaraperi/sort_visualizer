#include "engine.h"

Engine::Engine(std::string title, int width, int height)
{
    m_running = false;
    Graphics::init_graphics(title,width,height);
    if(Graphics::is_initialised()) {
        m_graphics = Graphics::get_instance();
        m_running = true;
        m_bs = new Bubble_Sort();
        m_paused = true;
        m_count = 150;
    }
}

Engine::~Engine()
{
    delete m_bs;
    m_graphics->release();
}

void Engine::start()
{
    SDL_Event ev;
    while(m_running) {
        while(SDL_PollEvent(&ev)) {
            if(ev.type==SDL_QUIT) {
                m_running = false;
            } else if(ev.type==SDL_KEYUP) {
                if(ev.key.keysym.sym==SDLK_r) { // reset numbers
                    m_bs->reset(m_count);
                    m_paused = true;
                } else if(ev.key.keysym.sym==SDLK_s) {
                    m_paused = false;
                } else if(ev.key.keysym.sym==SDLK_p) {
                    m_paused = true;
                } else if(ev.key.keysym.sym==SDLK_UP) {
                    m_count += 20;
                    m_count = std::min(m_count,250);
                    m_bs->reset(m_count);
                } else if(ev.key.keysym.sym==SDLK_DOWN) {
                    m_count -= 20;
                    m_count = std::max(m_count,20);
                    m_bs->reset(m_count);
                }
            }
        }
        update();
        render();
    }
}

void Engine::update()
{
    if(!m_paused) {
        if(!m_bs->finished())
            m_bs->algorithm_step();
    }
}

void Engine::render()
{
    m_graphics->set_background_color({0,0,0,255});
    m_graphics->clear_buffer();
    
    m_bs->draw();
    
    m_graphics->render_present();
}