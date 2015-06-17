#pragma once

#include "cocos2d.h"

USING_NS_CC;

class PencilLayer : public LayerColor
{
public:
    virtual bool init();

    void            VoidFunc(cocos2d::Ref* sender);
    void            menuCallback(cocos2d::Ref* sender);

    virtual void    OnMouseMove(Event* event);
    virtual void    OnMouseDown(Event* event);
    virtual void    OnMouseUp(Event* event);

    CREATE_FUNC(PencilLayer);

private:
    Point   m_MousePos;
};