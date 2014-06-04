#pragma once

#include <string>


enum day_of_week
{
	day_sunday = 0,
	day_monday,
	day_tuesday,
	day_wednesday,
	day_thursday,
	day_friday,
	day_saturday,
};


struct local_date
{
	int sec;
	int min;
	int hour;
	int mday;
	int mon;
	int year;
	int wday;
};


class LocalDate
{
public:
	static local_date getLocalDate();

	static day_of_week getDayOfWeek();

	static std::string getStringTime(); //hour:min:sec

	static std::string getStringDate(); //year-month-day

	static std::string getStringDayOfWeek();
};