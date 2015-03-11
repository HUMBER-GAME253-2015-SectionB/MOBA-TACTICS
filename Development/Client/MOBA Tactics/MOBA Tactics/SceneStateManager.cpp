//Author:	Mathieu Violette
//Date:		3/10/2015(MV)

#include "SceneStateManager.h"

SceneStateManager& SceneStateManager::GetInstance()
{
	static SceneStateManager instance;
	return instance;
}

SceneStateManager::SceneStateManager()
{
	currentState = SceneState::NONE;
	queuedState = currentState;
}

SceneStateManager::~SceneStateManager()
{
}

SceneState SceneStateManager::GetSceneState() const
{
	return currentState;
}

void SceneStateManager::UpdateSceneState()
{
	if (queuedState != currentState)
	{
		
	}
}
	
void SceneStateManager::QueueChangeToSceneState(SceneState _newSceneState)
{
	if (queuedState != _newSceneState)
		queuedState = _newSceneState;
}