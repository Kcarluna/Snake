#include <iostream>
#include <SDL.h>
#include <random>
#include "Snake.h"

#define SQUARE 25

Snake::Snake(int x, int y)
	: m_x(x), m_y(y) {
		m_snake.push_front({m_x, m_y, SQUARE, SQUARE});
	}

void Snake::set_x(int x) {
	m_snake[0].x = x;
}

void Snake::set_y(int y) {
	m_snake[0].y = y;
}

int Snake::get_x() const {
	return m_snake[0].x;
}

int Snake::get_y() const {
	return m_snake[0].y;
}

bool Snake::foodExists() const {
	return m_foodExists;
}

void Snake::set_direction(int x, int y) {
	if (x == 0 && y == -1) {
		m_up = true;
		m_down = false;
		m_left = false;
		m_right = false;
	} else if (x == 0 && y == 1) {
		m_up = false;
		m_down = true;
		m_left = false;
		m_right = false;
	} else if (x == -1 && y == 0) {
		m_up = false;
		m_down = false;
		m_left = true;
		m_right = false;
	} else if (x == 1 && y == 0) {
		m_up = false;
		m_down = false;
		m_left = false;
		m_right = true;
	}
	m_dx = x;
	m_dy = y;
}

bool Snake::isUp() const {
	return m_up;
}
bool Snake::isDown() const {
	return m_down;
}
bool Snake::isLeft() const {
	return m_left;
}
bool Snake::isRight() const {
	return m_right;
}

void Snake::generate_food(int lbound_width, int lbound_height, int ubound_width, int ubound_height) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rand_x(lbound_width, ubound_width);
	std::uniform_int_distribution<std::mt19937::result_type> rand_y(lbound_height, ubound_height);
	int x = rand_x(rng) * SQUARE; 
	int y = rand_y(rng) * SQUARE; 
	m_food = {x, y, SQUARE, SQUARE};
	m_foodExists = true;
}

void Snake::eat() {
	if (m_snake[0].x == m_food.x && m_snake[0].y == m_food.y) {
		grow();
		m_foodExists = false;
	}
}

void Snake::grow() {
	m_snake[0].x += m_dx * SQUARE;
	m_snake[0].y += m_dy * SQUARE;
	m_snake.push_front({m_snake[0].x, m_snake[0].y, SQUARE, SQUARE});
}


bool Snake::isDead() const {
	for (int i = 1; i < m_snake.size(); i++) {
		if (m_snake[0].x == m_snake[i].x && m_snake[0].y == m_snake[i].y) {
			return true;
		}
	}
	return false;
}

void Snake::update() {
	for (int i = m_snake.size() - 1; i > 0; i--) {
		m_snake[i] = m_snake[i - 1];
	}
	m_snake[0].x += m_dx * SQUARE;
	m_snake[0].y += m_dy * SQUARE;
}

void Snake::render(SDL_Renderer *renderer, SDL_Color palette) const {
	SDL_SetRenderDrawColor(renderer, palette.r, palette.g, palette.b, SDL_ALPHA_OPAQUE); 
	for (auto &segment: m_snake) {
		SDL_RenderFillRect(renderer, &segment);
	}
	SDL_RenderFillRect(renderer, &m_food);
}
