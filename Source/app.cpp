#pragma once
#include "app.h"
#include "GDIPlusManager.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


GDIPlusManager gdipm;

App::App(int w, int h)
	:
	wnd(w, h),
	gfx(wnd.GetHandle()),
	light(gfx, 1.0f),
	cloudSky(gfx)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> rdr(6.0f, 20.0f);
	std::uniform_real_distribution<float> rdd(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rda(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> rdb(0.0f, 3.1415f * 2.0f);
	for (int i = 0; i <= 80; i ++ )
	{
		skinnedBoxes.push_back(std::make_unique<SkinnedBox>(gfx,rng,rdr,rdd,rda,rdb));
	}
	objects.push_back(std::make_unique<ImportedObject>(gfx, "Assets\\model\\skeleton.OBJ"));
}

App::~App()
{
	
}

int App::Go()
{
	while (TRUE)
	{
		if (const auto ecode = Window::ProcessMessage())
		{
			return *ecode;
		}

		
		DoFrame();
	}
}

void App::DoFrame()
{
	const float dt = speed * timer.Mark();


	gfx.SetCameraMatrix(cam.GetMatrix());
	gfx.BeginFrame(0.07f, 0.0f, 0.12f);

	light.DrawMesh(gfx);
	light.BindCBuf(gfx.GetCameraMatrix());

	for (auto& item : skinnedBoxes)
	{
		item->Update(dt);
		item->BindAndDraw(gfx);
	}

	for (auto& item : objects)
	{
		item->Update(dt);
		item->BindAndDraw(gfx);
	}

	cloudSky.Update(dt);
	cloudSky.UpdateCbuf(gfx);
	cloudSky.BindAndDraw(gfx);


	if (ImGui::Begin("Time Speed"))
	{
		ImGui::SliderFloat("Time Speed", &speed, 0.0f, 5.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	ImGui::End();
	
	cam.SpawnControlWindow();
	light.SpawnControlWindow();
	SkinnedBox::SpawnStaticControlWindow(gfx);

	gfx.EndFrame();
}

