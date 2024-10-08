//
// created by yzm on 2024/10/7
//

#include "tree.h"

Tree::Tree()
{
    m_root_node = new Node();
}

void Tree::Post(Node* node, std::function<void(Node*)> func)
{
    for(auto& child:node->children())
    {
        Post(child, func);
    }
    if(node!=m_root_node)
    {
        func(node);
    }
}

Tree::~Tree()
{

}

void Tree::Find(Node* node, std::function<bool(Node*)> func, Node** node_result=nullptr)
{
    for(auto child:node->children())
    {
        Find(child, func,node_result);
        if(*node_result!=nullptr)
        {
            break;
        }
    }

    if(*node_result!=nullptr)
    {
        return;
    }

    if(func(node))
    {
        (*node_result) = node;
    }
}