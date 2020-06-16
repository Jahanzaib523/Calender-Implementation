//============================================================================
// Name        : Calender.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DateTime.h"
#include "Event.h"
#include "Calendar.h"

using namespace std;

int main() {
	DateTime* test1;
	try{
		test1=new DateTime(2020,6,15,22,59);
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	cout<<test1->timeString();
	cout<<test1->monthDayString();

	DateTime* test2;
	try{
		test2=new DateTime(2020,7,15,23,59);
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	cout<<test2->timeString();
	cout<<test2->monthDayString()<<endl;

	DateTime* conf;
	try{
		conf=new DateTime(2022,11,15,22,59);
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	cout<<conf->timeString()<<endl;
	cout<<conf->monthDayString()<<endl;

	string name="testing1";
	string loc="current loc1";
	Event* e1=new Event(name,loc,*test1,*test2);
	cout<<"conflict "<<e1->conflict(*conf)<<endl;
	cout<<"duration "<<e1->getDuration()<<endl;
	cout<<e1->toString()<<endl;


	DateTime* test3;
	try{
		test3=new DateTime(2021,5,15,22,59);
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	cout<<test3->timeString();
	cout<<test3->monthDayString();

	DateTime* test4;
	try{
		test4=new DateTime(2021,5,15,23,59);
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	cout<<test4->timeString();
	cout<<test4->monthDayString()<<endl;

	name="testing2";
	loc="current loc2";
	Event* e2=new Event(name,loc,*test3,*test4);
	cout<<"conflict "<<e2->conflict(*conf)<<endl;
	cout<<"duration "<<e2->getDuration()<<endl;
	cout<<e2->toString()<<endl;

	cout<<"Calender testing\n";

	Calendar* cal=new Calendar();
	cal->add_event(*e1);
	cal->add_event(*e2);

	cout<<cal->toString();
	cal->remove_event(*e1);

	cout<<cal->toString()<<endl;
	cal->add_event(*e2);
	cout<<cal->toString();
	cal->add_event(*e1);
	cout<<cal->toString();
	cal->make_space(*test3, *test4);
	cout<<cal->toString();


	cout<<"busy check"<<cal->busy_during(*test1)<<endl;
	cout<<"busy check"<<cal->busy_during(*test3)<<endl;

	cout<<"free check"<<cal->free_during(*test1)<<endl;
	cout<<"free check"<<cal->free_during(*test3)<<endl<<endl;

	cal->add_event(*e2);
	cout<<cal->toString()<<endl;

	Event t=cal->next_event(*test1);
	cout<<"test next_event: "<<t.toString()<<endl;
	t=cal->next_event(*conf);
	cout<<"test next_event: "<<t.toString()<<endl;

	t=cal->longest_event();
	cout<<"longest event "<<t.toString()<<endl;

	t=cal->shortest_event();
	cout<<"shortest event "<<t.toString();
	return 0;
}
