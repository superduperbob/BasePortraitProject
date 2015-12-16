#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "stdio.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	this->scheduleUpdate();

	auto winSize = Director::getInstance()->getVisibleSize();

	//Sprite creation
	cat = (Sprite*)rootNode->getChildByName("cat");
	background = (Sprite*)rootNode->getChildByName("background");
	background2 = (Sprite*)rootNode->getChildByName("background2");
	
	//Score label
	startScore = 0;
	scoreLabel = (ui::Text*)rootNode->getChildByName("score");
	scoreLabel->setString(StringUtils::format("%d", startScore));
	scoreLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height * 0.95));

	//Movement speed for cat
	move = 0;
	//scrolling tolerance for background
	tol = 0;
	
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//Button
	startButton = (ui::Button*)rootNode->getChildByName("startButton");
	startButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartPressed, this));
	
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Quirky_dog.mp3", true);

	GameManager::sharedGameManager()->isGameLive = false;

    return true;
}

void HelloWorld::StartPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{	
		this->Start();
	}
	this->Start();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{ 
	if (cat->getPosition().x > 0  && cat->getPosition().x < Director::getInstance()->getVisibleSize().width)
	{
		if (touch->getLocation().x >= Director::getInstance()->getVisibleSize().width / 2)
		{
			move = 15;
		}

		if (touch->getLocation().x <= Director::getInstance()->getVisibleSize().width / 2)
		{
			move = -15;
		}
	}
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{	
	move = 0;
}

static const int scrollSpeed = 5.0f;

void HelloWorld::update(float delta)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		//scrolling background
		Vec2 Bg1Pos = background->getPosition();
		Vec2 Bg2Pos = background2->getPosition();

		background->setPosition(Bg1Pos.x, Bg1Pos.y + scrollSpeed);
		background2->setPosition(Bg2Pos.x, Bg2Pos.y + scrollSpeed);

		if (background->getPosition().y > 1400 + tol)
		{
			background->setPosition(Bg1Pos.x, -480 + scrollSpeed);
		}

		if (background2->getPosition().y > 1400 + tol)
		{
			background2->setPosition(Bg2Pos.x, -480 + scrollSpeed);
		}

		//cat stuff
		Vec2 catPos = cat->getPosition();
		cat->setPosition(catPos.x + move, catPos.y);

		if (cat->getPosition().x < 0)
		{
			cat->setPosition(catPos.x + 15, catPos.y);
		}
		else if (cat->getPosition().x >  Director::getInstance()->getVisibleSize().width)
		{
			cat->setPosition(catPos.x - 15, catPos.y);
		}
		
		int tempPos = background->getPosition().y;
		int tempPos2 = background2->getPosition().y;

		//score
		if (tempPos > background->getPosition().y -100  || tempPos2 > background2->getPosition().y -100 )
		{
			GameManager::sharedGameManager()->UpdateScore(1);
			scoreLabel->setString(StringUtils::format("%d", GameManager::sharedGameManager()->GetScore() /10));
		}				
	}
}

void HelloWorld::Start()
{
	auto winSize = Director::getInstance()->getVisibleSize();

	GameManager::sharedGameManager()->ResetScore();
	GameManager::sharedGameManager()->isGameLive = true;

	cat->setPosition(winSize.width*0.5f, winSize.height*0.8f);
	move = 0;
	
	auto moveTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height*2*0.5f)); 
	startButton->runAction(moveTo);

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Meow.mp3");
	
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Meanwhile_in_Bavaria.mp3", true);
}

void HelloWorld::GameOver()
{

}