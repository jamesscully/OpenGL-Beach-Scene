#ifndef ONSCREENTEXT_H
#define ONSCREENTEXT_H
#include <string>

class OnscreenText
{
    public:
        OnscreenText(int nX, int nY, std::string text);
        OnscreenText(std::string text);
        virtual ~OnscreenText();

        void* font;
        std::string str;

        int x, y;


        void setPos(int x, int y);
        void setText(std::string s);
        void setFont(void* fnt);
        void render();

    protected:

    private:
};

#endif // ONSCREENTEXT_H
