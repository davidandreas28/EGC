#include "Object2D.h"

#include <Core/Engine.h>

#define TAU 2*3.141592

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, glm::vec3 secondaryClr, bool alternate) {
	Mesh* mesh = new Mesh(name);
	glm::vec3 clr(color);
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	vertices.push_back(VertexFormat(center, secondaryClr));
	indices.push_back(0);
	for (int i = 0; i <= 50; ++i) {
		glm::vec3 border_point(radius * cos((double)i * (TAU) / (double)50),
			radius * sin((double)i * TAU / (double)50),
			0);
		if (alternate) {
			clr = (i % 2) ? secondaryClr : color;
		}
		vertices.push_back(VertexFormat(center + border_point, clr));
		indices.push_back(i + 1);
	}
	mesh->SetDrawMode(GL_TRIANGLE_FAN);
	mesh->InitFromData(vertices, indices);
	return mesh;
}

Mesh* Object2D::CreateTube(std::string name, glm::vec3 leftBottomCorner, int y,  int x, int offset, int offset_y, glm::vec3 color, bool fill)
{	
	 
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(offset, 0, 0), color),
		VertexFormat(corner + glm::vec3(x + offset, 0, 0), color),
		VertexFormat(corner + glm::vec3(x + offset, 250 - offset_y, 0), color),
		VertexFormat(corner + glm::vec3(offset, 250 - offset_y, 0), color),

		VertexFormat(corner + glm::vec3(offset, y, 0), color),
		VertexFormat(corner + glm::vec3(x + offset, y, 0), color),
		VertexFormat(corner + glm::vec3(x + offset, y - 400 - offset_y, 0), color),
		VertexFormat(corner + glm::vec3(offset, y - 400 - offset_y, 0), color)


	};

	Mesh* tube = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		3, 0, 2,
		4, 5, 6,
		6, 7, 4
	};

	if (!fill) {
		tube->SetDrawMode(GL_LINE_LOOP);
	}
	else {

	}

	tube->InitFromData(vertices, indices);
	return tube;
}

Mesh* Object2D::CreateBird(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = center;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(length - 20, length - 30, 0), glm::vec3(0, 0, 0)),
		VertexFormat(corner + glm::vec3(length - 10, length - 30, 0), glm::vec3(0, 0, 0)),
		VertexFormat(corner + glm::vec3(length - 10, length - 20, 0), glm::vec3(0, 0, 0)),
		VertexFormat(corner + glm::vec3(length - 20, length - 20, 0), glm::vec3(0, 0, 0)),

		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),

		VertexFormat(corner + glm::vec3(length, length / 2 - 10, 0), glm::vec3(1, 0.753, 0.259)),
		VertexFormat(corner + glm::vec3(length + 10, length / 2 - 10, 0), glm::vec3(1, 0.753, 0.259)),
		VertexFormat(corner + glm::vec3(length, length / 2 + 10, 0), glm::vec3(1, 0.753, 0.259)),
		VertexFormat(corner + glm::vec3(length + 10, length / 2 + 10, 0), glm::vec3(1, 0.753, 0.259)),
	};

	Mesh* bird = new Mesh(name);
	std::vector<unsigned short> indices =
	{	0, 1, 2,
		3, 0, 2,
		4, 5, 6,
		7, 4, 6,
		8, 9, 10,
		10, 8, 11
	};

	if (!fill) {
		bird->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices

	}
	bird->InitFromData(vertices, indices);
	return bird;
}

