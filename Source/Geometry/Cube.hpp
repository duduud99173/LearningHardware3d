#pragma once
#include "IndexedTriangleList.hpp"


class Cube
{
public:
	template<typename V>
	static IndexedTriangleList<V> Make()
	{
		constexpr float side = 1.0f/2.0f;
		std::vector<V> vertices(8);
		vertices[0].pos = { -side, -side, -side };
		vertices[1].pos = {  side, -side, -side };
		vertices[2].pos = { -side,  side, -side };
		vertices[3].pos = { -side, -side,  side };
		vertices[4].pos = {  side,  side, -side };
		vertices[5].pos = { -side,  side,  side };
		vertices[6].pos = {  side, -side,  side };
		vertices[7].pos = {  side,  side,  side };
		std::vector<unsigned short> indices =
		{
			//d
			0,1,3,
			1,6,3,
			//b
			6,5,3,
			6,7,5,
			//l
			3,2,0,
			5,2,3,
			//r
			7,6,1,
			4,7,1,
			//u
			7,4,2,
			5,7,2,
			//f
			2,1,0,
			4,1,2
		};
		return { 
			std::move(vertices) ,{
				//d
				0,1,3,  1,6,3,
				//b
				6,5,3,  6,7,5,
				//l
				3,2,0,  5,2,3,
				//r
				7,6,1,  4,7,1,
				//u
				7,4,2,	5,7,2,
				//f
				2,1,0,	4,1,2
			} 
		};
	}
	template<typename V>
	static IndexedTriangleList<V> MakeSkinned()
	{
		constexpr float side = 1.0f / 2.0f;

		std::vector<V> vertices(14);

		vertices[0].pos = { -side,-side,-side };
		vertices[0].texCoord = { 2.0f / 3.0f,0.0f / 4.0f };
		vertices[1].pos = { side,-side,-side };
		vertices[1].texCoord = { 1.0f / 3.0f,0.0f / 4.0f };
		vertices[2].pos = { -side,side,-side };
		vertices[2].texCoord = { 2.0f / 3.0f,1.0f / 4.0f };
		vertices[3].pos = { side,side,-side };
		vertices[3].texCoord = { 1.0f / 3.0f,1.0f / 4.0f };
		vertices[4].pos = { -side,-side,side };
		vertices[4].texCoord = { 2.0f / 3.0f,3.0f / 4.0f };
		vertices[5].pos = { side,-side,side };
		vertices[5].texCoord = { 1.0f / 3.0f,3.0f / 4.0f };
		vertices[6].pos = { -side,side,side };
		vertices[6].texCoord = { 2.0f / 3.0f,2.0f / 4.0f };
		vertices[7].pos = { side,side,side };
		vertices[7].texCoord = { 1.0f / 3.0f,2.0f / 4.0f };
		vertices[8].pos = { -side,-side,-side };
		vertices[8].texCoord = { 2.0f / 3.0f,4.0f / 4.0f };
		vertices[9].pos = { side,-side,-side };
		vertices[9].texCoord = { 1.0f / 3.0f,4.0f / 4.0f };
		vertices[10].pos = { -side,-side,-side };
		vertices[10].texCoord = { 3.0f / 3.0f,1.0f / 4.0f };
		vertices[11].pos = { -side,-side,side };
		vertices[11].texCoord = { 3.0f / 3.0f,2.0f / 4.0f };
		vertices[12].pos = { side,-side,-side };
		vertices[12].texCoord = { 0.0f / 3.0f,1.0f / 4.0f };
		vertices[13].pos = { side,-side,side };
		vertices[13].texCoord = { 0.0f / 3.0f,2.0f / 4.0f };

		return{
			std::move(vertices),{
				0,2,1,   2,3,1,
				4,8,5,   5,8,9,
				2,6,3,   3,6,7,
				4,5,7,   4,7,6,
				2,10,11, 2,11,6,
				12,3,7,  12,7,13
			}
		};
	}

	template<class V>
	static IndexedTriangleList<V> MakeSkinnedIndependent()
	{
		constexpr float side = 1.0f / 2.0f;

		std::vector<V> vertices(24);
		vertices[0].pos = { -side,-side,-side };// 0 near side
		vertices[0].texCoord = { 0.0f,0.0f };
		vertices[1].pos = { side,-side,-side };// 1
		vertices[1].texCoord = { 1.0f,0.0f };
		vertices[2].pos = { -side,side,-side };// 2
		vertices[2].texCoord = { 0.0f,1.0f };
		vertices[3].pos = { side,side,-side };// 3
		vertices[3].texCoord = { 1.0f,1.0f };
		vertices[4].pos = { -side,-side,side };// 4 far side
		vertices[4].texCoord = { 1.0f,0.0f };
		vertices[5].pos = { side,-side,side };// 5
		vertices[5].texCoord = { 0.0f,0.0f };
		vertices[6].pos = { -side,side,side };// 6
		vertices[6].texCoord = { 1.0f,1.0f };
		vertices[7].pos = { side,side,side };// 7
		vertices[7].texCoord = { 0.0f,1.0f };
		vertices[8].pos = { -side,-side,-side };// 8 left side
		vertices[8].texCoord = { 1.0f,0.0f };
		vertices[9].pos = { -side,side,-side };// 9
		vertices[9].texCoord = { 1.0f,1.0f };
		vertices[10].pos = { -side,-side,side };// 10
		vertices[10].texCoord = { 0.0f,0.0f };
		vertices[11].pos = { -side,side,side };// 11
		vertices[11].texCoord = { 0.0f,1.0f };
		vertices[12].pos = { side,-side,-side };// 12 right side
		vertices[12].texCoord = { 0.0f,0.0f };
		vertices[13].pos = { side,side,-side };// 13
		vertices[13].texCoord = { 0.0f,1.0f };
		vertices[14].pos = { side,-side,side };// 14
		vertices[14].texCoord = { 1.0f,0.0f };
		vertices[15].pos = { side,side,side };// 15
		vertices[15].texCoord = { 1.0f,1.0f };
		vertices[16].pos = { -side,-side,-side };// 16 bottom side
		vertices[16].texCoord = { 0.0f,1.0f };
		vertices[17].pos = { side,-side,-side };// 17
		vertices[17].texCoord = { 1.0f,1.0f };
		vertices[18].pos = { -side,-side,side };// 18
		vertices[18].texCoord = { 0.0f,0.0f };
		vertices[19].pos = { side,-side,side };// 19
		vertices[19].texCoord = { 1.0f,0.0f };
		vertices[20].pos = { -side,side,-side };// 20 top side
		vertices[20].texCoord = { 0.0f,0.0f };
		vertices[21].pos = { side,side,-side };// 21
		vertices[21].texCoord = { 1.0f,0.0f };
		vertices[22].pos = { -side,side,side };// 22
		vertices[22].texCoord = { 0.0f,1.0f };
		vertices[23].pos = { side,side,side };// 23
		vertices[23].texCoord = { 1.0f,1.0f };


		

		return{
			std::move(vertices),{
				0,2, 1,    2,3,1,
				4,5, 7,    4,7,6,
				8,10, 9,  10,11,9,
				12,13,15, 12,15,14,
				16,17,18, 18,17,19,
				20,23,21, 20,22,23
			}
		};
	}

	template<class V>
	static IndexedTriangleList<V> MakeIndependent()
	{
		constexpr float side = 1.0f / 2.0f;

		std::vector<V> vertices(24);
		vertices[0].pos = { -side,-side,-side };// 0 near side
		vertices[1].pos = { side,-side,-side };// 1
		vertices[2].pos = { -side,side,-side };// 2
		vertices[3].pos = { side,side,-side };// 3
		vertices[4].pos = { -side,-side,side };// 4 far side
		vertices[5].pos = { side,-side,side };// 5
		vertices[6].pos = { -side,side,side };// 6
		vertices[7].pos = { side,side,side };// 7
		vertices[8].pos = { -side,-side,-side };// 8 left side
		vertices[9].pos = { -side,side,-side };// 9
		vertices[10].pos = { -side,-side,side };// 10
		vertices[11].pos = { -side,side,side };// 11
		vertices[12].pos = { side,-side,-side };// 12 right side
		vertices[13].pos = { side,side,-side };// 13
		vertices[14].pos = { side,-side,side };// 14
		vertices[15].pos = { side,side,side };// 15
		vertices[16].pos = { -side,-side,-side };// 16 bottom side
		vertices[17].pos = { side,-side,-side };// 17
		vertices[18].pos = { -side,-side,side };// 18
		vertices[19].pos = { side,-side,side };// 19
		vertices[20].pos = { -side,side,-side };// 20 top side
		vertices[21].pos = { side,side,-side };// 21
		vertices[22].pos = { -side,side,side };// 22
		vertices[23].pos = { side,side,side };// 23

		return{
			std::move(vertices),{
				0,2, 1,    2,3,1,
				4,5, 7,    4,7,6,
				8,10, 9,  10,11,9,
				12,13,15, 12,15,14,
				16,17,18, 18,17,19,
				20,23,21, 20,22,23
			}
		};
	}
};