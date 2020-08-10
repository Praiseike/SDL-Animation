
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define WIDTH 1336
#define HEIGHT 760

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Event event;

bool isRunning = true;



typedef struct Image{
    SDL_Texture * texture;
    SDL_Rect dest,src;
};


void render(Image *ken)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,ken->texture,&ken->src,&ken->dest);
    SDL_RenderPresent(renderer);
}

void moveFrame(Image * ken)
{
    int frame = int((SDL_GetTicks() /100)% 8);
    ken->src.x = ken->src.w * frame;
}

void handleEvents()
{
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            isRunning = false;
        }
    }
}



int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Unable to init sdl\n");
        exit(1);
    }

    window = SDL_CreateWindow("my window",0,0,WIDTH,HEIGHT,SDL_WINDOW_RESIZABLE);
    if(!window)
    {
        printf("Error: %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        printf("Error: %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }


    Image * ken = new Image;
    SDL_Surface * image  = IMG_Load("assets/walking_ken.png");
    if(!image)
    {
        printf("Error: %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    ken->texture = SDL_CreateTextureFromSurface(renderer,image);
    SDL_QueryTexture(ken->texture,NULL,NULL,&ken->src.w,&ken->src.h);
    ken->dest.x =  WIDTH/2;
    ken->dest.y = HEIGHT/2;
    ken->src.w = 75;
    ken->dest.h = ken->src.h + 60;
    ken->dest.w = ken->src.w + 60;
    ken->src.x = 0;
    ken->src.y = 0;


    SDL_FreeSurface(image);

    SDL_SetRenderDrawColor(renderer,0xf3,0xf3,0xf3,0xff);

    while(isRunning)
    {
        render(ken);
        moveFrame(ken);
        handleEvents();
    }

    SDL_DestroyTexture(ken->texture);
    delete ken;     // farewell ken
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
