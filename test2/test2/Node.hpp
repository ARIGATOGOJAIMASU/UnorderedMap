//
//  Node.hpp
//  test2
//
//  Created by CD-a8389742a on 2023/04/19.
//

#ifndef Node_hpp
#define Node_hpp

#include <iostream>
template<typename F ,typename B> class Un_order_map;

template<typename F ,typename B>
class Node
{
    friend class Un_order_map<F,B>;
    
private:
    std::pair<F,B> element_;
    Node* pNextNode_ = nullptr;
    Node* pPreveNode_ = nullptr;
    
private:
    Node(std::pair<F, B> element)
    {
        element_.first = element.first;
        element_.second = element.second;
    }
    
    Node(Node* node)
    {
        element_.first = node->element.first;
        element_.second = node->element.second;
    }
    
    bool addNext(std::pair<F, B> element)
    {
        //중복키를 허용x 같은 값이라면 return;
        if(compareFirst(element.first))
            return false;
        
        //현재 끝노드가 아니라면 다음 노드를 검색
        if(pNextNode_ != nullptr)
            return pNextNode_->addNext(element);
        
        //노드를 추가하고 true를 return
        pNextNode_ = new Node(element);
        pNextNode_->pPreveNode_ = this;
        return true;
    }
    
    bool addNext(Node* node)
    {
        //중복키를 허용x 같은 값이라면 return;
        if(compareFirst(node->element_.first))
            return false;
        
        //현재 끝노드가 아니라면 다음 노드를 검색
        if(pNextNode_ != nullptr)
            return pNextNode_->addNext(node);
        
        //노드를 추가하고 true를 return
        pNextNode_ = new Node<F,B>(node->element_);
        pNextNode_->pPreveNode_ = this;
        return true;
    }
    
    bool compareFirst(F first)
    {
        bool result = first == element_.first;
        return result;
    }
    
    Node<F,B>* getNode(F first)
    {
        if(compareFirst(first))
            return this;
        
        //다음 노드부터 검사 실행
        Node<F,B>* pTarget = pNextNode_;
        while(pTarget != nullptr)
        {
            if(pTarget->compareFirst(first))
                return pTarget;
            
            pTarget = pTarget->pNextNode_;
        }
        
        return nullptr;
    }
    
    void deleteNode()
    {
        if(pNextNode_ == nullptr)
            return;
        
        pNextNode_->deleteNode();
        pNextNode_ = nullptr;
        delete pNextNode_;
    }

public:
    B second()
    {
        return element_.second;
    }
};

#endif /* Node_hpp */
