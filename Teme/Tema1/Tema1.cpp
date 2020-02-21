#include "Tema1.h"
#include "Object2D.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Transform2D.h"


#define TAU 2*3.141592

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{	
	//set camera
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	
	// initialize translation factors
	translateX = 0;
	translateX2 = 0;
	translateX3 = 0;
	translateX4 = 0;
	translateY = 0;

	// initialize initial position
	bird_pos_x = 150;
	bird_pos_y = 450;

	score = 0;
	velocityFactor = 1;

	startGame = false;
	
	// initialize angularStep
	angularStep = 0;

	for (int i = 0; i < 3; ++i) {
		tubesScores[i] = false;
	}
	
	Mesh* bird = Object2D::CreateBird("bird", corner, squareSide, glm::vec3(1, 0.976, 0.506), true);
	AddMeshToList(bird);

	Mesh* tube1 = Object2D::CreateTube("tube1", corner, resolution.y, 100, 0, 0, glm::vec3(0.369, 1, 0.694), true);
	AddMeshToList(tube1);
	Mesh* tube2 = Object2D::CreateTube("tube2", corner, resolution.y, 100, 550, 100, glm::vec3(0.369, 1, 0.694), true);
	AddMeshToList(tube2);
	Mesh* tube3 = Object2D::CreateTube("tube3", corner, resolution.y, 100, 1250, -100, glm::vec3(0.369, 1, 0.694), true);
	AddMeshToList(tube3);

	Mesh* circle = Object2D::CreateCircle("circle", corner  + glm::vec3(squareSide - 62, 0, 0), 10, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), true);
	AddMeshToList(circle);
	Mesh* circle2 = Object2D::CreateCircle("circle2", corner + glm::vec3(squareSide - 37, 0, 0), 10, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), true);
	AddMeshToList(circle2);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1, 1.00000,  0.96078, 0.67843);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	if (gameEnded) {
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (showScore == false) {
			cout << ">>>>>>>GAME OVER<<<<<<<" << endl;
			cout << "Your Score ::: " << score - 100 << endl;
			showScore = true;
		}
		return;
	}
	
	glm::ivec2 resolution = window->GetResolution();
	modelMatrix1 = glm::mat3(1);
	modelMatrix1 *= Transform2D::Translate(bird_pos_x, bird_pos_y);

	if (startGame == false) {
		renderBird(modelMatrix1);
		return;
	}

	if (flap) {
		modelMatrix1 = glm::mat3(1);
		translateY += deltaTimeSeconds * (Tema1::gravity + Tema1::flapping);
		bird_pos_y += translateY;
		modelMatrix1 *= Transform2D::Translate(bird_pos_x, bird_pos_y);
		angularStep += deltaTimeSeconds * 28;
		flap = false;
	} else {
		modelMatrix1 = glm::mat3(1);
		translateY += deltaTimeSeconds * (Tema1::gravity);
		bird_pos_y += translateY;
		modelMatrix1 *= Transform2D::Translate(bird_pos_x, bird_pos_y);
		angularStep -= deltaTimeSeconds * 0.65;
	}

	if (translateY > resolution.y || translateY < 0) {
		translateY = 0;
	}

	if (angularStep > 0.5) {
		angularStep = 0.5;
	} else if (angularStep < -1) {
		angularStep = -1;
	}

	modelMatrix1 *= Transform2D::Translate(50, 50);
	modelMatrix1 *= Transform2D::Rotate(angularStep);
	modelMatrix1 *= Transform2D::Translate(-50, -50);

	if (bird_pos_y + 100 > resolution.y) {
		modelMatrix1 *= Transform2D::Translate(0, resolution.y);
		bird_pos_y = resolution.y - 100;
	} else if (bird_pos_y < 0) {
		modelMatrix1 *= Transform2D::Translate(0, 0);
		bird_pos_y = 0;
	}

	renderBird(modelMatrix1);

	modelMatrix1 = glm::mat3(1);
	modelMatrix1 *= Transform2D::Translate(resolution.x + translateX, 0); 
	translateX -= deltaTimeSeconds * (240 + velocityFactor);

	modelMatrix2 = glm::mat3(1);
	modelMatrix2 *= Transform2D::Translate(resolution.x + translateX2, 0);
	translateX2 -= deltaTimeSeconds * (240 + velocityFactor);

	modelMatrix3 = glm::mat3(1);
	modelMatrix3 *= Transform2D::Translate(resolution.x + translateX3, 0);
	translateX3 -= deltaTimeSeconds * (240 + velocityFactor);

	glm::vec3 myVec(translateX, translateX2, translateX3);
	for (int k = 0; k < 3; ++k) {
		for (int i = 0; i <= 50; ++i) {
			glm::vec3 border_point((100 * sqrt(2) / 2) * cos((double)i * (TAU) / (double)50),
				(100 * sqrt(2) / 2) * sin((double)i * TAU / (double)50),
				0);
			float x_pos = bird_pos_x + 50 + border_point.x;
			float y_pos = bird_pos_y + 50 + border_point.y;

			if (k == 0) {
				if (x_pos < resolution.x + translateX + 100
					&& x_pos > resolution.x + translateX
					&& ((y_pos < 250) || (y_pos > resolution.y - 400))
					) {
					// am coliziune
					endGame();
					break;
				}
				else if (bird_pos_x < resolution.x + translateX + 100
					&& tubesScores[k] == false) {
					score += 100;
					tubesScores[k] = true;
				}
			}
			else if (k == 1) {
				if (x_pos < resolution.x + translateX2 + 100 + 550
					&& x_pos > resolution.x + translateX2 + 550
					&& ((y_pos < 150) || (y_pos > resolution.y - 500))
					) {
					// am coliziune
					endGame();
					break;
				}
				else if (bird_pos_x > resolution.x + translateX2 + 100 + 550
					&& tubesScores[k] == false) {
					score += 100;
					tubesScores[k] = true;
				}
			}
			else if (k == 2) {
				if (x_pos < resolution.x + translateX3 + 100 + 1250
					&& x_pos > resolution.x + translateX3 + 1250
					&& ((y_pos < 350) || (y_pos > resolution.y - 300))
					) {
					// am coliziune
					endGame();
					break;
				}
				else if (bird_pos_x > resolution.x + translateX3 + 100 + 1250
					&& tubesScores[k] == false) {
					score += 100;
					tubesScores[k] = true;
				}
			}
		}
	}

	// respawn la pipes
	if (translateX  + 100 < 0 - resolution.x) {
		translateX = 0;
		modelMatrix1 = glm::mat3(1);
		modelMatrix1 *= Transform2D::Translate(resolution.x, 0);
		tubesScores[0] = false;
	}
	if (translateX2 + 100 + 550 < 0 - resolution.x) {
		translateX2 = -550;
		modelMatrix2 = glm::mat3(1);
		modelMatrix2 *= Transform2D::Translate(resolution.x, 0);
		tubesScores[1] = false;
	}
	if (translateX3 + 100 + 1250 < 0 - resolution.x) {
		translateX3 = -1250;
		modelMatrix3 = glm::mat3(1);
		modelMatrix3 *= Transform2D::Translate(resolution.x, 0);
		tubesScores[2] = false;
	}
	RenderMesh2D(meshes["tube1"], shaders["VertexColor"], modelMatrix1);
	RenderMesh2D(meshes["tube2"], shaders["VertexColor"], modelMatrix2);
	RenderMesh2D(meshes["tube3"], shaders["VertexColor"], modelMatrix3);

	if (score % 700 == 0) {
		velocityFactor += 5;
	}

}
 
void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE) {
		startGame = true;
		flap= true;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
void Tema1::renderBird(glm::mat3 matrix) {
	RenderMesh2D(meshes["bird"], shaders["VertexColor"], matrix);
	RenderMesh2D(meshes["circle"], shaders["VertexColor"], matrix);
	RenderMesh2D(meshes["circle2"], shaders["VertexColor"], matrix);
}
void Tema1::endGame() {
	gameEnded = true;
}
