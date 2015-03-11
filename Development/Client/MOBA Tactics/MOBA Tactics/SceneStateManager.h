//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#ifndef SCENESTATE_MANAGER_H
#define SCENESTATE_MANAGER_H

#include "SceneState.h"

class SceneStateManager
{
private:
	SceneStateManager();
	SceneState currentState, queuedState;
public:
	static SceneStateManager& GetInstance();
	~SceneStateManager();
	SceneState GetSceneState() const;
	void UpdateSceneState();
	void QueueChangeToSceneState(SceneState _newGameState);
};

#endif