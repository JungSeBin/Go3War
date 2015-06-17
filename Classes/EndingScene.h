#include "cocos2d.h"

USING_NS_CC;

class EndingScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void EndingCredit(float dt);

    CREATE_FUNC(EndingScene);
};