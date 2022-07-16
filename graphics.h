#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Graphics {
public:
    static void init_graphics(std::string title, int width, int height);
    static Graphics* get_instance();
    static bool is_initialised();
    static void release();

    void set_background_color(SDL_Color color); 
    void clear_buffer();
    void render_present();
    void render_rect(SDL_Rect rect, SDL_Color rect_color, bool filled);
    void render_rectf(SDL_FRect rect, SDL_Color rect_color, bool filled);

    void window_resize(int h, int w);

    int get_width();
    int get_height();

private:
    static Graphics* m_instance;
    static bool m_initialised;

    int m_width;
    int m_height;
    std::string m_title;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    Graphics(std::string title, int width, int height);
    ~Graphics();

    bool init();
};