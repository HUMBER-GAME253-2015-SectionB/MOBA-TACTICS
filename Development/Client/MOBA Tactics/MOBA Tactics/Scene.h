//Author:	David Vo, Nicholas Higa
//Date:		2/23/2015(DV), 3/30/2015(NH)

#pragma once

#include "IScene.h"
#include "ClientAPI.h"
#include "SceneStateManager.h"
#include "EventManager.h"
#include "PlayerState.h"

class Scene : public IScene
{
public:
	Scene();
	~Scene();

	void Init();
	void LoadContent();
	void UnloadContent();
	void OnEvent(SDL_Event *event);
	void UpdateInput(SDL_Event *event);
	void Update();
	void Draw();
	void Exit();

	//Delete after debug
	vec2 minBound, maxBound;
	Sprite *tmp1, *tmp2, *tmp3, *tmp4;

	int GetCurrentPlayer();
	void SetCurrentPlayer(int);

	int GetNumPlayers();
	void SetNumPlayers(int);

private:
	static SceneStateManager sceneStateManager;
	int currentPlayer;
	int numPlayers;
};