#pragma once

#include <vector>
#include "cocos2d.h"

USING_NS_CC;

class Students
{
public:
    Students();
    ~Students();

    void    Init();
    void Die();

    Sprite* GetStudent(int i){ return m_StudentList[i]; }
    int     GetAllNum(){ return m_AllNum; }
    int     GetAliveNum(){ return m_AliveNum; }
private:
    std::vector<Sprite*>    m_StudentList;
    std::vector<int>        m_DieList;
    int                     m_AllNum;
    int                     m_AliveNum;
};