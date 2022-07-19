#include <iostream>
#include <SDL.h>
#include "palette.h"
#include "Snake.h"

#define SQUARE 25
#define FPS 120

static int WIDTH = 800;
static int HEIGHT = 600;

const int MAP_WIDTH = 800;
const int MAP_HEIGHT = 600;

static int LBOUND_WIDTH = (WIDTH / 2) - (MAP_WIDTH / 2); 
static int LBOUND_HEIGHT = (HEIGHT / 2) - (MAP_HEIGHT / 2); 

static int UBOUND_WIDTH = (WIDTH / 2) + (MAP_WIDTH / 2); 
static int UBOUND_HEIGHT = (HEIGHT / 2) + (MAP_HEIGHT / 2); 

bool QUIT = false, PAUSED = false;
SDL_Rect MAP = {LBOUND_WIDTH, LBOUND_HEIGHT, MAP_WIDTH, MAP_HEIGHT};
Snake SNAKE(0, 0);
void update(SDL_Event *event) {
while(SDL_PollEvent(event)) {
			switch(event->type) {
				case SDL_QUIT:
					QUIT = true;
					break;
				case SDL_WINDOWEVENT:
					switch(event->window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							WIDTH = event->window.data1;
							HEIGHT = event->window.data2;
							LBOUND_WIDTH = (WIDTH / 2) - (MAP_WIDTH / 2); 
							LBOUND_HEIGHT = (HEIGHT / 2) - (MAP_HEIGHT / 2); 
							UBOUND_WIDTH = (WIDTH / 2) + (MAP_WIDTH / 2); 
							UBOUND_HEIGHT = (HEIGHT / 2) + (MAP_HEIGHT / 2); 

							MAP = {LBOUND_WIDTH, LBOUND_HEIGHT, MAP_WIDTH, MAP_HEIGHT};

							SNAKE.set_x(LBOUND_WIDTH);
							SNAKE.set_y(LBOUND_HEIGHT);
							break;
						default:
							break;
					}
				case SDL_KEYDOWN:
					switch(event->key.keysym.sym) {
						case SDLK_w:
							if (!SNAKE.isDown()) {
								SNAKE.set_direction(0, -1);
							}
							break;
						case SDLK_a:
							if (!SNAKE.isRight()) {
								SNAKE.set_direction(-1, 0);
							}
							break;
						case SDLK_s:
							if (!SNAKE.isUp()) {
								SNAKE.set_direction(0, 1);
							}
							break;
						case SDLK_d:
							if (!SNAKE.isLeft()) {
								SNAKE.set_direction(1, 0);
							}
							break;
						case SDLK_SPACE:
							PAUSED = !PAUSED;
							break;
						default:
							break;
					}
				default:
					break;
			}
		}
}

void render(SDL_Renderer *renderer) {
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, palette[0].r, palette[0].g, palette[0].b, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, palette[1].r, palette[1].g, palette[1].b, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &MAP);

		SDL_SetRenderDrawColor(renderer, palette[2].r, palette[2].g, palette[2].b, SDL_ALPHA_OPAQUE);
		for (int x = LBOUND_WIDTH; x <= UBOUND_WIDTH; x += SQUARE) {
			SDL_RenderDrawLine(renderer, x, LBOUND_HEIGHT, x, UBOUND_HEIGHT);
		}
		for (int y = LBOUND_HEIGHT; y <= UBOUND_HEIGHT; y += SQUARE) {
			SDL_RenderDrawLine(renderer, LBOUND_WIDTH, y, UBOUND_WIDTH, y);
		}

		SNAKE.render(renderer, palette[3]);
		SDL_RenderPresent(renderer);
}

void render_death_scene(std::string msg) {
	std::cout << msg << std::endl;
}

int main() {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 1;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL window and renderer: %s", SDL_GetError());
		return 1;
	}
	SDL_SetWindowTitle(window, "SNAKE");

	while (!QUIT) {
		update(&event);

		if (!SNAKE.foodExists()) {
			SNAKE.generate_food(LBOUND_WIDTH / SQUARE, LBOUND_HEIGHT / SQUARE, (UBOUND_WIDTH - SQUARE) / SQUARE, (UBOUND_HEIGHT - SQUARE) / SQUARE);
		}
		if (SNAKE.get_x() < LBOUND_WIDTH || SNAKE.get_x() > (UBOUND_WIDTH - SQUARE) || SNAKE.get_y() < LBOUND_HEIGHT || SNAKE.get_y() > (UBOUND_HEIGHT - SQUARE)) {
			render_death_scene("YOU HIT THE WALL");
			PAUSED = true;
		}
		SNAKE.eat();
		if (!PAUSED) {
			SNAKE.update();
			if (SNAKE.isDead()) {
				render_death_scene("YOU DIED");
				PAUSED = true;
			}
		}

		render(renderer);
		SDL_Delay(FPS);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	return 0;
}
