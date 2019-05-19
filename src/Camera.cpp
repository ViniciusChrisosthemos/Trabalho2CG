#include "Camera.h"

Camera::Camera(Vector3* observer, Vector3* target)
{
    this->observer = observer;
    this->target = target;
    angle = 0;
}

void Camera::SetObserver(Vector3* observer)
{
    this->observer = observer;
}

void Camera::SetTarget(Vector3* target)
{
    this->target = target;
}

Camera::~Camera()
{
    delete observer;
    delete target;
}
