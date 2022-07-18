#include <iostream>
#include <SDL.h>
#include "palette.h"
#include "Snake.h"

#define SQUARE 25
#define FPS 60

static int WIDTH = 800;
static int HEIGHT = 600;

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
	const int MAP_WIDTH = 800;
	const int MAP_HEIGHT = 600;
	SDL_Rect map = {(WIDTH / 2) - (MAP_WIDTH / 2), (HEIGHT / 2) - (MAP_HEIGHT / 2), MAP_WIDTH, MAP_HEIGHT};
	Snake snake((WIDTH / 2) - (MAP_WIDTH / 2), (HEIGHT / 2) - (MAP_HEIGHT / 2));

	bool quit = false;
	while (!quit) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_WINDOWEVENT:
					switch(event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							WIDTH = event.window.data1;
							HEIGHT = event.window.data2;
							map = {(WIDTH / 2) - (MAP_WIDTH / 2), (HEIGHT / 2) - (MAP_HEIGHT / 2), MAP_WIDTH, MAP_HEIGHT};

							snake.set_x((WIDTH / 2) - (MAP_WIDTH / 2));
							snake.set_y((HEIGHT / 2) - (MAP_HEIGHT / 2));
							break;
						default:
							break;
					}
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_w:
							snake.set_direction(0, -1);
							break;
						case SDLK_a:
							snake.set_direction(-1, 0);
							break;
						case SDLK_s:
							snake.set_direction(0, 1);
							break;
						case SDLK_d:
							snake.set_direction(1, 0);
							break;
						default:
							break;
					}
				default:
					break;
			}
		}
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, palette[0].r, palette[0].g, palette[0].b, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, palette[1].r, palette[1].g, palette[1].b, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &map);

		SDL_SetRenderDrawColor(renderer, palette[2].r, palette[2].g, palette[2].b, SDL_ALPHA_OPAQUE);
		for (int x = (WIDTH / 2) - (MAP_WIDTH / 2); x <= (WIDTH / 2) + (MAP_WIDTH / 2); x += SQUARE) {
			SDL_RenderDrawLine(renderer, x, (HEIGHT / 2) - (MAP_HEIGHT / 2), x, (HEIGHT / 2) + (MAP_HEIGHT / 2));
		}
		for (int y = (HEIGHT / 2) - (MAP_HEIGHT / 2); y <= (HEIGHT / 2) + (MAP_HEIGHT / 2); y += SQUARE) {
			SDL_RenderDrawLine(renderer, (WIDTH / 2) - (MAP_WIDTH / 2), y, (WIDTH / 2) + (MAP_WIDTH / 2), y);
		}

		if (snake.get_x() < ((WIDTH / 2) + (MAP_WIDTH / 2) - SQUARE) && snake.get_y() < ((HEIGHT / 2) + (MAP_HEIGHT / 2) - SQUARE)) {
			snake.update();
		}
		snake.render(renderer, palette[3]);
		SDL_RenderPresent(renderer);
		SDL_Delay(FPS);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}
