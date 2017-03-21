#ifndef RECT_H
#define RECT_H

class Rect {
	private:
		float m_x, m_y;
		float m_w, m_h;

	public:
		Rect(float x = 0, float y = 0, float w = 0, float h = 0);

		float get_x();
		float get_y();
		float get_w();
		float get_h();
		bool is_inside(float mouse_x, float mouse_y);

};

#endif