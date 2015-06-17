#include "Player.h"

USING_NS_CC;

Player::Player()
:m_IsPencilSharp(false), m_PencilSharpGauge(0), m_PlayerPos(1100, 250), m_IsKillComplete(false)
{
}


Player::~Player()
{
}

Player* Player::m_Instance = nullptr;

Player* Player::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new Player;
    }

    return m_Instance;
}

void Player::releaseInstance()
{
    if (m_Instance != nullptr)
    {
        delete m_Instance;
        m_Instance = nullptr;
    }
}

void Player::Move()
{
    m_PlayerPos.x -= 20;
}
