#ifndef VECTOR3_H
#define VECTOR3_H


class Vector3
{
    public:
        float x;
        float y;
        float z;

        Vector3();
        Vector3(float x, float y, float z);
        Vector3 UnitVector();
        Vector3 Sum(const Vector3 &v);
        Vector3 Produt(float factor);
        virtual ~Vector3();

    protected:

    private:
};

#endif // VECTOR3_H
