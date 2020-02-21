#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();
	int sign = 1;

	void Init() override;

	static const int gravity = -300;   // constant downward acceleration
	static const int flapping = 2550;   // upward acceleration whenever isFlapping is true

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void renderBird(glm::mat3 matrix);
	void endGame();
protected:
	glm::mat3 modelMatrix1, modelMatrix2, modelMatrix3;
	float translateX, translateX2, translateX3, translateX4, translateY;
	float angularStep;
	float bird_pos_x, bird_pos_y;
	bool flap = false;
	bool startGame = false;
	bool gameEnded = false;
	int score;
	int velocityFactor;
	bool tubesScores[3];
	bool showScore = false;
};
