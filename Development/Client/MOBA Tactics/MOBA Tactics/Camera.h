//Author:	Nicholas Higa
//Date:		3/15/2015 (NH), 3/24/2015(NH)

#include "ICamera.h"
#include <SDL.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include "Sprite.h"

using namespace std;
using namespace glm;

class Camera : public ICamera
{
public:
	Camera(SDL_Renderer *renderer, vec2 pos, int width, int height, vec2 minBoundary, vec2 maxBoundary);
	Camera(SDL_Renderer *renderer, vec2 pos, int width, int height, vec2 minBoundary, vec2 maxBoundary, float minScale, float maxScale);
	void Draw(SDL_Renderer *ren);
	void Update();
	void AddToDrawList(Sprite *item);
	void RemoveFromDrawList(Sprite *item);
	void CentreOn(vec2 _pos);

	SDL_Rect* GetCamera();
	SDL_Renderer* GetRenderer();
	vec2 GetPosition();
	int GetWidth();
	int GetHeight();
	vec2 GetDrawablePosOnScreen(Sprite *item);
	vec2 GetBaseVelocity();
	vec2 GetMinBounds();
	vec2 GetMaxBounds();
	float GetMinScale();
	float GetMaxScale();
	float GetScale();

	void SetCamera(SDL_Rect *cam);
	void SetRenderer(SDL_Renderer *renderer);
	void SetPosition(vec2 pos);
	void SetWidth(int w);
	void SetHeight(int h);
	void SetBaseVelocity(vec2);
	void SetMinBounds(vec2);
	void SetMaxBounds(vec2);
	void SetMinScale(float);
	void SetMaxScale(float);
	void SetScale(float);

	void MoveCamera(vec2 displacement);
private:
	SDL_Rect* camera;
	SDL_Renderer* ren;
	vector<Sprite*> drawList;

	vec2 baseVelocity;
	vec2 currentVelocity;
	bool isMoving;

	vec2 increment;
	vec2 targetPosition;
	vec2 startPosition;

	vec2 minBounds, maxBounds; //Min and max of how far the camera can move off screen
	float minScale;
	float maxScale;
	float scale;

	void SetIsMoving(bool);
	bool GetIsMoving();

	void SetCurrentVelocity(vec2);
	vec2 GetCurrentVelocity();

	void SetTargetPosition(vec2);
	vec2 GetTargetPosition();

	void SetStartPosition(vec2);
	vec2 GetStartPosition();
};