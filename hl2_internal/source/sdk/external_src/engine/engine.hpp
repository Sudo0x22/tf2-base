#pragma once
#include<vector>
class Vector {
public:
	float x, y, z;
};
class Vector2D {
public:
	float x, y;
};

namespace engine
{
	bool WorldToScreen(Vector in, Vector2D& out);
}