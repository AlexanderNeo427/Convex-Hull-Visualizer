#include "SceneManager.h"

SceneManager::SceneManager()
	:
	m_pCurrentScene(nullptr),
	m_pNextScene(nullptr)
{}

void SceneManager::AddScene(std::shared_ptr<IScene> pScene)
{
	pScene->OnInitialize();
	pScene->OnEnable();
	m_sceneMap.insert({ pScene->SceneID(), pScene });

	if (m_pCurrentScene == nullptr)
	{
		m_pCurrentScene = m_pNextScene = pScene;
	}
}

void SceneManager::OnUpdate(const float deltaTime)
{
	if (m_pCurrentScene != m_pNextScene)
	{
		m_pCurrentScene->OnDisable();
		m_pCurrentScene = m_pNextScene;
		m_pNextScene->OnEnable();
	}
	m_pCurrentScene->OnUpdate(deltaTime);
}

void SceneManager::OnRender()
{
	m_pCurrentScene->OnRender();
}

void SceneManager::LoadScene(const std::string& sceneID)
{
	auto found = m_sceneMap.find(sceneID) != m_sceneMap.end();
	if (found) m_pNextScene = m_sceneMap.at(sceneID);
}