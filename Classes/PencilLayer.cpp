#include "PencilLayer.h"
#include "SimpleAudioEngine.h" 
#include "Player.h"
#include "ClassRoomScene.h"

bool PencilLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE)) //ÇÏ¾á»ö ¼¼ÆÃ
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();

    auto background = MenuItemImage::create(
        "Resources/Black.png", 
        "Resources/Black.png", 
        CC_CALLBACK_1(PencilLayer::VoidFunc, this));

    auto menu0 = Menu::create(background, false);
    menu0->setAnchorPoint(Point(0, 0));
    menu0->setPosition(winSize.width / 2, winSize.height / 2);
    menu0->setOpacity(50);
    this->addChild(menu0, 10);

    auto exit = MenuItemImage::create(
        "Resources/Exit.png",
        "Resources/ExitSelected.png",
        CC_CALLBACK_1(PencilLayer::menuCallback, this));
    auto menu = Menu::create(exit, false);
    menu->setPosition(1200, 700);
    this->addChild(menu, 13);

    Sprite* pencil;
    if (Player::getInstance()->IsPencilSharp())
    {
        pencil = Sprite::create("Resources/Pencil2.png");
    }
    else if (Player::getInstance()->GetSharpGauge()>=50)
    {
        pencil = Sprite::create("Resources/Pencil1.png");
    }
    else
    {
        pencil = Sprite::create("Resources/Pencil0.png");
    }
    pencil->setAnchorPoint(Point(0.5, 0));
    pencil->setPosition(640, 0);
    this->addChild(pencil, 11, "pencil");

    auto cuter = Sprite::create("Resources/Cuter.png");
    cuter->setAnchorPoint(Point(0.5, 0.5));
    cuter->setPosition(800, 400);
    this->addChild(cuter,12,"cuter");

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(PencilLayer::OnMouseMove, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(PencilLayer::OnMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(PencilLayer::OnMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


    return true;
}

void PencilLayer::VoidFunc(cocos2d::Ref* sender)
{
    //void
}

void PencilLayer::menuCallback(cocos2d::Ref* sender)
{
    this->getParent()->removeChildByName("pencilLayer");
}

void PencilLayer::OnMouseMove(Event* event)
{
    auto location = static_cast<EventMouse*>(event)->getLocation();
    location.y = (Director::getInstance()->getWinSize().height) * 2 - location.y;

    m_MousePos.x = location.x;
    m_MousePos.y = location.y;

    auto cuter = this->getChildByName("cuter");
    cuter->setPosition(m_MousePos.x, m_MousePos.y);
}

void PencilLayer::OnMouseDown(Event* event)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
        "Resources/Cut.wma");

    Sprite* cuter = static_cast<Sprite*>(this->getChildByName("cuter"));
    cuter->setTexture(CCTextureCache::sharedTextureCache()->addImage("Resources/CuterPressed.png"));
    Player::getInstance()->UpSharpGauge();

    if (Player::getInstance()->IsPencilSharp())
    {
        return;
    }

    if( Player::getInstance()->GetSharpGauge() >= 70)
    {
        Sprite* pencil = static_cast<Sprite*>(this->getChildByName("pencil"));
        pencil->setTexture(CCTextureCache::sharedTextureCache()->addImage("Resources/Pencil2.png"));

        Player::getInstance()->SetIsSharp(true);
        Player::getInstance()->ResetSharpGauge();
    }
    else if (Player::getInstance()->GetSharpGauge() >= 40)
    {
        Sprite* pencil = static_cast<Sprite*>(this->getChildByName("pencil"));
        pencil->setTexture(CCTextureCache::sharedTextureCache()->addImage("Resources/Pencil1.png"));
    }
}

void PencilLayer::OnMouseUp(Event* event)
{
    Sprite* cuter = static_cast<Sprite*>(this->getChildByName("cuter"));
    cuter->setTexture(CCTextureCache::sharedTextureCache()->addImage("Resources/Cuter.png"));
}
