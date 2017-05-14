#ifndef TIMER_H
#define TIMER_H

class Timer {
    private:
        double m_time;

    public:
        Timer();
        void update(double dt);
        void restart();
        double get();
};

#endif