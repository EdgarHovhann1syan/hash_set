#include "hash_set.h"
#include <iostream>
int main()
{
    hash_set set;
    set.insert(1);
    set.insert(2);
    set.insert(2);
    set.insert(2);
    set.remove(1);
    set.print();
    std::cout << set.size() << std::endl;

    return 0;
}