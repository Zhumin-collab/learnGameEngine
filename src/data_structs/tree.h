//
// created  by yzm on 2024/10/7
//

#ifndef TREE_H
#define TREE_H

#include <list>
#include <functional>

class Tree{
public:
    class Node{
    public:
        virtual ~Node(){}

        Node* parent(){return m_parent;}
        void set_parent(Node* parent){m_parent = parent;}

        std::list<Node*>& children(){return m_children;}

        void add_child(Node* child){
            if(child->parent()!=nullptr){
                child->parent()->RemoveChild(child);
            }
            m_children.push_back(child);
            child->set_parent(this);
        }

        void RemoveChild(Node* child){
            m_children.remove(child);
        }

        bool Empty()
        {
            return m_children.size()>0;
        }
    private:
        Node* m_parent = nullptr;
        std::list<Node*> m_children;
    };

public:
    Tree();
    ~Tree();

    Node* root_node(){return m_root_node;}

    void Post(Node* node, std::function<void(Node*)> func);

    void Find(Node* node, std::function<bool(Node*)> func,Node** node_result);

private:
    Node* m_root_node;

};



#endif // TREE_H