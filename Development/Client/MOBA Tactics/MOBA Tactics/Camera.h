//Author:	Nicholas Higa
//Date:		3/15/2015 (NH)

#include <SDL.h>
#include <vector>
#include <glm/glm.hpp>
#include "Sprite.h"

using namespace std;
using namespace glm;

class Camera
{
public:
	Camera(SDL_Renderer *renderer, vec2 pos, int width, int height);
	void Draw(SDL_Renderer *ren);
	void Update();
	void AddToDrawList(Sprite *item);
	void RemoveFromDrawList(Sprite *item);

	SDL_Rect* GetCamera();
	SDL_Renderer* GetRenderer();
	vec2 GetPosition();
	int GetWidth();
	int GetHeight();
	vec2 GetDrawablePosOnScreen(Sprite *item);

	void SetCamera(SDL_Rect *cam);
	void SetRenderer(SDL_Renderer *renderer);
	void SetPosition(vec2 pos);
	void SetWidth(int w);
	void SetHeight(int h);

	void MoveCamera(vec2 displacement);
	void CenterAroundPosition(vec2 _pos);
private:
	SDL_Rect* camera;
	SDL_Renderer* ren;
	vector<Sprite*> drawList;
};