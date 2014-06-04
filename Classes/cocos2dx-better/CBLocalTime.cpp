#include "CBLocalTime.h"
#include "cocos2d.h"


double CBLocalTime::getCurMillisecond()
{
	cocos2d::cc_timeval now_time;
	cocos2d::CCTime::gettimeofdayCocos2d(&now_time, NULL);
	double millisecond = ((double)now_time.tv_sec)*1000 + now_time.tv_usec/1000;
	return millisecond;
}
