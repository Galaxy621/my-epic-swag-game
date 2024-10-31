#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <cmath>

#define v4_unpack(v) v.x, v.y, v.z, v.w

class Vector4 {
    public:
        Vector4() {};
        Vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {};
        ~Vector4() {};

        float get_magnitude() {
            return sqrt(x * x + y * y + z * z + w * w);
        };

        Vector4 normalise() {
            float magnitude = get_magnitude();
            return Vector4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
        };

        Vector4 operator+(const Vector4& other) {
            return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        };

        Vector4 operator-(const Vector4& other) {
            return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        };

        Vector4 operator*(const Vector4& other) {
            return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
        };

        Vector4 operator/(const Vector4& other) {
            return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
        };

        Vector4 operator*(const float& scalar) {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        };

        Vector4 operator/(const float& scalar) {
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        };

        float x = 0;
        float y = 0;
        float z = 0;
        float w = 0;

};

#endif // VECTOR4_HPP