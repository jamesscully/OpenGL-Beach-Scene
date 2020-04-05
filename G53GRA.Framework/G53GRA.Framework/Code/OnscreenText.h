#ifndef ONSCREENTEXT_H
#define ONSCREENTEXT_H
#include <string>

class OnscreenText
{
    public:
        OnscreenText(int nX, int nY, std::string text);
        OnscreenText(int nX, int nY, std::string text, float* value);
        virtual ~OnscreenText();

        std::string str;

        int x, y;

        float *value;

        // indicates whether we need to add the above value to string
        bool has_value;

        void render();

    protected:

    private:
};

#endif // ONSCREENTEXT_H
