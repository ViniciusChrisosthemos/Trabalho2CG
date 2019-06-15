#ifndef TEXT_H
#define TEXT_H
#include <Object.h>

class Text : public Object
{
    public:
        Text();
        void SetText(Model* model);
        void Rotate(float force);
        virtual ~Text();

    protected:

    private:
};

#endif // TEXT_H
