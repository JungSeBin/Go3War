#include "Students.h"


Students::Students()
:m_AllNum(0), m_AliveNum(0)
{
    m_AllNum = 18;
    m_AliveNum = m_AllNum;
    Init();
}


Students::~Students()
{
}

void Students::Init()
{
    int sNum = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            m_StudentList.push_back(Sprite::create("Resources/Student.png"));
            m_StudentList[sNum]->setAnchorPoint(Point(0, 0));
            m_StudentList[sNum]->setPosition(Point(j * 170 + 70, (2 - i) * 150));
            m_StudentList[sNum]->setTag(sNum);
            sNum++;
        }
    }
}

void Students::Die()
{
    if (m_AliveNum <= 0)
        return;

    int dieNum;
    bool isTrue = true;

    while (isTrue)
    {
        if (m_DieList.size() == 0)
            isTrue = false;

        dieNum = rand() % m_AllNum;
        for (auto dieStudent : m_DieList)
        {
            if (dieStudent == dieNum)
            {
                isTrue = true;
                break;
            }
            isTrue = false;
        }
    }

    m_StudentList[dieNum]->runAction(FadeTo::create(1.0f, 0));

    m_DieList.push_back(dieNum);
    m_AliveNum--;
}
