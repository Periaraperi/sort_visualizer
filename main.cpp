#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <cmath>
#include <algorithm>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int getRand()
{
    return rand()%255;
}

void reset(std::vector<int>& nums, std::vector<int>& heights, int blocks_area_height)
{
    nums.clear();
    heights.clear();
    for(int i=1; i<=300; ++i) {
        nums.push_back((rand()%100)+1);
        //nums.push_back(i);
    }
    int max_elem = *max_element(nums.begin(),nums.end());
    for(int i=0; i<nums.size(); ++i)
        heights.push_back(blocks_area_height*nums[i]/max_elem);

}

bool bubble(std::vector<int>& nums, std::vector<int>& heights)
{
    for(int i=0; i<nums.size()-1; ++i) {
        for(int j=i; j+1<nums.size(); ++j) {
            if(nums[j]>nums[j+1]) {
                std::swap(nums[j],nums[j+1]);
                std::swap(heights[j],heights[j+1]);
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    if(SDL_Init(SDL_INIT_EVERYTHING)<0) {
        std::cout << "Failed to initialise SDL subsystems " << SDL_GetError() << '\n';
        return -1;
    }
    int window_width = 32*40;
    int window_height = 32*30;
    SDL_Window* window = SDL_CreateWindow("title",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                                 window_width,window_height,SDL_WINDOW_SHOWN); 

    if(window==nullptr) {
        std::cout << "Failed to create window " << SDL_GetError() << '\n';
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer==nullptr) {
        std::cout << "Failed to create Renderer " <<  SDL_GetError() << '\n';
        return -1;
    }

    std::vector<int> nums;
    std::vector<SDL_Color> colors;
    std::vector<int> heights;
    SDL_Rect blocks_area = {0,0,window_width,(int)(window_height*0.75f)};
    reset(nums,heights,blocks_area.h);
    float outer_block_width = (float)window_width / (int)nums.size();
    
    SDL_FRect block;
    block.y = 0;
    block.w = outer_block_width;
    
    for(int i=0; i<nums.size(); ++i) 
        colors.push_back({(uint8_t)getRand(),(uint8_t)getRand(),(uint8_t)getRand(),255});

    SDL_Color background_color = {10,0,0,255};

    bool sorted = false;
    bool swapped = false;
    bool start = false;

    bool running = 1;
    SDL_Event ev;
    while(running) {
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN: {
                    if(ev.key.keysym.sym==SDLK_s) {
                        start = true;
                    } else if(ev.key.keysym.sym==SDLK_r) {
                        reset(nums,heights,blocks_area.h);
                        start = false;
                        sorted = false;
                        swapped = false;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer,background_color.r,background_color.g,background_color.b,255);
        SDL_RenderClear(renderer);

        if(start) {
            if(!sorted) {
                swapped = bubble(nums,heights);
                if(!swapped) 
                    sorted = true;
            }
        }

        for(int i=0; i<nums.size(); ++i) {
            //SDL_SetRenderDrawColor(renderer,colors[i].r,colors[i].g,colors[i].b,255);
            SDL_SetRenderDrawColor(renderer,100,200,200,255);
            block.x = i*outer_block_width;
            block.h = heights[i];
            SDL_RenderFillRectF(renderer,&block);
        }
        
        //SDL_RenderCopy(renderer,nullptr,nullptr,nullptr);
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}