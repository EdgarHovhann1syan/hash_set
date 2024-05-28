#include "hash_set.h"

std::size_t hash_set::hash(int val)
{
    return (val * 31);
}
hash_set::hash_set() : totalNumberOfSlotsInHashtable(10), m_elems(10, nullptr), numberOfItemsInHashtable(0)
{
    for (int i = 0; i < totalNumberOfSlotsInHashtable; i++)
    {
        m_elems[i] = new SLL();
    }
}

void hash_set::insert(int val)
{
    if(loadFactor >= 0.7)
    {
        rehash();
    }
    int ind = hash(val) % totalNumberOfSlotsInHashtable;
    m_elems[ind]->push_front(val);
    ++numberOfItemsInHashtable;
    loadFactor = numberOfItemsInHashtable / totalNumberOfSlotsInHashtable;
}

void hash_set::remove(int val) {
    int idx = hash(val)% totalNumberOfSlotsInHashtable;
    SLL::Node* current = m_elems[idx]->head();
    SLL::Node* prev = nullptr;

    while (current != nullptr) {
        if (current->m_data == val) {
            if (prev == nullptr) {
                m_elems[idx]->m_head = current->m_next;
                delete current;
                current = m_elems[idx]->head();
            } else {
                prev->m_next = current->m_next;
                SLL::Node* temp = current;
                current = current->m_next; 
                delete temp;
            }
            --numberOfItemsInHashtable;
        } else {
            prev = current;
            current = current->m_next;
        }
    }
    loadFactor = static_cast<double>(numberOfItemsInHashtable / totalNumberOfSlotsInHashtable);

}


bool hash_set::contains(int val)
{
    int ind = hash(val) % totalNumberOfSlotsInHashtable;
    SLL::Node* current = m_elems[ind]->head();
    while(current)
    {
        if(current->m_next->m_data == val)
        {
            return true;
        }
        current = current->m_next;
    }
    return false;
}

void hash_set::print()
{
    for (int i = 0; i < totalNumberOfSlotsInHashtable; i++)
    {
        m_elems[i]->print();
    }
}

std::size_t hash_set::size()
{
    return numberOfItemsInHashtable;
}

void hash_set::rehash()
{
    std::vector<SLL*> newElems(totalNumberOfSlotsInHashtable * 2, nullptr);
    for(int i = 0; i < newElems.size(); ++i)
    {
        newElems[i] = new SLL;
    }
    for(int i = 0; i < totalNumberOfSlotsInHashtable; ++i)
    {
        SLL::Node* current = m_elems[i]->head();
        while(current != nullptr)
        {
            int idx = hash(current->m_data) % newElems.size();
            newElems[idx]->push_front(current->m_data);
            current = current->m_next;
        }
    }
    m_elems = newElems;
    totalNumberOfSlotsInHashtable *= 2;
    loadFactor = numberOfItemsInHashtable / totalNumberOfSlotsInHashtable;
}



