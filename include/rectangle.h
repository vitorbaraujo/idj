#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    private:
        int m_x, m_y;
        int m_w, m_h;

    public:
        Rectangle(int x = 0, int y = 0, int w = 0, int h = 0);

        int get_x();
        int get_y();
        int get_w();
        int get_h();
        bool is_inside(int mouse_x, int mouse_y);
};

#endif
