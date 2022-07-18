#include <iostream>
#include <SDL.h>
#include "Snake.h"

#define SQUARE 25

Snake::Snake(int x, int y)
	: m_x(x), m_y(y) {}

void Snake::set_x(int x) {
	m_x = x;
}

void Snake::set_y(int y) {
	m_y = y;
}

int Snake::get_x() const {
	return m_x;
}

int Snake::get_y() const {
	return m_y;
}

void Snake::set_direction(int x, int y) {
	m_dx = x;
	m_dy = y;
}

void Snake::update() {
	m_x += m_dx * SQUARE;
	m_y += m_dy * SQUARE;
}

void Snake::render(SDL_Renderer *renderer, SDL_Color palette) const {
	SDL_SetRenderDrawColor(renderer, palette.r, palette.g, palette.b, SDL_ALPHA_OPAQUE); 
	SDL_Rect player = {m_x, m_y, SQUARE, SQUARE};
	SDL_RenderFillRect(renderer, &player);
}
