#pragma once
#include <deque>

class Snake {
private:
	int m_x = 0, m_y = 0, m_dx = 1, m_dy = 0;
	std::deque<SDL_Rect> m_snake = {};
	bool m_foodExists = false;
	SDL_Rect m_food = {};
	bool m_up = false, m_down = false, m_left = false, m_right = true;
public:
	Snake(int x, int y);
	void set_x(int x);
	void set_y(int y);
	int get_x() const;
	int get_y() const;
	bool foodExists() const;

	void set_direction(int x, int y);
	bool isUp() const;
	bool isDown() const;
	bool isLeft() const;
	bool isRight() const;

	void generate_food(int lbound_width, int lbound_height, int ubound_width, int ubound_height);
	void eat();
	void grow();

	bool isDead() const;
	void update();
	void render(SDL_Renderer *renderer, SDL_Color palette) const ;
};
