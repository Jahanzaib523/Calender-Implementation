/*
 * DateTime.cpp
 *
 *  Created on: May 31, 2020
 *      Author: BilalZumar
 */

#include "DateTime.h"
#include <string>

DateTime::DateTime(){
	this->year=0;
	this->month=0;
	this->day=0;
	this->hour=0;
	this->minute=0;
}

DateTime::DateTime(int year, int month, int day, int hour, int minute){
	if(month>12 || month<1 || day < 1 || hour>23 ||hour<0 || minute>59|| minute < 0 )
	{
		throw "DateTime Exception";
	}
	if( month == 2)
	{
		if((year%400==0) || (year%4==0 && year%100!=0))
			if(day>29){
				throw "DateTime Exception";
			}
		else
			if(day>28){
				throw "DateTime Exception";
			}
	}
	else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||month == 10 || month==12)
		if(day>31){
			throw "DateTime Exception";
	}
	else
		if(day>30){
			throw "DateTime Exception";
	}

	this->year=year;
	this->month=month;
	this->day=day;
	this->hour=hour;
	this->minute=minute;
}

DateTime::DateTime(const DateTime &obj){
	this->year=obj.year;
	this->month=obj.month;
	this->day=obj.day;
	this->hour=obj.hour;
	this->minute=obj.minute;
}

void DateTime::operator=(const DateTime &obj){
	this->year=obj.year;
	this->month=obj.month;
	this->day=obj.day;
	this->hour=obj.hour;
	this->minute=obj.minute;
}

bool DateTime::operator<(const DateTime &obj) const{
	if(this->year<obj.year){
		return true;
	}
	if(this->year==obj.year && this->month<obj.month){
		return true;
	}
	if(this->year==obj.year && this->month==obj.month && this->day<obj.day){
		return true;
	}
	if(this->year==obj.year && this->month==obj.month && this->day==obj.day && this->hour<obj.hour){
		return true;
	}
	if(this->year==obj.year && this->month==obj.month && this->day==obj.day && this->hour>obj.hour && this->minute<obj.minute){
		return true;
	}
	return false;
}
bool DateTime::operator>(const DateTime &obj) const{
	if(this->year>obj.year){
		return true;
	}
	else if(this->year==obj.year && this->month>obj.month){
		return true;
	}
	else if(this->year==obj.year && this->month==obj.month && this->day>obj.day){
		return true;
	}
	else if(this->year==obj.year && this->month==obj.month && this->day==obj.day && this->hour>obj.hour){
		return true;
	}
	else if(this->year==obj.year && this->month==obj.month && this->day==obj.day && this->hour==obj.hour && this->minute>obj.minute){
		return true;
	}
	else{
		return false;
	}
}

bool DateTime::operator==(const DateTime &obj) const{
	if(this->year==obj.year && this->month==obj.month && this->day==obj.day && this->hour==obj.hour && this->minute==obj.minute){
		return true;
	}
	else{
		return false;
	}
}

std::string DateTime::timeString() const{
	return std::to_string(this->hour)+":"+std::to_string(this->minute);
}

std::string DateTime::monthDayString() const{
	if(this->month==0)
		return "";
	return this->months[this->month-1]+" "+std::to_string(this->day);
}

int DateTime::getDay() const {
	return day;
}

int DateTime::getHour() const {
	return hour;
}

int DateTime::getMinute() const {
	return minute;
}

int DateTime::getMonth() const {
	return month;
}

int DateTime::getYear() const {
	return year;
}

DateTime::~DateTime() {

}
