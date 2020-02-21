
#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, glm::vec3 secondaryClr, bool alternate);
	Mesh* CreateTube(std::string name, glm::vec3 leftBottomCorner, int y, int x, int offset, int offset_y, glm::vec3 color, bool fill);
	Mesh* CreateBird(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill = false);

}

