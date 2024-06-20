#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H
 
#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int sizeList;
        int sizeArray;

    public:
        objPosArrayList();
        ~objPosArrayList();

        int getSize() const;
        void insertHead(const objPos& thisPos);
        void insertTail(const objPos& thisPos);
        void removeHead();
        void removeTail();

        void getHeadElement(objPos& returnPos) const;
        void getTailElement(objPos& returnPos) const;
        void getElement(objPos& returnPos, int index) const;
};

#endif