//BrickControl.h
#ifndef BRICK_CONTROL_H
#define BRICK_CONTROL_H

//#include "Brick.h"
#include "SDLUtils.h"
#include "BrickStrong.h"
#include "BrickBeton.h"
#include "BrickPortal.h"
#include <vector>

extern std::vector<Portal*>PortalList;

class BrickControl
{
public:
    static std::vector<Brick*> brickList;
    //static std::vector<Brick*> portalaList;
    //static std::vector<BrickStrong> brickStrongList;
    static bool LoadBricksFromFile(const char*);
    static void delete_bricks();
    BrickControl();
    ~BrickControl();
private:

};

#endif
