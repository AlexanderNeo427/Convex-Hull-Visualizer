#ifndef _ISCENE_
#define _ISCENE_

#include "../../src/Events.h"
#include <string>
#include <memory>

class SceneManager;

struct IScene
{
	explicit IScene(std::shared_ptr<SceneManager> pSceneManager,
					const std::string& sceneID,
					const int width,
					const int height)
		:
		m_pSceneManager(pSceneManager),
		m_sceneID(sceneID),
		m_width(width), 
		m_height(height)
	{}

	virtual void OnInitialize() {}
	virtual void OnEnable() {}
	virtual void OnUpdate(const float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnDisable() {}
	virtual void OnHandleEvent(const Event& event) {}

	const std::string& SceneID() const
	{
		return m_sceneID;
	}
protected:
	int Width() const { return m_width; }
	int Height() const { return m_height; }
private:
	const int m_width;
	const int m_height;
	const std::string m_sceneID;
	std::shared_ptr<SceneManager> m_pSceneManager;
};

#endif
