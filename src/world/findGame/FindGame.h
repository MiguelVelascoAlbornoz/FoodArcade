#pragma once
#include "Face.h"
class FindGame
{
public:
	FindGame();
	~FindGame();
	void moveCircles();
	float iconsSize = 1;
	void startLevel();
	void passLevel();
	void selectImpostor();
	void generateQuadLevel();
	int impostorIndex = -1;

	void generateNoiseLevel(float facesCount);
	void everyoneInEachDirectionBouncing(float facesFactor);
	void everyoneInEachDirection(float facesFactor);
	void generateQuadsMoveVertical(float velocity);
	bool bouncing = false;
	bool canDestroy = false;
	Face* impostorFace = NULL;
	std::vector<Image*> possibleIcons;
	int lastSecond = 11;
	void  render();
	VAO squareVao;
	int level = 1;
	vec2 gameCanvasSize;
	float time = 11;
	std::list<PlusTimeGui> plusTimeGuis;
	bool waitingToSumTime = false;
	bool inInterface = false;
	float interfaceTime = 0;
	bool alreadyInteracted = false;
	bool canSumTime = false;
	float counterToSumTime = 0;
	bool timeCounting = false;
	bool levelRunning = false;
	float gameEndTimer = 0;
	bool countGameEnd = false;;
	void gameEnd();
	
	bool renderEndGui = false;
	struct Light  {
		vec2 pos;
		float radius;
		bool moving = false;
		vector<vec2> movePos;
		float speed = 500;
		bool shouldIncrease = false;
	};
	int neededTime = 0;
	float sumTimeTimer = 0; 
	bool setYellow = false;
	bool renderTime = false;;
	bool renderLevel = true;
	float facesSize;
	Image* impostor;
	Light lightCircles[2];
	void setCircles();
	void renderGui();
	std::vector<Face> faces;
	void gen();
};

