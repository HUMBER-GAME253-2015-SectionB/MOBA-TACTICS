//Author:	Nicholas Higa
//Date:		3/15/2015 (NH), 3/24/2015(NH)

#include "Camera.h"

//Position refers to the top left of the camera

Camera::Camera(SDL_Renderer *renderer, vec2 pos, int width, int height, vec2 minBoundary, vec2 maxBoundary) 
{
	new (this) Camera(renderer, pos, width, height, minBoundary, maxBoundary, 0.8f, 2.0f);
}

Camera::Camera(SDL_Renderer *renderer, vec2 pos, int width, int height, vec2 minBoundary, vec2 maxBoundary, float minScale, float maxScale)
{
	SetRenderer(renderer);
	SDL_Rect *rect = new SDL_Rect();
	rect->x = (int)pos.x;
	rect->y = (int)pos.y;
	rect->w = width;
	rect->h = height;
	SetCamera(rect);
	SetMinBounds(minBoundary);
	SetMaxBounds(maxBoundary);
	SetBaseVelocity(vec2(20, 20)); //Change later
	SetMinScale(minScale);
	SetMaxScale(maxScale);
	SetScale(1.0f);
}

void Camera::Draw(SDL_Renderer *ren)
{
	SDL_RenderSetScale(ren, scale, scale);
	for (unsigned i = 0; i < drawList.size(); i++)
		drawList[i]->Draw(drawList[i]->GetPosition() - GetPosition(), ren);
}

void Camera::Update()
{
	if (GetIsMoving())
	{
		SetPosition(lerp(startPosition, targetPosition, increment));
		increment += 0.02;

		if (increment.x >= 1)
		{
			SetIsMoving(false);
		}
	}
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

void Camera::CentreOn(vec2 _pos)
{
	if (!isMoving)
	{
		increment = vec2(0.02, 0.02);
		SetIsMoving(true);
		SetTargetPosition((GetPosition() + _pos) - vec2(GetWidth() / 2, GetHeight() / 2));
		SetStartPosition(GetPosition());
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

	return vec2(-999999999, -999999999); //If sprite not found, return really negative value
}

vec2 Camera::GetBaseVelocity()
{
	return baseVelocity;
}

vec2 Camera::GetMinBounds()
{
	return minBounds;
}

vec2 Camera::GetMaxBounds()
{
	return maxBounds;
}

float Camera::GetMinScale()
{
	return minScale;
}

float Camera::GetMaxScale()
{
	return maxScale;
}

float Camera::GetScale()
{
	return scale;
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

void Camera::SetBaseVelocity(vec2 vel)
{
	baseVelocity = vel;
}

void Camera::SetMinBounds(vec2 val)
{
	minBounds = val;
}

void Camera::SetMaxBounds(vec2 val)
{
	maxBounds = val;
}

void Camera::SetMinScale(float val)
{
	minScale = val;
}

void Camera::SetMaxScale(float val)
{
	maxScale = val;
}

void Camera::SetScale(float val)
{
	if (val < GetMaxScale() && val > GetMinScale())
		scale = val;
	else if (val > GetMaxScale())
		scale = GetMaxScale();
	else if (val < GetMinScale())
		scale = GetMinScale();
}

void Camera::MoveCamera(vec2 displacement)
{
	vec2 temp = GetPosition();
	vec2 minBoundary = GetMinBounds();	
	vec2 maxBoundary = GetMaxBounds();

	if (displacement.x <= 0 && temp.x + displacement.x >= minBoundary.x)
		SetPosition(vec2(temp.x + displacement.x, temp.y));
	else if (displacement.x <= 0 && temp.x + displacement.x < minBoundary.x)
		SetPosition(vec2(minBoundary.x, temp.y));

	if (displacement.x > 0 && temp.x + displacement.x + GetWidth() <= maxBoundary.x)
		SetPosition(vec2(temp.x + displacement.x, temp.y));
	else if (displacement.x > 0 && temp.x + displacement.x + GetWidth() > maxBoundary.x)
		SetPosition(vec2(maxBoundary.x - GetWidth(), temp.y));
	
	if (displacement.y <= 0 && temp.y + displacement.y >= minBoundary.y)
		SetPosition(vec2(GetPosition().x, GetPosition().y + displacement.y));
	else if (displacement.y <= 0 && temp.y + displacement.y < minBoundary.y)
		SetPosition(vec2(temp.x, minBoundary.y));

	if (displacement.y > 0 && temp.y + displacement.y + GetHeight() <= maxBoundary.y)
		SetPosition(vec2(temp.x, temp.y + displacement.y));
	else if (displacement.y > 0 && temp.y + displacement.y + GetHeight() > maxBoundary.y)
		SetPosition(vec2(temp.x, maxBoundary.y - GetHeight()));
}

void Camera::SetIsMoving(bool _isMoving)
{
	isMoving = _isMoving;
}

bool Camera::GetIsMoving()
{
	return isMoving;
}

void Camera::SetCurrentVelocity(vec2 vel)
{
	currentVelocity = vel;
}

vec2 Camera::GetCurrentVelocity()
{
	return currentVelocity;
}

void Camera::SetTargetPosition(vec2 targetPos)
{
	targetPosition = targetPos;
}

vec2 Camera::GetTargetPosition()
{
	return targetPosition;
}

void Camera::SetStartPosition(vec2 pos)
{
	startPosition = pos;
}

vec2 Camera::GetStartPosition()
{
	return startPosition;
}