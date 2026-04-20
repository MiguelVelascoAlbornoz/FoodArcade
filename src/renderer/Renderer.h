#pragma once

#include "GIF.h"



using namespace glm;
class Renderer
{
public:
	GLFWcursor* cursor;
	static ImFont* upheav;
	static ImFont* gameFont;
	static ImFont* marioFont;
	static ImFont* pixer;
	static ImFont* marioFontsmall;
	static ImFont* minecraftFont;
	
	static ma_sound MENU_SOUND;
	static ma_sound GAME_OVER_SOUND;
	static ma_sound CARD_FLIP;
	static ma_sound CARDS_GAIN;
	static ma_sound CORRECT_ANSWER;
	static ma_sound INVALID_ANSWER;
	static ma_sound DAMAGE;
	static ma_sound EXPLOSION;
	static ma_sound FUSE;
	static ma_sound GAIN_TIME;
	static ma_sound LASER;
	static ma_sound POWER_UP;
	static ma_sound TIMER;
	static ma_sound CAKE_SPAWN;

	~Renderer();
	float aspectRatio;
	bool initRenderer(bool fullscreen);
	bool setupWindow();
	bool setupImGUI();
	static void errorCallback(int error, const char* description);
	bool glLogCall(const char* function, const char* file, int line);
	void background( GLfloat r, GLfloat g, GLfloat b);
	void toggleFullscreen();
	void update();

	bool getIsFullscreen() const { return isFullscreen; };
	const vec2& getWindowSize() { return windowSize; };
	GLFWwindow* window = nullptr;
private:

	bool isFullscreen = true;



};

