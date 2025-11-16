#pragma once
#include "graphic.h"
#include "Timer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "Drawable\Box.h"
#include "Drawable\SkinnedBox.h"
#include "Drawable\ImportedObject.h"
#include "Drawable\CloudSky.h"

class App
{
public:
	App(int w, int h);
	~App();
	int Go();
	void DoFrame();
	
private:
	ImguiManager imgui;
	Window wnd;
	Graph gfx;
	Timer timer;
	std::vector<std::unique_ptr<Box>> boxes;
	std::vector<std::unique_ptr<SkinnedBox>> skinnedBoxes;
	std::vector<std::unique_ptr<ImportedObject>> objects;
	CloudSky cloudSky;
	float speed = 1.0f;
	Camera cam;
	PointLight light;
};