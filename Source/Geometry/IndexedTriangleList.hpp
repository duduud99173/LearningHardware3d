#pragma once
#include <vector>
#include <DirectXMath.h>


template<typename V>
class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(std::vector<V> in_vertices, std::vector<unsigned short> in_indices)
		:
		vertices(std::move(in_vertices)),
		indices(std::move(in_indices))
	{}
	void SetNormalInpendentFlat()
	{
		namespace dx = DirectX;
		assert(indices.size() % 3 == 0 && indices.size() > 0);
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto& v1 = vertices[indices[i]];
			auto& v2 = vertices[indices[i + 1]];
			auto& v3 = vertices[indices[i + 2]];

			const dx::XMVECTOR p1 = dx::XMLoadFloat3(&v1.pos);
			const dx::XMVECTOR p2 = dx::XMLoadFloat3(&v2.pos);
			const dx::XMVECTOR p3 = dx::XMLoadFloat3(&v3.pos);
			
			const auto n = dx::XMVector3Normalize( dx::XMVector3Cross( dx::XMVectorSubtract(p2,p1), dx::XMVectorSubtract(p3,p1) ) );

			dx::XMStoreFloat3(&v1.n, n);
			dx::XMStoreFloat3(&v2.n, n);
			dx::XMStoreFloat3(&v3.n, n);
		}
	}
	void SetTinTBN()
	{
		namespace dx = DirectX;
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto& v1 = vertices[indices[i]];
			auto& v2 = vertices[indices[i + 1]];
			auto& v3 = vertices[indices[i + 2]];

			const dx::XMVECTOR p1 = dx::XMLoadFloat3(&v1.pos);
			const dx::XMVECTOR p2 = dx::XMLoadFloat3(&v2.pos);
			const dx::XMVECTOR p3 = dx::XMLoadFloat3(&v3.pos);

			dx::XMFLOAT3 e1;
			dx::XMFLOAT3 e2;

			dx::XMStoreFloat3(&e1, dx::XMVectorSubtract(p2, p1));
			dx::XMStoreFloat3(&e2, dx::XMVectorSubtract(p3, p1));

			dx::XMFLOAT2 dUV1;
			dx::XMFLOAT2 dUV2;

			dUV1.x = v2.texCoord.x - v1.texCoord.x;
			dUV1.y = v2.texCoord.y - v1.texCoord.y;
			dUV2.x = v3.texCoord.x - v1.texCoord.x;
			dUV2.y = v3.texCoord.y - v1.texCoord.y;

			float f = 1.0f / (dUV1.x * dUV2.y - dUV1.y * dUV2.x);
			dx::XMFLOAT3 tangent;

			tangent.x = f * (e1.x * dUV1.x - e2.x * dUV1.y);
			tangent.y = f * (e1.y * dUV1.x - e2.y * dUV1.y);
			tangent.z = f * (e1.z * dUV1.x - e2.z * dUV1.y);
			 
			dx::XMStoreFloat3(&v1.T,dx::XMVector3Normalize(dx::XMLoadFloat3(&tangent)));

			v2.T = v1.T;
			v3.T = v1.T;

		}
	}
public:
	std::vector<V> vertices;
	std::vector<unsigned short> indices;
};