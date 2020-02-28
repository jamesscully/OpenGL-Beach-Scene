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


	void drawGridLines();
	void drawAxisLines();


};