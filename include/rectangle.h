#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    private:
        double m_x, m_y;
        double m_w, m_h;

    public:
        Rectangle(double x = 0, double y = 0, double w = 0, double h = 0);

        double get_x();
        double get_y();
        double get_w();
        double get_h();
        bool is_inside(double mouse_x, double mouse_y);
};

#endif
