#pragma once
#include "constants.h"

enum buttonState{ MOUSE_OVER, NOT_OVER};

class Button
{
public: 
	//Gets mouse intput
	void input(SDL_Event* e);

	//Makes sure two buttons can't be pressed at once
	static void alterButtons(Button b);

	void draw(SDL_Renderer* gRenderer);

	Button(SDL_Renderer* gRenderer, std::string path, int x, int y,int w, int h);

	~Button();

	//True if cursor should be active
	static bool CURSOR_ACTIVE;
	static std::vector<bool> ButtonsCursor;
	static int ButtonCount;
	static bool buttonChange;
	int ID;
	void setActivated(bool a);
	bool getActivated();
private:
	//Gets button sprite sheet
	LTexture* buttonSheet; 
	//Button attributes
	int xPos, yPos,
		mWidth, mHeight;
	int activated;
	//State of the button
	buttonState mState;

	//Clips for the button animation
	SDL_Rect* clips[2];

	bool anyActive();

};