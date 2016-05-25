#include "simpleButton.h"

int Button::ButtonCount = 0;
std::vector<bool> Button::ButtonsCursor;
bool Button::buttonChange;
Button::Button(SDL_Renderer* gRenderer, std::string path, int x, int y, int w, int h)
{
	ID = ButtonCount++;
	ButtonsCursor.push_back(false);
	buttonSheet = new LTexture;
	xPos = x;
	yPos = y;
	mWidth = w;
	mHeight = h;
	activated = false;
	buttonSheet->loadFromFile(gRenderer, path);

	//Setup button clips
	clips[0] = new SDL_Rect;
	clips[0]->h = mHeight;
	clips[0]->w = mWidth;
	clips[0]->x = 0;
	clips[0]->y = 0;
	clips[1] = new SDL_Rect;
	clips[1]->h = mHeight;
	clips[1]->w = mWidth;
	clips[1]->x = mWidth;
	clips[1]->y = 0;
}

Button::~Button()
{
	delete clips[1];
	delete clips[0];
	delete buttonSheet;
}

void Button::draw(SDL_Renderer* gRenderer)
{
	if (mState == NOT_OVER && !activated)
		buttonSheet->render(gRenderer, xPos, yPos, clips[0]);
	else if (mState == MOUSE_OVER || activated)
		buttonSheet->render(gRenderer, xPos, yPos, clips[1]);
}

void Button::input(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Mouse pos
		int x, y;
		SDL_GetMouseState(&x, &y);
		//Check if mouse is colliding with the button
		bool inside = true;

		//Mouse is left of the button
		if (x < xPos)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > xPos + mWidth)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < yPos)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > yPos + mHeight)
		{
			inside = false;
		}
		
		if (inside)
		{
			ButtonsCursor.at(ID) = true;
			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				activated = !activated;
				break;
			case SDL_MOUSEMOTION:
				mState = MOUSE_OVER;
				SDL_Cursor* cursor;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
				SDL_SetCursor(cursor);
				break;
				//mState = PRESSED;
			}
		}
		else
		{
			ButtonsCursor.at(ID) = false;
			//If no buttons are active change the cursor back
			if (!anyActive())
			{
				SDL_Cursor* cursor;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
				SDL_SetCursor(cursor);
				cursor = NULL;
				delete cursor;
			}
			
			mState = NOT_OVER;
		}
	}
	if (activated==true)
		buttonChange = true;
}

bool Button::getActivated()
{
	return activated;
}

void Button::setActivated(bool a)
{
	activated = a;
}

//Checks to see if any of the buttons are active
bool Button::anyActive()
{
	for (int i = 0; i != ButtonsCursor.size(); i++)
		if (ButtonsCursor.at(i))
			return true;
	return false;
}