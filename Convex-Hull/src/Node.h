#ifndef NODE
#define NODE

#include <vector>
#include <memory>

#include "Events.h"

class Node
{
public:
    Node() 
        :
        m_parentNode(nullptr),
        m_currNode(nullptr)
    {}
    Node(std::shared_ptr<Node> parentNode)
        :
        m_parentNode(std::move(parentNode)),
        m_currNode(nullptr)
    {}

    virtual void OnInitialize() = 0;
    virtual void OnActivate() = 0;
    virtual void OnUpdate(const float deltaTime) = 0;
    virtual void OnDeactivate() = 0;
    virtual bool HandleEvent(const Event& evt) { return false; }
    inline std::shared_ptr<Node> GetActiveChild() const { return m_currNode; }
public:
    void SetParent(std::shared_ptr<Node> parentNode) 
    {
        m_parentNode = parentNode;
    }

    template<class T>
    std::shared_ptr<T> AddChildNode(std::shared_ptr<Node> parent)
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node");

        std::shared_ptr<T> childNode = std::make_shared<T>(parent);
        m_currNode->OnInitialize();
        m_childNodes.emplace_back(childNode);

        if (m_currNode == nullptr)
            m_currNode = childNode;

        return childNode;
    }
private:
    template<class T>
    std::shared_ptr<T> SwitchCurrNode()
    {
        if (std::dynamic_pointer_cast<std::shared_ptr<T>>(m_currNode))
            return;

        for (auto node : m_childNodes)
        {
            auto nextNode = std::dynamic_pointer_cast<std::shared_ptr<T>>(node);
            if (nextNode != nullptr)
            {
                m_currNode->OnDeactivate();
                m_currNode = nextNode;
                m_currNode->OnActivate();
                return nextNode;
            }
        }
        return nullptr;
    }
private:
    std::shared_ptr<Node> m_parentNode;
    std::shared_ptr<Node> m_currNode;
    std::vector<std::shared_ptr<Node>> m_childNodes;
};

#endif

