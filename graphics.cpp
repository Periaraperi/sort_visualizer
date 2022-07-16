#include "Graphics.h"

bool Graphics::m_initialised = false;
Graphics* Graphics::m_instance = nullptr;

Graphics::Graphics(std::string title, int width, int height)
:m_title(title), m_width(width), m_height(height)
{
    m_initialised = init();
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Graphics::release()
{
    delete m_instance;
}

void Graphics::init_graphics(std::string title, int width, int height)
{
    if(m_instance!=nullptr)
        return;
    m_instance = new Graphics(title,width,height);
}

bool Graphics::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) {
        std::cout << "Failed to initialise SDL subsystems " << SDL_GetError() << '\n';
        return 0;
    }

    m_window = SDL_CreateWindow(m_title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                                m_width,m_height,SDL_WINDOW_SHOWN); 

    if(m_window==nullptr) {
        std::cout << "Failed to create window " << SDL_GetError() << '\n';
        return 0;
    }
    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
    if(m_renderer==nullptr) {
        std::cout << "Failed to create Renderer " <<  SDL_GetError() << '\n';
        return 0;
    }

    return 1; // success
}

Graphics* Graphics::get_instance()
{
    return m_instance;
}

bool Graphics::is_initialised()
{
    return m_initialised;
}

void Graphics::set_background_color(SDL_Color color)
{
    SDL_SetRenderDrawColor(m_renderer,color.r,color.g,color.b,color.a);
}

void Graphics::clear_buffer()
{
    SDL_RenderClear(m_renderer);
}

void Graphics::render_present()
{
    SDL_RenderPresent(m_renderer);
}

void Graphics::render_rect(SDL_Rect rect, SDL_Color rect_color, bool filled)
{
    set_background_color(rect_color);
    if(filled)
        SDL_RenderFillRect(m_renderer,&rect);    
    else
        SDL_RenderDrawRect(m_renderer,&rect);
}

void Graphics::render_rectf(SDL_FRect rect, SDL_Color rect_color, bool filled)
{
    set_background_color(rect_color);
    if(filled)
        SDL_RenderFillRectF(m_renderer,&rect);    
    else
        SDL_RenderDrawRectF(m_renderer,&rect);
}

void Graphics::window_resize(int w, int h)
{
    m_width = w;
    m_height = h;
}

int Graphics::get_width()
{
    return m_width;
}

int Graphics::get_height()
{
    return m_height;
}