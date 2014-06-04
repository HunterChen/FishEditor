#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "UI/EditorLayer.h"
#include "AppInitialize.h"

USING_NS_CC;
using namespace CocosDenshion;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{

}

bool AppDelegate::applicationDidFinishLaunching()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);
	pDirector->setDisplayStats(false);
	pDirector->setAnimationInterval(1.0 / 60);
	pEGLView->setDesignResolutionSize(1136, 640, kResolutionFixedHeight);

	AppInitialize::LoadResource();

	CCScene* scene = EditorScene::getScene();
	pDirector->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
