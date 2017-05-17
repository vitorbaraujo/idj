#include "collision.h"

bool Collision::is_colliding(Rectangle& a, Rectangle& b, double a_angle, double b_angle){
    a_angle = Utils::to_rad(a_angle);
    b_angle = Utils::to_rad(b_angle);

    Vector A[] = {  Vector( a.get_x(), a.get_y() + a.get_h() ),
                    Vector( a.get_x() + a.get_w(), a.get_y() + a.get_h() ),
                    Vector( a.get_x() + a.get_w(), a.get_y() ),
                    Vector( a.get_x(), a.get_y() )
    };
    Vector B[] = {  Vector( b.get_x(), b.get_y() + b.get_h() ),
                    Vector( b.get_x() + b.get_w(), b.get_y() + b.get_h() ),
                    Vector( b.get_x() + b.get_w(), b.get_y() ),
                    Vector( b.get_x(), b.get_y() )
    };

    for(auto& v : A){
        v = rotate(v - a.get_center(), a_angle) + a.get_center();
    }

    for(auto& v : B){
        v = rotate(v - b.get_center(), b_angle) + b.get_center();
    }

    Vector axes[] = { norm(A[0] - A[1]), norm(A[1] - A[2]), norm(B[0] - B[1]), norm(B[1] - B[2]) };

    for(auto& axis : axes){
        double P[4];

        for(int i = 0; i < 4; ++i)
            P[i] = dot(A[i], axis);

        double minA = *std::min_element(P, P + 4);
        double maxA = *std::max_element(P, P + 4);

        for(int i = 0; i < 4; ++i)
            P[i] = dot(B[i], axis);

        double minB = *std::min_element(P, P + 4);
        double maxB = *std::max_element(P, P + 4);

        if(maxA < minB || minA > maxB)
            return false;
    }

    return true;
}

double Collision::mag(const Vector& p){
    return sqrt(p.get_x() * p.get_x() + p.get_y() * p.get_y());
}

Vector Collision::norm(const Vector& p){
    return p * (1.f / mag(p));
}

double Collision::dot(const Vector& a, const Vector& b){
    return a.get_x() * b.get_x() + a.get_y() * b.get_y();
}

Vector Collision::rotate(const Vector& p, double angle) {
    double cs = cos(angle), sn = sin(angle);
    return Vector ( p.get_x() * cs - p.get_y() * sn, p.get_x() * sn + p.get_y() * cs );
}
