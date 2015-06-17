#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCallBack(cocos2d::Ref* sender);
    void ReplaceScene(float dt);

    void VoidFunc(cocos2d::Ref* sender);

    CREATE_FUNC(StartScene);
};

#endif