#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_RADIUS = 20;
const int BALL_SPEED = 5;

int main(int argc, char* argv[]) {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Bouncing Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    //Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //Ball position and velocity
    int ballX = SCREEN_WIDTH / 2;
    int ballY = SCREEN_HEIGHT / 2;
    int ballVelX = BALL_SPEED;
    int ballVelY = BALL_SPEED;

    bool running = true;
    SDL_Event event;

    //Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        //Update ball position
        ballX += ballVelX;
        ballY += ballVelY;

        //Bounce off walls
        if (ballX - BALL_RADIUS < 0 || ballX + BALL_RADIUS > SCREEN_WIDTH) {
            ballVelX = -ballVelX;
        }
        if (ballY - BALL_RADIUS < 0 || ballY + BALL_RADIUS > SCREEN_HEIGHT) {
            ballVelY = -ballVelY;
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Draw ball
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int w = -BALL_RADIUS; w < BALL_RADIUS; w++) {
            for (int h = -BALL_RADIUS; h < BALL_RADIUS; h++) {
                if (w * w + h * h <= BALL_RADIUS * BALL_RADIUS) {
                    SDL_RenderDrawPoint(renderer, ballX + w, ballY + h);
                }
            }
        }

        //Update screen
        SDL_RenderPresent(renderer);

        //Cap frame rate
        SDL_Delay(16); // ~60 FPS
    }

    //Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}