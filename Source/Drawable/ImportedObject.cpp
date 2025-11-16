#include "ImportedObject.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Geometry\IndexedTriangleList.hpp"
#include "Bindable\TransformCbuf.h"

ImportedObject::ObjectCBuf ImportedObject::staticObjCBuf;

ImportedObject::ImportedObject(Graph& gfx, const char* filename)
{
	r = 0;
	chi = 0;
	theta = 0;
	phi = 0;
	roll = 0;
	yaw = 0;
	pitch = 0;
	dchi = 0;
	dtheta = 0;
	dphi = 0;
	droll = 0;
	dyaw = 0;
	dpitch = 0;

	

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 n;
		};

		Assimp::Importer imp;
		const aiScene* scene = imp.ReadFile(filename,
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals
		);

		aiMesh* pMesh = scene->mMeshes[0];
		
		std::vector<Vertex> vertices;
		std::vector<unsigned short> indices;
		vertices.reserve(pMesh->mNumVertices);
		indices.reserve(pMesh->mNumFaces * 3);
		for (size_t i = 0; i < pMesh->mNumVertices; i++)
		{
			vertices.emplace_back(
				DirectX::XMFLOAT3(static_cast<float>(pMesh->mVertices[i].x),
					static_cast<float>(pMesh->mVertices[i].y),
					static_cast<float>(pMesh->mVertices[i].z)),
				DirectX::XMFLOAT3(static_cast<float>(pMesh->mNormals[i].x),
					static_cast<float>(pMesh->mNormals[i].y),
					static_cast<float>(pMesh->mNormals[i].z))
			);
		}

		for (size_t i = 0; i < pMesh->mNumFaces; i++)
		{
			indices.push_back(pMesh->mFaces[i].mIndices[0]);
			indices.push_back(pMesh->mFaces[i].mIndices[1]);
			indices.push_back(pMesh->mFaces[i].mIndices[2]);
		}
		
		IndexedTriangleList<Vertex> model(std::move(vertices), std::move(indices));


		auto pvs = std::make_unique<VertexShader>(gfx, L"Shader\\PhongVS.cso");
		auto vsbc = pvs->GetByteCode();

		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
		};
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddStaticBind(std::move(pvs));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"Shader\\PhongPS.cso"));
		AddStaticBind(std::make_unique<InputLayout>(gfx, layout, vsbc));
		AddStaticBind(std::make_unique<Topology>(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		AddStaticBind(std::make_unique<PixelConstantBuffer<ObjectCBuf>>(gfx, staticObjCBuf, 1u));

	}
	else
	{
		SetIndexPointer();
	}
	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

}

DirectX::XMMATRIX ImportedObject::GetTransformMatrix() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)
		* DirectX::XMMatrixTranslation(r, 0.0f, 0.0f)
		* DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);

}

void ImportedObject::Update(float dt)
{
	chi += dt * dchi;
	theta += dt * dtheta;
	phi += dt * dphi;
	roll += dt * droll;
	yaw += dt * dyaw;
	pitch += dt * dpitch;
}
