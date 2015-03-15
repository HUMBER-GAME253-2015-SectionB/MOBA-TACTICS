//Author:	Nicholas Higa
//Date:		3/15/2015 (NH)

#include "Camera.h"

//Position refers to the top left of the camera
Camera::Camera(SDL_Renderer *renderer, vec2 pos, int width, int height)
{
	SetRenderer(renderer);
	SDL_Rect *rect = new SDL_Rect();
	rect->x = (int)pos.x;
	rect->y = (int)pos.y;
	rect->w = width;
	rect->h = height;
	SetCamera(rect);
}

void Camera::Draw(SDL_Renderer *ren)
{
	for (unsigned i = 0; i < drawList.size(); i++)
		drawList[i]->Draw(drawList[i]->GetPosition() - GetPosition(), ren);
}

void Camera::Update()
{
}

void Camera::AddToDrawList(Sprite *item)
{
	drawList.push_back(item);
}

void Camera::RemoveFromDrawList(Sprite *item)
{ 
	vector<Sprite*>::iterator it;
	int i = 0;

	for (it = drawList.begin(); it < drawList.end(); it++, i++)
	{
		if (drawList[i] == item)
		{
			drawList.erase(it);
			break;
		}
	}
}

SDL_Rect* Camera::GetCamera()
{
	return camera;
}

SDL_Renderer* Camera::GetRenderer()
{
	return ren;
}

vec2 Camera::GetPosition()
{
	int x, y;
	x = GetCamera()->x; 
	y = GetCamera()->y;
	return vec2(GetCamera()->x, GetCamera()->y);
}

int Camera::GetWidth()
{
	return GetCamera()->w;
}

int Camera::GetHeight()
{
	return GetCamera()->h;
}

vec2 Camera::GetDrawablePosOnScreen(Sprite *item)
{
	vector<Sprite*>::iterator it;
	int i = 0;

	for (it = drawList.begin(); it < drawList.end(); it++, i++)
	{
		if (drawList[i] == item)
		{
			return drawList[i]->GetPosition() - GetPosition();
		}
	}
}

void Camera::SetCamera(SDL_Rect *cam)
{
	camera = cam;
}

void Camera::SetRenderer(SDL_Renderer *renderer)
{
	ren = renderer;
}

void Camera::SetPosition(vec2 pos)
{
	camera->x = (int)pos.x;
	camera->y = (int)pos.y;
}

void Camera::SetWidth(int w)
{
	camera->w = w;
}

void Camera::SetHeight(int h)
{
	camera->h = h;
}

void Camera::MoveCamera(vec2 displacement)
{
	SetPosition(GetPosition() + displacement);
}

void Camera::CenterAroundPosition(vec2 _pos)
{

}