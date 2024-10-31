#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <ostream>

#include "vector3.hpp"

class Matrix4 {
    public:
        Matrix4();
        ~Matrix4();

        void set_identity();
        void set_scale(Vector3 scale);
        void set_translation(Vector3 translation);

        void set_rotation_x(float angle);
        void set_rotation_y(float angle);
        void set_rotation_z(float angle);

        void operator *=(const Matrix4& other) {
            Matrix4 result;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < 4; k++) {
                        result.mat[i][j] += mat[i][k] * other.mat[k][j];
                    }
                }
            }
            *this = result;
        }
        
        friend auto operator<<(std::ostream& os, const Matrix4& m) -> std::ostream& {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    os << m.mat[i][j] << " ";
                }
                os << std::endl;
            }
            return os;
        }

        float mat[4][4] = {};
};

#endif // MATRIX4_HPP