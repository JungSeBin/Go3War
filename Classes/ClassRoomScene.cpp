#include "ClassRoomScene.h"
#include "PencilLayer.h"
#include "Player.h"
#include "AssassinationLayer.h"
#include "Students.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h" 
#include "EndingScene.h"

USING_NS_CC;

Scene* ClassRoomScene::createScene()
{
    auto scene = Scene::create();

    auto layer = ClassRoomScene::create();

    scene->addChild(layer);

    return scene;
}

bool ClassRoomScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
        "Resources/Horror.mp3", true);

    auto winSize = Director::getInstance()->getWinSize();

    auto black = Sprite::create("Resources/Black.png");
    black->setAnchorPoint(Point(0, 0));
    black->setPosition(0, 0);
    black->runAction(FadeTo::create(1.0f, 0));
    this->addChild(black,400);

    m_RedEffect = Sprite::create("Resources/Red.png");
    m_RedEffect->setAnchorPoint(Point(0, 0));
    m_RedEffect->setPosition(0, 0);
    m_RedEffect->setOpacity(0);
    this->addChild(m_RedEffect, 100);

    auto background = Sprite::create("Resources/ClassRoom.png");
    background->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(background);

    auto test = Sprite::create("Resources/TestDday.png");
    test->setPosition(650, 650);
    m_Dday = 3;
    this->addChild(test);
    UpdateDday();

    auto teacher0 = Sprite::create("Resources/Teacher0.png");
    teacher0->setAnchorPoint(Point(0.5, 0.5));
    teacher0->setPosition(390, 500);
    this->addChild(teacher0);
    auto teacher1 = Sprite::create("Resources/Teacher1.png");
    teacher1->setAnchorPoint(Point(0.5, 0.5));
    teacher1->setPosition(400, 500);
    this->addChild(teacher1);

    auto action0 = FadeTo::create(0.15f, 0);
    auto action1 = DelayTime::create(0.5f);
    auto action2 = FadeTo::create(0.15f, 255);
    auto action3 = Sequence::create(action0, action1, action2, action1, false);
    auto action4 = Sequence::create(action2, action1, action0, action1, false);

    teacher0->runAction(RepeatForever::create(action3));
    teacher1->runAction(RepeatForever::create(action4));

    m_Students = new Students;
    AddStudents();

    auto pencilButton = MenuItemImage::create(
        "Resources/PencilCut.png",
        "Resources/PencilCutSelected.png",
        CC_CALLBACK_1(ClassRoomScene::menuCallBack0, this));
    auto assassinationButton = MenuItemImage::create(
        "Resources/Assassination.png",
        "Resources/AssassinationSelected.png",
        CC_CALLBACK_1(ClassRoomScene::menuCallBack1, this));
    assassinationButton->setName("assassination");
    auto menu = Menu::create(pencilButton, assassinationButton, false);
    menu->setPosition(1180, 200);
    menu->alignItemsVerticallyWithPadding(70);
    this->addChild(menu,1,"classRoomMenu");

    Player::getInstance()->SetEnemyNum(m_Students->GetAliveNum());

    m_Hour = 8;
    m_Min = 0;
    auto label = Label::createWithSystemFont("", "ThonBuri", 34);
    label->setPosition(300, 770);
    label->setColor(Color3B::BLACK);
    this->addChild(label,100,"time");

    this->schedule(schedule_selector(ClassRoomScene::Tick), 1.0f);
    this->schedule(schedule_selector(ClassRoomScene::Update));
    return true;
}

void ClassRoomScene::AddStudents()
{
    for (int i = 0; i < m_Students->GetAllNum(); ++i)
    {
        this->addChild(m_Students->GetStudent(i));
    }
}

void ClassRoomScene::UpdateDday()
{

    if (m_Dday <= 0)
    {
        GameOver();
    }

    if (this->getChildByName("day") != nullptr)
    {
        this->removeChildByName("day");
    }

    Sprite* dDay;

    switch (m_Dday)
    {
    case 1:
        dDay = Sprite::create("Resources/Dday1.png");
        break;
    case 2:
        dDay = Sprite::create("Resources/Dday2.png");
        break;
    case 3:
        dDay = Sprite::create("Resources/Dday3.png");
        break;
    default:
        break;
    }

    dDay->setPosition(800, 650);
    this->addChild(dDay,1,"day");
}

void ClassRoomScene::menuCallBack0(cocos2d::Ref* sender)
{
    auto pencilLayer = PencilLayer::create();
    this->addChild(pencilLayer, 1, "pencilLayer");
}

void ClassRoomScene::menuCallBack1(cocos2d::Ref* sender)
{
    auto assassinationLayer = AssassinationLayer::create();
    this->addChild(assassinationLayer, 1, "assassinationLyaer");
}

void ClassRoomScene::Update(float dt)
{
    if ((Player::getInstance()->IsKillComplete()))
    {
        KillComplete();
    }

    m_RedEffect->setOpacity(220 - m_Students->GetAliveNum() * 12);

    auto menu = static_cast<Menu*>(this->getChildByName("classRoomMenu"));
    auto button = static_cast<MenuItem*>(menu->getChildByName("assassination"));

    if (!(Player::getInstance()->IsPencilSharp()))
    {
        button->setOpacity(100);
        button->setEnabled(false);
    }
    else
    {
        button->setOpacity(255);
        button->setEnabled(true);
    }
}

void ClassRoomScene::KillComplete()
{
    m_Students->Die();
    Player::getInstance()->SetEnemyNum(m_Students->GetAliveNum());
    Player::getInstance()->SetIsKillComplete(false);
    Player::getInstance()->ResetSharpGauge();

    if (m_Students->GetAliveNum() <= 0)
    {
        GameEnding();
    }
}

void ClassRoomScene::Tick(float dt)
{
    if (m_Students->GetAliveNum() <= 0)
    {
        GameEnding();
    }

    m_Min++;

    if (m_Min >= 60)
    {
        m_Min = 0;
        m_Hour++;
    }

    if (m_Hour >= 16)
    {
        m_Dday--;
        m_Hour = 8;
        m_Min = 0;
        UpdateDday();
    }

    std::string time = "시간  ";
    time += std::to_string(m_Hour);
    time += " 시 : ";
    time += std::to_string(m_Min);
    time += " 분";

    auto _label = static_cast<Label*>(this->getChildByName("time"));
    _label->setString(time);
}

void ClassRoomScene::GameOver()
{
    auto gameOver = MenuItemImage::create(
        "Resources/GameOver.png",
        "Resources/GameOver.png",
        CC_CALLBACK_1(ClassRoomScene::VoidFunc,this));

    auto menu0 = Menu::create(gameOver, false);
    gameOver->setAnchorPoint(Point(0.5, 0.5));
    gameOver->setPosition(0, 0);
    this->addChild(menu0, 1000);

    auto replay = MenuItemImage::create(
        "Resources/Replay.png",
        "Resources/ReplaySelected.png",
        CC_CALLBACK_1(ClassRoomScene::Replay, this));
    auto menu1 = Menu::create(replay, false);
    menu1->setAnchorPoint(Point(0.5, 0.5));
    menu1->setPosition(600, 100);
    this->addChild(menu1, 1001);
}

void ClassRoomScene::VoidFunc(cocos2d::Ref* sender)
{
    //void
}

void ClassRoomScene::GameEnding()
{
    Director::getInstance()->replaceScene(EndingScene::createScene());
}

void ClassRoomScene::Replay(cocos2d::Ref* sender)
{
    Player::getInstance()->ResetPlayerPos();
    Player::getInstance()->ResetSharpGauge();
    Player::getInstance()->SetIsSharp(false);
    Director::getInstance()->replaceScene(StartScene::createScene());
}
