#pragma once
#include <vector>

class Snake {
private:
	int m_x, m_y, m_dx = 1, m_dy;
	std::vector<SDL_Rect> m_snake;
public:
	Snake(int x, int y);
	void set_x(int x);
	void set_y(int x);
	int get_x() const;
	int get_y() const ;

	void set_direction(int x, int y);
	void update();
	void render(SDL_Renderer *renderer, SDL_Color palette) const ;
};
