#ifndef HS
#define HS


#include "./SLL/sll.h"
#include <vector>
class hash_set
{
public:
    hash_set();
    void insert(int val);
    void remove(int val);
    bool contains(int val);
    void print();
    std::size_t size();

private:
    std::vector<SLL*> m_elems;
    std::size_t numberOfItemsInHashtable;
    std::size_t totalNumberOfSlotsInHashtable;
    double loadFactor;
    std::size_t hash(int val);
    void rehash();
};


#endif //HS