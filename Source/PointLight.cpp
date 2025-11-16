#include "PointLight.h"
#include "imgui.h"

PointLight::PointLight(Graph& gfx, float r) : cBuf( gfx ), mesh(gfx, r), gfx(gfx)
{
	Reset();
}


void PointLight::BindCBuf(DirectX::FXMMATRIX viewMatrix)
{
	PointLightCBuf tempData = cbData;
	DirectX::XMStoreFloat3(&tempData.pos, GetViewedPos(viewMatrix));
	cBuf.Update(gfx, tempData);
	cBuf.Bind(gfx);
}

void PointLight::BindMeshColor()
{
	mesh.SetColor(cbData.diffColor);
	mesh.UpdateColorPSBuf(gfx);
}

DirectX::XMVECTOR PointLight::GetViewedPos( DirectX::FXMMATRIX viewMatrix)
{
	return DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&cbData.pos), viewMatrix);
}

void PointLight::DrawMesh(Graph& gfx)
{
	mesh.SetPosition(cbData.pos);
	mesh.BindAndDraw(gfx);
}

void PointLight::SpawnControlWindow()
{
	bool dirty = false;

	if (ImGui::Begin("Light"))
	{
		ImGui::SliderFloat("X", &cbData.pos.x, -60.0f, 60.0f);
		ImGui::SliderFloat("Y", &cbData.pos.y, -60.0f, 60.0f);
		ImGui::SliderFloat("Z", &cbData.pos.z, -60.0f, 60.0f);

		ImGui::Text("Intensity/Color");
		dirty = dirty || ImGui::SliderFloat("Intensity", &cbData.lightIntensity, 0.01f, 2.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
		dirty = dirty || ImGui::ColorEdit3("Diffuse Color", &cbData.diffColor.x);
		dirty = dirty || ImGui::ColorEdit3("Ambient", &cbData.ambient.x);

		ImGui::Text("Falloff");
		dirty = dirty || ImGui::SliderFloat("Constant", &cbData.attCon, 0.05f, 10.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
		dirty = dirty || ImGui::SliderFloat("Linear", &cbData.attLin, 0.0001f, 4.0f, "%.4f", ImGuiSliderFlags_Logarithmic);
		dirty = dirty || ImGui::SliderFloat("Quadratic", &cbData.attQuad, 0.0000001f, 10.0f, "%.7f", ImGuiSliderFlags_Logarithmic);
	
		if (ImGui::Button("Reset"))
		{
			Reset();
			dirty = true;
		}
	}
	ImGui::End();
	
	if (dirty)
	{
		BindMeshColor();
	}
}

void PointLight::Reset()
{
	cbData =
	{
		{0.0f, 0.0f, 0.0f},
		1.0f,
		{ 1.0f, 1.0f, 1.0f },
		{},
		{ 0.05f, 0.05f, 0.05f },
		1.0f,
		0.045,
		0.0075f,
		{},
		{}
	};
}
