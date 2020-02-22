#ifndef FRAMEWORK_OBJECT_H
#define FRAMEWORK_OBJECT_H

#include "FList.hpp"

class FObject {
public:
    FObject();
    virtual ~FObject();
    
    virtual void                            Update() { }
    virtual void                            Draw() { }
    
    virtual void                            Kill();
    int                                     mKill;
};

class FObjectList {
public:
    FObjectList();
    virtual ~FObjectList();
    
    void                                    Add(void *pObject);
    inline void operator                    += (void *pItem) { Add(pItem); }
    
    bool                                    Empty();
    
    void                                    Update();
    void                                    Draw();
    
    void                                    Free();
    void                                    KillAll();
    
    FList                                   mObjectList;
    FList                                   mObjectListTemp;
    FList                                   mObjectListKill;
    FList                                   mObjectListDelete;
};

#endif
