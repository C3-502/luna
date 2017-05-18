#ifndef COMMON_DEF_H
#define COMMON_DEF_H

// if someday i have to implition luna_list myself
#define DEF_LUNA_LIST \
    #include <vector> \
    using std::vector = LunaList;

#endif // COMMON_DEF_H
