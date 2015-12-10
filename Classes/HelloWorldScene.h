#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float);

	//Touch setup
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

	void StartPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void Start();
	void GameOver();

private:
	cocos2d::Sprite*		cat;
	cocos2d::Sprite*		background;
	cocos2d::Sprite*		background2;
	cocos2d::ui::Button*	startButton;
	cocos2d::Label*			score;


	int						move;
	int						tol;
};

#endif // __HELLOWORLD_SCENE_H__
