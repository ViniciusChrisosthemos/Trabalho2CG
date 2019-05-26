#ifndef CAMERA_H
#define CAMERA_H
#include <Vector3.h>

class Camera
{
    public:
        Vector3* observer;
        Vector3* target;
        float angle;

        Camera(Vector3* observer, Vector3* target);
        void SetObserver(Vector3* observer, float angle);
        void SetTarget(Vector3* target);
        virtual ~Camera();

    protected:

    private:
};

#endif // CAMERA_H
