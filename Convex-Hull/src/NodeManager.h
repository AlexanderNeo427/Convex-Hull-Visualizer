#ifndef NODE_MANAGER
#define NODE_MANAGER

#include "Node.h"

struct NodeManager
{
public:
	NodeManager(const std::shared_ptr<Node> root): m_root(root) {}

	void Update(const float deltaTime)
	{
		auto itr = m_root;
		while (itr != nullptr)
		{
			itr->OnUpdate(deltaTime);
			itr = itr->GetActiveChild();
		}
	}
	void PropagateEvent(const Event& evt)
	{
		auto itr = m_root;
		while (itr != nullptr)
		{
			if (itr->HandleEvent(evt)) break;
			itr = itr->GetActiveChild();
		}
	}
private:
	std::shared_ptr<Node> m_root;
};

#endif
