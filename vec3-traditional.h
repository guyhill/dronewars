#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class Vec3 {
private:
    float x, y, z, w;
public:
    Vec3() {}
    Vec3(float x, float y, float z): x(x), y(y), z(z), w(0.0f) {}
    
    // Accessor functions
    float getx() {
        return x;
    }
    float gety() {
        return y;
    }
    float getz() {
        return z;
    }

    // Unary operators
    Vec3 &operator+() {
        return *this;
    }

    Vec3 operator-() {
        return Vec3(-x, -y, -z);
    }

    Vec3 &operator+=(const Vec3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3 &operator-=(const Vec3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vec3 &operator*=(const float c) {
        x *= c;
        y *= c;
        z *= c;
        return *this;
    }
    
    Vec3 &operator/=(const float c) {
        x /= c;
        y /= c;
        z /= c;
        return *this;
    }
    
    // Binary operators
    Vec3 operator+(const Vec3 &v) {
        Vec3 result = *this;
        return result += v;
    }
    
    Vec3 operator-(const Vec3 &v) {
        Vec3 result = *this;
        return result -= v;
    }
    
    Vec3 operator*(const float c) {
        Vec3 result = *this;
        return result *= c;
    }
    
    Vec3 operator/(const float c) {
        Vec3 result = *this;
        return result /= c;
    }
    
    // Friends
    // Geometric functions
    friend float inner(const Vec3 &u, const Vec3 &v);
    friend Vec3 cross(const Vec3 &u, const Vec3 &v);
    friend float length(const Vec3 &u);
    friend float triple(const Vec3 &u, const Vec3 &v, const Vec3 &w);

    // Stream operators
    friend std::ostream &operator<<(std::ostream &s, const Vec3 &u);
    friend std::istream &operator>>(std::istream &s, Vec3 &u);
};

inline float inner(const Vec3 &u, const Vec3 &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}   

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

inline float length(const Vec3 &u) {
    return sqrt(inner(u, u));
}

inline float triple(const Vec3 &u, const Vec3 &v, const Vec3 &w) {
    return inner(u, cross(v, w));
}

inline std::ostream &operator<<(std::ostream &s, const Vec3 &u) {
    s << u.x << " " << u.y << " " << u.z;
    return s;
}

inline std::istream &operator>>(std::istream &s, Vec3 &u) {
    s >> u.x >> u.y >> u.z;
    return s;
}

#endif