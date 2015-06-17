#pragma once

#include <vector>
#include "cocos2d.h"

USING_NS_CC;

enum TeacherState
{
    T_NONE,
    T_GLANCE,
    T_STARE,
    T_DETECT
};

class AssassinationLayer : public LayerColor
{
public:
    virtual bool    init();

    void            VoidFunc(cocos2d::Ref* sender);
    void            menuCallback(cocos2d::Ref* sender);
    void            Replay(cocos2d::Ref* sender);
    void            InitTeacher();
    void            InitStudent();
    void            Assassinate();
    void            CutScene(float dt);
    void            Look(float dt);
    void            Check(float dt);
    void            RemoveLayer(float dt);
    void            GameOver(float dt);

    virtual void    onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    CREATE_FUNC(AssassinationLayer);

private:
    std::vector<Sprite*>    m_TeacherSprite;
    std::vector<Sprite*>    m_PlayerSprite;
    TeacherState            m_TeacherState;

    EventListenerKeyboard*  m_KeyBoardListener;

};