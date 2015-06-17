#include "AssassinationLayer.h"
#include "SimpleAudioEngine.h" 
#include "StartScene.h"
#include "Player.h"

USING_NS_CC;

bool AssassinationLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::RED)) //»¡°£»ö ¼¼ÆÃ
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();

    auto classRoom = Sprite::create("Resources/ClassRoom.png");
    classRoom->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(classRoom);

    auto background = MenuItemImage::create(
        "Resources/Red.png",
        "Resources/Red.png",
        CC_CALLBACK_1(AssassinationLayer::VoidFunc, this));

    auto menu0 = Menu::create(background, false);
    menu0->setAnchorPoint(Point(0, 0));
    menu0->setPosition(winSize.width / 2, winSize.height / 2);
    menu0->setOpacity(180);
    this->addChild(menu0, 10);

    auto exit = MenuItemImage::create(
        "Resources/Exit.png",
        "Resources/ExitSelected.png",
        CC_CALLBACK_1(AssassinationLayer::menuCallback, this));
    auto menu1 = Menu::create(exit, false);
    menu1->setPosition(1200, 700);
    this->addChild(menu1, 11, "exit");

    InitTeacher();
    InitStudent();

    m_KeyBoardListener = EventListenerKeyboard::create();
    m_KeyBoardListener->onKeyPressed = CC_CALLBACK_2(AssassinationLayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_KeyBoardListener, this);

    float level = (Player::getInstance()->GetEnemyNum()) * 0.05f + 0.3f;
    this->schedule(schedule_selector(AssassinationLayer::Look), level);
    this->schedule(schedule_selector(AssassinationLayer::Check));

    return true;
}

void AssassinationLayer::VoidFunc(cocos2d::Ref* sender)
{
    //void
}

void AssassinationLayer::menuCallback(cocos2d::Ref* sender)
{
    Player::getInstance()->ResetPlayerPos();
    this->getParent()->removeChild(this, false);
}

void AssassinationLayer::InitTeacher()
{
    m_TeacherState = T_NONE;

    auto teacher1 = Sprite::create("Resources/Teacher1.png");
    teacher1->setAnchorPoint(Point(0.5, 0.5));
    teacher1->setPosition(400, 500);
    
    auto teacher2 = Sprite::create("Resources/Teacher_Look1.png");
    teacher2->setAnchorPoint(Point(0.5, 0.5));
    teacher2->setPosition(400, 500);
    teacher2->setVisible(false);

    auto teacher3 = Sprite::create("Resources/Teacher_Look2.png");
    teacher3->setAnchorPoint(Point(0.5, 0.5));
    teacher3->setPosition(400, 500);
    teacher3->setVisible(false);

    auto teacher4 = Sprite::create("Resources/Teacher_Look3.png");
    teacher4->setAnchorPoint(Point(0.5, 0.5));
    teacher4->setPosition(400, 500);
    teacher4->setVisible(false);

    auto teacherChat = Sprite::create("Resources/Teacher_Chat.png");
    teacherChat->setPosition(700, 600);
    teacherChat->setVisible(false);
    this->addChild(teacherChat, 12, "chat");

    m_TeacherSprite.push_back(teacher1);
    m_TeacherSprite.push_back(teacher2);
    m_TeacherSprite.push_back(teacher3);
    m_TeacherSprite.push_back(teacher4);

    for (auto sprite : m_TeacherSprite)
    {
        sprite->setScale(2.0f);
        this->addChild(sprite, 20);
    }
}

void AssassinationLayer::Look(float dt)
{
    if (m_TeacherState == T_DETECT)
        return;
    if ((Player::getInstance()->IsKillComplete()))
        return;

    int randNum = rand() % 10;
    switch (m_TeacherState)
    {
    case T_NONE:
        if (randNum >= 4)
        {
            m_TeacherState = T_GLANCE;
            m_TeacherSprite[0]->setVisible(false);
            m_TeacherSprite[1]->setVisible(true);
        }
        break;
    case T_GLANCE:
        m_TeacherSprite[1]->setVisible(false);
        if (randNum >= 5)
        {
            m_TeacherState = T_STARE;
            m_TeacherSprite[2]->setVisible(true);
        }
        else
        {
            m_TeacherState = T_NONE;
            m_TeacherSprite[0]->setVisible(true);
        }
        break;
    case T_STARE:
        m_TeacherState = T_NONE;
        m_TeacherSprite[2]->setVisible(false);
        m_TeacherSprite[0]->setVisible(true);
        break;
    case T_DETECT:
        break;
    }
}

void AssassinationLayer::InitStudent()
{
    auto student = Sprite::create("Resources/Student.png");
    student->setPosition(150, 250);
    student->setScale(1.8f);
    this->addChild(student, 20);

    auto player = Player::getInstance();
    auto playerSprite0 = Sprite::create("Resources/Student.png");
    playerSprite0->setPosition(player->GetPlayerPos());
    playerSprite0->setVisible(false);
    playerSprite0->setScale(1.8f);

    auto playerSprite1 = Sprite::create("Resources/Student_Work1.png");
    playerSprite1->setPosition(player->GetPlayerPos());
    playerSprite1->setVisible(true);

    auto playerSprite2 = Sprite::create("Resources/Student_Work2.png");
    playerSprite2->setPosition(player->GetPlayerPos());
    playerSprite2->setVisible(false);

    m_PlayerSprite.push_back(playerSprite0);
    m_PlayerSprite.push_back(playerSprite1);
    m_PlayerSprite.push_back(playerSprite2);

    for (auto sprite : m_PlayerSprite)
    {
        this->addChild(sprite, 20);
    }
}

void AssassinationLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if ((Player::getInstance()->IsKillComplete()) || m_TeacherState == T_DETECT)
        return;
    if (Player::getInstance()->GetPlayerPos().x <= 200)
        return;

    auto player = Player::getInstance();
    if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        m_PlayerSprite[0]->setVisible(false);
        if (player->GetState() == P_STAND2 || player->GetState() == P_SIT)
        {
            player->SetPlayerState(P_STAND1);
            m_PlayerSprite[1]->setVisible(false);
            m_PlayerSprite[2]->setVisible(true);
        }
        else
        {
            player->SetPlayerState(P_STAND2);
            m_PlayerSprite[2]->setVisible(false);
            m_PlayerSprite[1]->setVisible(true);
        }
        player->Move();
        for (auto sprite : m_PlayerSprite)
        {
            sprite->setPosition(player->GetPlayerPos());
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        player->SetPlayerState(P_SIT);
        m_PlayerSprite[0]->setVisible(true);
        m_PlayerSprite[1]->setVisible(false);
        m_PlayerSprite[2]->setVisible(false);
    }
    else
        return;
}

void AssassinationLayer::Check(float dt)
{
    if (Player::getInstance()->GetPlayerPos().x <= 200)
    {
        _eventDispatcher->removeEventListener(m_KeyBoardListener);
        unschedule(schedule_selector(AssassinationLayer::Check));
        Player::getInstance()->SetIsKillComplete(true);
        Player::getInstance()->ResetPlayerPos();
        Player::getInstance()->SetIsSharp(false);
        Player::getInstance()->ResetSharpGauge();
        Assassinate();
    }

    if (Player::getInstance()->GetState() != P_SIT && m_TeacherState == T_STARE)
    {
        _eventDispatcher->removeEventListener(m_KeyBoardListener);
        unschedule(schedule_selector(AssassinationLayer::Check));
        m_TeacherState = T_DETECT;
        m_TeacherSprite[2]->setVisible(false);
        m_TeacherSprite[3]->setVisible(true);
        this->getChildByName("chat")->setVisible(true);
        Player::getInstance()->ResetPlayerPos();
        Player::getInstance()->ResetSharpGauge();

        this->removeChildByName("exit");
        this->schedule(schedule_selector(AssassinationLayer::GameOver), 3.0f);;
    }
}

void AssassinationLayer::Assassinate()
{
    auto background = MenuItemImage::create(
        "Resources/Red.png",
        "Resources/Red.png",
        CC_CALLBACK_1(AssassinationLayer::VoidFunc, this));

    auto menu0 = Menu::create(background, false);
    menu0->setAnchorPoint(Point(0, 0));
    menu0->setPosition(640, 400);
    menu0->setOpacity(240);
    this->addChild(menu0, 50);

    auto player1 = Sprite::create("Resources/Student_Smile1.png");
    player1->setAnchorPoint(Point(0.5, 0.5));
    player1->setScale(5.0f);
    player1->setPosition(700, 300);
    this->addChild(player1, 52);

    auto player2 = Sprite::create("Resources/Student_Smile2.png");
    player2->setAnchorPoint(Point(0.5, 0.5));
    player2->setScale(5.0f);
    player2->setPosition(700, 300);
    this->addChild(player2, 52);

    auto action0 = FadeTo::create(0.01f, 0);
    auto action1 = FadeTo::create(0.3f, 0);
    auto action2 = DelayTime::create(0.5f);
    auto action3 = FadeTo::create(0.3f, 255);
    auto action4 = FadeTo::create(0.01f, 255);

    player1->runAction(Sequence::create(action0, action2, action3, action2, action1, false));
    player2->runAction(Sequence::create(action0, action2, action1, action2, action3, action1, false));

    this->schedule(schedule_selector(AssassinationLayer::CutScene), 2.5f);
   
}

void AssassinationLayer::CutScene(float dt)
{
    auto background = MenuItemImage::create(
        "Resources/Red.png",
        "Resources/Red.png",
        CC_CALLBACK_1(AssassinationLayer::VoidFunc, this));

    auto menu0 = Menu::create(background, false);
    menu0->setAnchorPoint(Point(0, 0));
    menu0->setPosition(640, 400);
    this->addChild(menu0, 100);

    auto student = Sprite::create("Resources/Student.png");
    student->setScale(5.0f);
    student->setAnchorPoint(Point(0.5, 0));
    student->setPosition(640, 100);
    student->runAction(Sequence::create(DelayTime::create(0.4f), FadeTo::create(0.1f, 0), false));
    this->addChild(student, 101);

    auto cut1 = Sprite::create("Resources/KillCut1.png");
    cut1->setAnchorPoint(Point(0.5, 0));
    cut1->setPosition(640, 0);
    cut1->runAction(Sequence::create(DelayTime::create(0.4f), FadeTo::create(0.1f, 0), false));
    this->addChild(cut1, 102);

    auto cut2 = Sprite::create("Resources/KillCut2.png");
    cut2->setAnchorPoint(Point(0, 0));
    cut2->setPosition(0, 0);
    cut2->setOpacity(0);
    cut2->runAction(Sequence::create(DelayTime::create(0.8f), FadeTo::create(0.1f, 255), false));
    this->addChild(cut2, 103);

    auto cut3 = Sprite::create("Resources/KillCut3.png");
    cut3->setAnchorPoint(Point(0, 0));
    cut3->setPosition(0, 0);
    cut3->setOpacity(0);
    cut3->runAction(Sequence::create(DelayTime::create(1.2f), FadeTo::create(0.1f, 255), false));
    this->addChild(cut3, 104);

    auto cut4 = Sprite::create("Resources/KillCut4.png");
    cut4->setAnchorPoint(Point(0, 0));
    cut4->setPosition(0, 0);
    cut4->setOpacity(0);
    cut4->runAction(Sequence::create(DelayTime::create(1.6f), FadeTo::create(0.1f, 255), false));
    this->addChild(cut4, 105);

    auto cut5 = Sprite::create("Resources/KillCut5.png");
    cut5->setAnchorPoint(Point(0, 0));
    cut5->setPosition(0, 0);
    cut5->setOpacity(0);
    cut5->runAction(Sequence::create(DelayTime::create(2.0f), FadeTo::create(0.1f, 255), false));
    this->addChild(cut5, 106);

    auto cut6 = Sprite::create("Resources/KillCut6.png");
    cut6->setAnchorPoint(Point(0, 0));
    cut6->setPosition(0, 0);
    cut6->setOpacity(0);
    cut6->runAction(Sequence::create(DelayTime::create(2.4f), FadeTo::create(0.1f, 255), false));
    this->addChild(cut6, 107);

    auto cut7 = Sprite::create("Resources/KillCut7.png");
    cut7->setAnchorPoint(Point(0, 0));
    cut7->setPosition(0, 0);
    cut7->setOpacity(0);
    cut2->runAction(Sequence::create(DelayTime::create(2.8f), FadeTo::create(0.1f, 255), false));
    this->addChild(cut7, 108);

    this->schedule(schedule_selector(AssassinationLayer::RemoveLayer), 3.0f);
}

void AssassinationLayer::RemoveLayer(float dt)
{
    this->getParent()->removeChild(this, true);
}

void AssassinationLayer::GameOver(float dt)
{
    auto gameOver = MenuItemImage::create(
        "Resources/GameOver.png",
        "Resources/GameOver.png",
        CC_CALLBACK_1(AssassinationLayer::VoidFunc, this));

    auto menu = Menu::create(gameOver, false);
    gameOver->setAnchorPoint(Point(0.5, 0.5));
    gameOver->setPosition(0, 0);

    this->addChild(menu, 1000);

    auto replay = MenuItemImage::create(
        "Resources/Replay.png",
        "Resources/ReplaySelected.png",
        CC_CALLBACK_1(AssassinationLayer::Replay, this));
    auto menu1 = Menu::create(replay, false);
    menu1->setAnchorPoint(Point(0.5, 0.5));
    menu1->setPosition(1150, 100);
    this->addChild(menu1, 10000);
}

void AssassinationLayer::Replay(cocos2d::Ref* sender)
{
    Player::getInstance()->ResetPlayerPos();
    Player::getInstance()->ResetSharpGauge();
    Player::getInstance()->SetIsSharp(false);
    Director::getInstance()->replaceScene(StartScene::createScene());
}

