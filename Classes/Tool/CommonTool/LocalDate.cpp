#include "LocalDate.h"
#include <ctime>
#include <sstream>

local_date LocalDate::getLocalDate()
{
	time_t tt = time(NULL);
	struct tm *t = localtime(&tt);

	local_date dateTmp;
	dateTmp.year = t->tm_year + 1900;
	dateTmp.mon = t->tm_mon + 1;
	dateTmp.mday = t->tm_mday;
	dateTmp.hour = t->tm_hour;
	dateTmp.min = t->tm_min;
	dateTmp.sec = t->tm_sec;
	dateTmp.wday = t->tm_wday;
	return dateTmp;
}

day_of_week LocalDate::getDayOfWeek()
{
	return day_of_week(LocalDate::getLocalDate().wday);
}

std::string LocalDate::getStringTime()
{
	local_date dateTmp = LocalDate::getLocalDate();
	std::stringstream strTmp;
	strTmp<<dateTmp.hour<<":"<<dateTmp.min<<":"<<dateTmp.sec;
	return strTmp.str();
}

std::string LocalDate::getStringDate()
{
	local_date dateTmp = LocalDate::getLocalDate();
	std::stringstream strTmp;
	strTmp<<dateTmp.year<<"-"<<dateTmp.mon<<"-"<<dateTmp.mday;
	return strTmp.str();
}

std::string LocalDate::getStringDayOfWeek()
{
	std::string str[7];
	str[0] = "Sunday";
	str[1] = "Monday";
	str[2] = "Tuesday";
	str[3] = "Wednesday";
	str[4] = "Thursday";
	str[5] = "Friday";
	str[6] = "Saturday";

	day_of_week day_week = day_of_week(LocalDate::getLocalDate().wday);
	return str[day_week];
}

