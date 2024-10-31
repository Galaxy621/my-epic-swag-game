#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>
#define v3_unpack(v) v.x, v.y, v.z

class Vector3 {
    public:
        Vector3() {};
        Vector3(float x, float y, float z): x(x), y(y), z(z) {};
        ~Vector3() {};

        float get_magnitude() {
            return sqrt(x * x + y * y + z * z);
        };

        Vector3 normalise() {
            float magnitude = get_magnitude();
            return Vector3(x / magnitude, y / magnitude, z / magnitude);
        };

        Vector3 operator+(const Vector3& other) {
            return Vector3(x + other.x, y + other.y, z + other.z);
        };

        Vector3 operator-(const Vector3& other) {
            return Vector3(x - other.x, y - other.y, z - other.z);
        };

        Vector3 operator*(const Vector3& other) {
            return Vector3(x * other.x, y * other.y, z * other.z);
        };

        Vector3 operator/(const Vector3& other) {
            return Vector3(x / other.x, y / other.y, z / other.z);
        };

        Vector3 operator*(const float& scalar) {
            return Vector3(x * scalar, y * scalar, z * scalar);
        };

        Vector3 operator/(const float& scalar) {
            return Vector3(x / scalar, y / scalar, z / scalar);
        };

        float x = 0;
        float y = 0;
        float z = 0;

};

#endif // VECTOR3_HPP