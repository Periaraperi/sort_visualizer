#include "engine.h"

int main(int argc, char** argv) 
{
    Engine* e = new Engine("test",1280,720);
    e->start();
    delete e;
    return 0;
}