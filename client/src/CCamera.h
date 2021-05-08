#pragma once
#include <cmath>
#include <vector>

#include "CClock.h"
#include "CFrameBuffer.h"

#include "./map/CMap.h"
#include "./map/CMapCell.h"

using namespace std;



class CCamera {
private:
    CFrameBuffer* buffer;
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;

    CMap* map;
    CClock* clock;

    void drawEntity();

    double getMoveSpeed();
    double getRotationSpeed();
    bool canMove(bool isForward, CMapCell* cell, CMapCell* cellNext, float diff, double dir) const;
    void moveStraight(bool isForward, double moveSpeed);
public:
    CCamera(CFrameBuffer* buffer, CClock* clock, CMap* map);
    ~CCamera();
    CFrameBuffer* draw();
};