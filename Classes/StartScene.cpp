#include "StartScene.h"
#include "ClassRoomScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    auto scene = Scene::create();

    auto layer = StartScene::create();

    scene->addChild(layer);

    return scene;
}

bool StartScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto layer = MenuItemImage::create("Resources/Black.png","Resources/Black.png",CC_CALLBACK_1(StartScene::VoidFunc,this));
    layer->setAnchorPoint(Point(0, 0));
    layer->setPosition(0, 0);
    layer->setOpacity(0);
    this->addChild(layer,-1,"layer");

    auto winSize = Director::getInstance()->getWinSize();

    auto title = Sprite::create("Resources/Title.png");
    title->setAnchorPoint(Point(0, 1));
    title->setPosition(Point(0, 800));
    this->addChild(title, 2, "title");

    auto startButton = MenuItemImage::create(
        "Resources/Start.png",
        "Resources/StartSelected.png",
        CC_CALLBACK_1(StartScene::menuCallBack, this));
    
    auto menu = Menu::create(startButton, false);
    menu->setPosition(winSize.width / 2, winSize.height / 6);
    this->addChild(menu,1,"start");

    return true;
}

void StartScene::menuCallBack(cocos2d::Ref* sender)
{
    auto layer = this->getChildByName("layer");
    auto action0 = FadeTo::create(2.0f, 255);

    layer->setZOrder(100);
    layer->runAction(action0);

    this->schedule(schedule_selector(StartScene::ReplaceScene), 3.0f);

    
}

void StartScene::ReplaceScene(float dt)
{
    Director::getInstance()->replaceScene(ClassRoomScene::createScene());
}

void StartScene::VoidFunc(cocos2d::Ref* sender)
{
    //void
}
