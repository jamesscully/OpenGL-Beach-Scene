#pragma once

#include "../Framework/Engine/Scene.h"

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};

private:

    int WIN_HEIGHT, WIN_WIDTH;

	void Initialise();
	void Projection();

    void drawDebugText();


protected:
    void HandleMouse(int button, int state, int x, int y) override;
    void HandleMouseMove(int x, int y) override;


private:
    virtual void HandleKey(unsigned char key, int state, int x, int y);
    void drawGridLines();
    void drawAxisLines();
};