#pragma once
#include "IndexedTriangleList.hpp"
#include "Mathmatic.h"
#include <DirectXMath.h>


class Sphere
{
public:
	template<typename V>
	static IndexedTriangleList<V> MakeTesselated(int latDiv, int longDiv)
	{
		namespace dx = DirectX;
		std::vector<V> vertices;
		std::vector<unsigned short> indices;
		
		const float latAngle = Pi / latDiv;
		const float longAngle = 2.0f * Pi / longDiv;

		const dx::XMVECTOR base = dx::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		for (int ilat = 1; ilat < latDiv; ilat++)
		{
			const dx::XMVECTOR latBase = dx::XMVector3Transform(base, dx::XMMatrixRotationX(ilat * latAngle));
			for (int ilong = 0; ilong < longDiv; ilong++)
			{
				vertices.emplace_back();
				const dx::XMVECTOR v = dx::XMVector3Transform(latBase, dx::XMMatrixRotationZ(ilong * longAngle));
				dx::XMStoreFloat3(&vertices.back().pos, v);
			}
		}
		unsigned short iNorth = (unsigned short)vertices.size();
		vertices.emplace_back();
		dx::XMStoreFloat3(&vertices.back().pos, base);
		unsigned short iSouth = (unsigned short)vertices.size();
		vertices.emplace_back();
		dx::XMStoreFloat3(&vertices.back().pos, dx::XMVectorNegate(base));

		const auto calcIdx = [longDiv](unsigned short ilat, unsigned short ilong) -> unsigned short
			{
				return (unsigned short)(ilat * longDiv + ilong);
			};

		for (unsigned short ilat = 0; ilat < latDiv - 2; ilat++)
		{
			for (unsigned short ilong = 0; ilong < longDiv - 1; ilong++)
			{
				indices.push_back(calcIdx(ilat, ilong));
				indices.push_back(calcIdx(ilat + 1, ilong));
				indices.push_back(calcIdx(ilat, ilong + 1));
				indices.push_back(calcIdx(ilat, ilong + 1));
				indices.push_back(calcIdx(ilat + 1, ilong));
				indices.push_back(calcIdx(ilat + 1, ilong + 1));
			}
			indices.push_back(calcIdx(ilat, longDiv - 1));
			indices.push_back(calcIdx(ilat + 1, longDiv -1));
			indices.push_back(calcIdx(ilat, 0));
			indices.push_back(calcIdx(ilat, 0));
			indices.push_back(calcIdx(ilat + 1, longDiv - 1));
			indices.push_back(calcIdx(ilat + 1, 0));
		}
		for (unsigned short ilong = 0; ilong < longDiv - 1; ilong++)
		{
			indices.push_back(iNorth);
			indices.push_back(calcIdx(0, ilong));
			indices.push_back(calcIdx(0, ilong + 1));
			indices.push_back(iSouth);
			indices.push_back(calcIdx(latDiv - 2, ilong + 1));
			indices.push_back(calcIdx(latDiv - 2, ilong));
		}
		indices.push_back(iNorth);
		indices.push_back(calcIdx(0, longDiv - 1));
		indices.push_back(calcIdx(0, 0));
		indices.push_back(iSouth);
		indices.push_back(calcIdx(latDiv - 2, 0));
		indices.push_back(calcIdx(latDiv - 2, longDiv - 1));

		return{ std::move(vertices),std::move(indices) };
	}

	template<typename V>
	static IndexedTriangleList<V> Make()
	{
		return MakeTesselated<V>( 12, 24 );
	}
};