#pragma once
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

enum PlayerState
{
    P_NONE,
    P_STAND1,
    P_STAND2,
    P_SIT
};
class Player
{
public:
    Player();
    ~Player();

    static Player*  getInstance();
    void            releaseInstance();

    void            UpSharpGauge(){ m_PencilSharpGauge++; }
    void            ResetSharpGauge(){ m_PencilSharpGauge = 0; }
    void            SetIsSharp(bool isSharp){ m_IsPencilSharp = isSharp; }
    void            SetIsKillComplete(bool isKillComplete){ m_IsKillComplete = isKillComplete; }
    void            SetPlayerState(PlayerState state){ m_State = state; }
    void            SetEnemyNum(int enemyNum){ m_EnemyNum = enemyNum; }
    void            Move();
    void            ResetPlayerPos(){ m_PlayerPos.x = 1100; }

    int             GetSharpGauge(){ return m_PencilSharpGauge; }
    int             GetEnemyNum(){ return m_EnemyNum; }
    PlayerState     GetState(){ return m_State; }
    Point           GetPlayerPos(){ return m_PlayerPos; }
    bool            IsPencilSharp(){ return m_IsPencilSharp; }
    bool            IsKillComplete(){ return m_IsKillComplete; }

private:
    Point                   m_PlayerPos;
    static Player*          m_Instance;
    PlayerState             m_State;
    int                     m_PencilSharpGauge;
    bool                    m_IsPencilSharp;
    bool                    m_IsKillComplete;
    int                     m_EnemyNum;
};

