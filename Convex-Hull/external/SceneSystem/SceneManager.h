#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include <unordered_map>
#include <string>
#include <memory>

#include "../../src/Events.h"
#include "IScene.h"

class SceneManager
{
public:
	explicit SceneManager();
	void AddScene(std::shared_ptr<IScene> pScene);
	void OnUpdate(const float deltaTime);
	void OnRender();
	void LoadScene(const std::string& sceneID);
	void OnHandleEvent(const Event& event)
	{
		m_pCurrentScene->OnHandleEvent(event);
	}
private:
	std::unordered_map<std::string, std::shared_ptr<IScene>> m_sceneMap;
	std::shared_ptr<IScene> m_pCurrentScene;
	std::shared_ptr<IScene> m_pNextScene;
};

#endif
