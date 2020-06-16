/*
 * Event.cpp
 *
 *  Created on: May 31, 2020
 *      Author: BilalZumar
 */

#include "Event.h"
#include <string>
#include <iostream>

Event::Event(){
	this->name="";
	this->location="";
	this->start=DateTime();
	this->end=DateTime();
}

Event::Event(std::string name, std::string location, DateTime start, DateTime end){
	this->name=name;
	this->location=location;
	this->start=start;
	this->end=end;
	if(name==""){
		throw std::domain_error("events must have a name");
	}
	if(start>end){
		throw std::domain_error("end is before start");
	}
}

Event::Event(const Event &obj){
	this->name=obj.name;
	this->location=obj.location;
	this->start=obj.start;
	this->end=obj.end;
}

void Event::operator+(const Event &obj){
	this->name=obj.name;
	this->location=obj.location;
	this->start=obj.start;
	this->end=obj.end;
}

bool Event::conflict(const Event &other) const{
	if(other.start>this->start && other.start<this->end){
		return true;
	}
	if(other.end>this->start && other.end<this->end)
	{
		return true;
	}
	if(this->start>other.start && this->start<other.end){
		return true;
	}
	if(this->end>other.start && this->end<other.end)
	{
		return true;
	}
	if(other.start==this->start || other.start==this->end || other.end==this->start || other.end==this->end)
	{
		return true;
	}
	return false;
}

bool Event::conflict(const DateTime &other) const{
	if(other>this->start && other<this->end || other==this->start || other==this->end){
		return true;
	}
	return false;
}

void Event::setName(const std::string &name){
	this->name=name;
}

void Event::setLocation(const std::string &location){
	this->location=location;
}

void Event::setStart(const DateTime &start){
	this->start=start;
}

void Event::setEnd(const DateTime &end){
	this->end=end;
}

std::string Event::getName() const{
	return this->name;
}

std::string Event::getLocation() const{
	return this->location;
}

DateTime Event::getStart() const{
	return this->start;
}

DateTime Event::getEnd() const{
	return this->end;
}

std::string Event::getDuration() const{
	std::string ret="";
	int balance=0,year,month,day,hour,minute;

	int v1=this->end.getMinute();
	int v2=this->start.getMinute();
	if(v1>=v2){
		minute=v1-v2;
		balance=0;
	}
	else{
		minute=60+v1-v2;
		balance=-1;
	}

	v1=this->end.getHour();
	v2=this->start.getHour();
	v2-=balance;

	if(v1>=v2){
		hour=v1-v2;
		balance=0;
	}
	else{
		hour=24+v1-v2;
		balance=-1;
	}

	v1=this->end.getDay();
	v2=this->start.getDay();
	v2-=balance;
	if(v1>=v2){
		day=v1-v2;
		balance=0;
	}
	else{
		day=30+v1-v2;
		balance=-1;
	}

	v1=this->end.getMonth();
	v2=this->start.getMonth();
	v2-=balance;
	if(v1>=v2){
		month=v1-v2;
		balance=0;
	}
	else{
		month=12+v1-v2;
		balance=-1;
	}

	v1=this->end.getYear();
	v2=this->start.getYear();
	v2-=balance;
	if(v1>=v2){
		year=v1-v2;
		balance=0;
	}
	else{
		year=v2-v1;
	}

	if(year!=0){
		ret+=std::to_string(year)+" year";
	}
	if(month!=0){
		ret+=std::to_string(month)+" month";
	}
	if(day!=0){
		ret+=std::to_string(day)+" day";
	}
	if(hour!=0){
		ret+=std::to_string(hour)+" hour";
	}
	if(minute!=0){
		ret+=std::to_string(minute)+" minute";
	}

	return ret;
}

int* Event::getDuration(int i) const{
	int* ret=new int[5];
	int balance=0,year,month,day,hour,minute;

	int v1=this->end.getMinute();
	int v2=this->start.getMinute();
	if(v1>=v2){
		minute=v1-v2;
		balance=0;
	}
	else{
		minute=60+v1-v2;
		balance=-1;
	}

	v1=this->end.getHour();
	v2=this->start.getHour();
	v2-=balance;

	if(v1>=v2){
		hour=v1-v2;
		balance=0;
	}
	else{
		hour=24+v1-v2;
		balance=-1;
	}

	v1=this->end.getDay();
	v2=this->start.getDay();
	v2-=balance;
	if(v1>=v2){
		day=v1-v2;
		balance=0;
	}
	else{
		day=30+v1-v2;
		balance=-1;
	}

	v1=this->end.getMonth();
	v2=this->start.getMonth();
	v2-=balance;
	if(v1>=v2){
		month=v1-v2;
		balance=0;
	}
	else{
		month=12+v1-v2;
		balance=-1;
	}

	v1=this->end.getYear();
	v2=this->start.getYear();
	v2-=balance;
	if(v1>=v2){
		year=v1-v2;
		balance=0;
	}
	else{
		year=v2-v1;
	}

	ret[0]=year;
	ret[1]=month;
	ret[2]=day;
	ret[3]=hour;
	ret[4]=minute;

	return ret;
}

std::string Event::toString() const{
	std::string ret=this->start.monthDayString();
	if(this->start==this->end){
		ret+="            ";
	}
	else
	{
		ret+=" "+this->start.timeString();
		ret+=" "+this->end.timeString();
	}
	ret+=" "+this->name;
	if(this->location!=""){
		ret+=" - "+this->location;
	}
	return ret;
}

Event::~Event(){

}

