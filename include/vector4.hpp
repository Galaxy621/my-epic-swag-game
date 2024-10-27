#ifndef VECTOR4_HPP
#define VECTOR4_HPP

class Vector4 {
    public:
        Vector4() {};
        Vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {};
        ~Vector4() {};

        float x = 0;
        float y = 0;
        float z = 0;
        float w = 0;

};

#endif // VECTOR4_HPP