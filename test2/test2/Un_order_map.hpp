//
//  Un_order_map.hpp
//  test2
//
//  Created by CD-a8389742a on 2023/04/19.
//

#ifndef Un_order_map_hpp
#define Un_order_map_hpp

#include <iostream>
#include <functional>
#include "Node.hpp"

#define PRIME_IDX_CNT 30

template<typename F, typename B>
class Un_order_map
{
public:
    Node<F,B>** pNodes_ = nullptr;
    size_t size_ = 0;
    int primeIntIdx_ = 0;
    int primeInt_[PRIME_IDX_CNT] { 2, 5, 11, 23, 47, 97, 197, 397, 797, 1597,
        3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117, 1646237,
        3292489, 6584983, 13169977, 26339969, 52679969, 105359939, 210719881, 421439783, 842879579, 1685759167};
    
public:
    size_t hashTable(F first)
    {
        std::hash<F> hashIdx;
        size_t capacity = (size_t)getCapacity();
        size_t idx = hashIdx(first) % capacity;
        return idx;
    }
    
    int count(F first)
    {
        int idx = hashTable(first);
        if(pNodes_[idx] == nullptr)
            return 0;
        
        return 1;
    }
    
    bool insert(std::pair<F, B> element)
    {
        int capacity = getCapacity();
        
        //일정사이즈가 넘어가면 배열의 사이즈를 늘린다.
        if(0.75f <= size_ / (float)capacity)
        {
            expandArrSize();
        }
        
        size_t idx = hashTable(element.first);
        
        //해당 인덱스에 값이 있는지 확인하고 있다면 추가할 수 있는지 확인한다.
        Node<F,B>* pNode = pNodes_[idx];
        
        if(pNode)
        {
            bool ret = pNode->addNext(element);
            if(ret)
            {
                size_ += 1;
            }
            
            return ret;
        }
        else
        {
            //추가
            pNodes_[idx] = new Node(element);
            size_ += 1;
        }
        
        return true;
    }
    
    void expandArrSize()
    {
        primeIntIdx_ += 1;
        
        int beforeCapacity = getCapacityInner(primeIntIdx_ - 1);
        int curCapacity = getCapacityInner(primeIntIdx_);
        
        if(curCapacity == -1)
        {
            --primeIntIdx_;
            return;
        }
        
        Node<F,B>** p = new Node<F,B>*[curCapacity];
        
        for(size_t i = 0; i < beforeCapacity; ++i)
        {
            Node<F,B>* pNode = pNodes_[i];
            if(pNode == nullptr)
                continue;
            
            //링크드리스트로 연결이 되어 있다면 연결되어 있는 모든 노드를 넣어준다.
            while(pNode != nullptr)
            {
                //해당 인덱스에 값이 있는지 확인
                size_t idx = hashTable(pNode->element_.first);
                Node<F,B>* pTarget = p[idx];
                
                if(pTarget != nullptr)
                {
                    pTarget->addNext(pNode);
                }
                else
                {
                    p[idx] = pNode;
                }
                
                pNode = pNode->pNextNode_;
            }
            
            pNodes_[i] = nullptr;
        }
        
        delete[] pNodes_;
        pNodes_ = p;
    }
    
    bool erase(F first)
    {
        size_t idx = hashTable(first);
        Node<F, B>* pHeadNode = pNodes_[idx];
        
        if(pHeadNode == nullptr)
            return false;

        //헤드원소인 경우
        if(pHeadNode->compareFirst(first))
        {
            Node<F, B>* pNextNode = pNodes_[idx]->pNextNode_;
            
            delete pHeadNode;
            pHeadNode = nullptr;
            --size_;
            
            if(pNextNode == nullptr)
                return true;

            pNextNode->pPreveNode_ = nullptr;
            pNodes_[idx] = pNextNode;
            return true;
        }
        
        Node<F, B>* pTargetNode = pHeadNode->pNextNode_;
        //해당하는 키가 없다면 삭제 불가능
        while(pTargetNode != nullptr)
        {
            //해당키와 일치하면 while문을 통과
            if(pTargetNode->compareFirst(first))
            {
                //삭제할노드의 이전노드와 다음노드를 연결
                pTargetNode->pPreveNode_->pNextNode_ = pTargetNode->pNextNode_;
                
                delete pTargetNode;
                
                --size_;
                return true;
            }
            
            pTargetNode = pTargetNode->pNextNode_;
        }
        
        return false;
    }
    
    bool empty()
    {
        return (int)size_ == 0;
    }
    
    size_t size()
    {
        return size_;
    }
    
    Node<F,B>* find(F first)
    {
        size_t idx = hashTable(first);
        
        Node<F,B>* curNode = pNodes_[idx];
        Node<F,B>* pTargetNode = curNode->getNode(first);
        return pTargetNode;
    }
    
    Node<F,B>* operator[](F first)
    {
        Node<F,B>* result = find(first);
        return result;
    }
    
    int getCapacity()
    {
        int ret = getCapacityInner(primeIntIdx_);
        return ret;
    }
    
private:
    int getCapacityInner(int primeIdx)
    {
        if(primeIdx >= PRIME_IDX_CNT || primeIdx < 0)
            return -1;
        
        int result = primeInt_[primeIdx];
        return result;
    }

public:
    Un_order_map()
    {
        size_t capacity = getCapacity();
        pNodes_ = new Node<F,B>*[capacity]{ nullptr,  };
    }
    
    //할당 해제
    ~Un_order_map()
    {
        size_t capacity = getCapacity();
        for(size_t i = 0; i < capacity; ++i)
        {
            if(pNodes_[i] != nullptr)
            {
                pNodes_[i]->deleteNode();
                delete pNodes_[i];
                pNodes_[i] = nullptr;
            }
        }
    }
};


#endif /* Un_order_map_hpp */
