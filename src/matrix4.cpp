#include "matrix4.hpp"

Matrix4::Matrix4() {
    set_identity();
}

Matrix4::~Matrix4() {
}

void Matrix4::set_identity() {
    memset(mat, 0, sizeof(float) * 16);

    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;

}

void Matrix4::set_rotation_x(float angle) {
    mat[1][1] = cos(angle);
    mat[1][2] = -sin(angle);
    mat[2][1] = sin(angle);
    mat[2][2] = cos(angle);
}

void Matrix4::set_rotation_y(float angle) {
    mat[0][0] = cos(angle);
    mat[0][2] = sin(angle);
    mat[2][0] = -sin(angle);
    mat[2][2] = cos(angle);
}

void Matrix4::set_rotation_z(float angle) {
    mat[0][0] = cos(angle);
    mat[0][1] = -sin(angle);
    mat[1][0] = sin(angle);
    mat[1][1] = cos(angle);
}

void Matrix4::set_scale(Vector3 scale) {
    mat[0][0] = scale.x;
    mat[1][1] = scale.y;
    mat[2][2] = scale.z;
}

void Matrix4::set_translation(Vector3 translation) {
    mat[3][0] = translation.x;
    mat[3][1] = translation.y;
    mat[3][2] = translation.z;
}