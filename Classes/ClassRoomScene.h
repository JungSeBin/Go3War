#ifndef __CLASSROOM_SCENE_H__
#define __CLASSROOM_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Students;
class ClassRoomScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void VoidFunc(cocos2d::Ref* sender);
    void menuCallBack0(cocos2d::Ref* sender);
    void menuCallBack1(cocos2d::Ref* sender);
    void Replay(cocos2d::Ref* sender);

    void AddStudents();
    void GameOver();
    void GameEnding();

    void Update(float dt);
    void Tick(float dt);
    void UpdateDday();

    void KillComplete();

    CREATE_FUNC(ClassRoomScene);

private:
    Students*   m_Students;
    Sprite*     m_RedEffect;
    int         m_Dday;
    int         m_Hour;
    int         m_Min;
};

#endif