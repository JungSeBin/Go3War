#include "EndingScene.h"

USING_NS_CC;

cocos2d::Scene* EndingScene::createScene()
{
    auto scene = Scene::create();

    auto layer = EndingScene::create();

    scene->addChild(layer);

    return scene;
}


bool EndingScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();

    auto background = Sprite::create("Resources/Red.png");
    background->setAnchorPoint(Point(0, 0));
    background->setPosition(0, 0);
    this->addChild(background);

    auto endingCut1 = Sprite::create("Resources/EndingCut1.png");
    endingCut1->setAnchorPoint(Point(0.5, 0.5));
    endingCut1->setPosition(winSize.width / 2, winSize.height / 2);
    endingCut1->runAction(Sequence::create(DelayTime::create(1.2f), FadeTo::create(0.01f, 0), false));
    this->addChild(endingCut1);

    auto endingCut2 = Sprite::create("Resources/EndingCut2.png");
    endingCut2->setAnchorPoint(Point(0.5, 0));
    endingCut2->setPosition(winSize.width / 2, 0);
    endingCut2->setOpacity(0);
    endingCut2->runAction(Sequence::create(DelayTime::create(1.2f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut2);

    auto endingCut3 = Sprite::create("Resources/EndingCut3.png");
    endingCut3->setAnchorPoint(Point(0.5, 0));
    endingCut3->setPosition(winSize.width / 2, 0);
    endingCut3->setOpacity(0);
    endingCut3->runAction(Sequence::create(DelayTime::create(2.0f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut3);

    auto endingCut4 = Sprite::create("Resources/EndingCut4.png");
    endingCut4->setAnchorPoint(Point(0.5, 0));
    endingCut4->setPosition(winSize.width / 2, 0);
    endingCut4->setOpacity(0);
    endingCut4->runAction(Sequence::create(DelayTime::create(2.8f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut4);

    auto endingCut5 = Sprite::create("Resources/EndingCut5.png");
    endingCut5->setAnchorPoint(Point(0.5, 0));
    endingCut5->setPosition(winSize.width / 2, 0);
    endingCut5->setOpacity(0);
    endingCut5->runAction(Sequence::create(DelayTime::create(3.6f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut5);

    auto endingCut6 = Sprite::create("Resources/EndingCut6.png");
    endingCut6->setAnchorPoint(Point(0.5, 0));
    endingCut6->setPosition(winSize.width / 2, 0);
    endingCut6->setOpacity(0);
    endingCut6->runAction(Sequence::create(DelayTime::create(4.4f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut6);

    auto endingCut7 = Sprite::create("Resources/EndingCut7.png");
    endingCut7->setAnchorPoint(Point(0.5, 0));
    endingCut7->setPosition(winSize.width / 2, 0);
    endingCut7->setOpacity(0);
    endingCut7->runAction(Sequence::create(DelayTime::create(5.2f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut7);

    auto endingCut8 = Sprite::create("Resources/EndingCut8.png");
    endingCut8->setAnchorPoint(Point(0.5, 0));
    endingCut8->setPosition(winSize.width / 2, 0);
    endingCut8->setOpacity(0);
    endingCut8->runAction(Sequence::create(DelayTime::create(6.0f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut8);

    auto endingCut9 = Sprite::create("Resources/EndingCut9.png");
    endingCut9->setAnchorPoint(Point(0.5, 0));
    endingCut9->setPosition(winSize.width / 2, 0);
    endingCut9->setOpacity(0);
    endingCut9->runAction(Sequence::create(DelayTime::create(6.8f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut9);

    auto endingCut10 = Sprite::create("Resources/EndingCut10.png");
    endingCut10->setAnchorPoint(Point(0.5, 0));
    endingCut10->setPosition(winSize.width / 2, 0);
    endingCut10->setOpacity(0);
    endingCut10->runAction(Sequence::create(DelayTime::create(7.6f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut10);

    auto endingCut11 = Sprite::create("Resources/EndingCut11.png");
    endingCut11->setAnchorPoint(Point(0.5, 0));
    endingCut11->setPosition(winSize.width / 2, 0);
    endingCut11->setOpacity(0);
    endingCut11->runAction(Sequence::create(DelayTime::create(8.4f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut11);

    auto endingCut12 = Sprite::create("Resources/EndingCut12.png");
    endingCut12->setAnchorPoint(Point(0.5, 0));
    endingCut12->setPosition(winSize.width / 2, 0);
    endingCut12->setOpacity(0);
    endingCut12->runAction(Sequence::create(DelayTime::create(9.2f), FadeTo::create(0.01f, 255), false));
    this->addChild(endingCut12);

    this->schedule(schedule_selector(EndingScene::EndingCredit), 12.0f);
    return true;
}

void EndingScene::EndingCredit(float dt)
{
    unschedule(schedule_selector(EndingScene::EndingCredit));
    this->removeAllChildren();

    auto winSize = Director::getInstance()->getWinSize();

    auto endingCredit = Sprite::create("Resources/EndingCredit.png");
    endingCredit->setAnchorPoint(Point(0.5, 0));
    endingCredit->setPosition(winSize.width / 2, -1600);
    endingCredit->runAction(MoveTo::create(20.0f, Point(winSize.width / 2, 0)));
    this->addChild(endingCredit);
}
