/*
 * Calendar.cpp
 *
 *  Created on: Jun 1, 2020
 *      Author: BilalZumar
 */

#include <iostream>
#include "Calendar.h"

Calendar::CalendarNode::CalendarNode(Event e){
	this->e=e;
	this->next=NULL;
	this->prev=NULL;
}

Calendar::CalendarNode::CalendarNode(const CalendarNode &obj){
	this->e=obj.e;
	this->next=obj.next;
	this->prev=obj.prev;
}

void Calendar::CalendarNode::operator=(const CalendarNode &obj){
	this->e=obj.e;
	this->next=obj.next;
	this->prev=obj.prev;
}

Calendar::CalendarNode::~CalendarNode(){
}

Calendar::Calendar() {
	this->head=NULL;
	this->tail=NULL;
}

Calendar::Calendar(const Calendar &obj){
	if (obj.head == nullptr)
		head = tail = nullptr;
	else
	{
		head = new CalendarNode(obj.head->e);
		CalendarNode* tempOther = obj.head->next;
		CalendarNode* temp = head;
		while (tempOther != nullptr )
		{
			temp->next = new CalendarNode(tempOther->e);
			temp=temp->next;
			tempOther = tempOther->next;
		}
		tail = temp;
	}
}

void Calendar::operator=(const Calendar &obj){
	this->head=obj.head;
	this->tail=obj.tail;
}

bool Calendar::add_event(const Event &e){

	if(this->head==NULL)
	{
		CalendarNode* temp=new CalendarNode(e);
		this->head=temp;
		this->tail=temp;
//		std::cout<<"first"<<std::endl;
	}
	else
	{
//		std::cout<<"adding "<<e.getName()<<std::endl;

		CalendarNode* curr=head;
		if(this->conflict(e))
		{
			std::cout<<"conflict "<<e.getName()<<std::endl;
			return false;
		}

		curr=head;
		if(curr->e.getStart() > e.getStart()){
//			std::cout<<"true"<<std::endl;
			CalendarNode* temp=new CalendarNode(e);
			temp->next=this->head;
			this->head->prev=temp;
			this->head=temp;
		}
		else{

			while(curr->next!=NULL && curr->next->e.getStart() < e.getStart()){
				curr=curr->next;
			}
			CalendarNode* temp=new CalendarNode(e);
//			std::cout<<"false"<<std::endl;

			if(curr->next!=NULL)
			{
				temp->next=curr->next;
				temp->prev=curr;
				curr->next->prev=temp;
				curr->next=temp;
			}
			else{
				curr->next=temp;
				temp->prev=curr;
				tail=temp;
			}
		}
//		std::cout<<"added "<<e.getName()<<std::endl;
	}
	return true;
}

void Calendar::remove_event(const Event &e){

	CalendarNode* curr=this->head;
	curr=this->head;
	while(curr!=NULL){

		int count=0;
		if(curr->e.getName()==e.getName() && curr->e.getLocation()==e.getLocation() && curr->e.getStart()==e.getStart() && curr->e.getEnd()==e.getEnd()){
			CalendarNode* temp=curr;
			if(curr->next==NULL)
			{
				this->tail=curr->prev;
				curr->prev->next=NULL;
			}
			else if(count==0){
				this->head=curr->next;
				curr->next->prev=NULL;
			}
			else{
				curr->prev->next=curr->next;
				curr->next->prev=curr->prev;
			}
			delete temp;
		}
		count++;
		curr=curr->next;
	}
	return;
}

void Calendar::make_space(const DateTime &start, const DateTime &end){
	Event* temp=new Event("test","",start,end);
	CalendarNode* curr=head;
	int count=0;
	while(curr!=NULL){
		if(curr->e.conflict(*temp))
		{
			CalendarNode* temp=curr;
			if(curr->next==NULL)
			{
				std::cout<<"Removing "+curr->e.getName()<<std::endl;
				if(curr->prev==NULL){
					this->tail=curr->prev;
					this->head=curr->prev;
				}
				else
				{
					this->tail=curr->prev;
					curr->prev->next=NULL;
				}
			}
			else if(curr->prev==NULL){
				std::cout<<curr->e.getName()+" erroe2"<<std::endl;
				this->head=curr->next;
				curr->next->prev=NULL;
			}
			else{
				std::cout<<curr->e.getName()+" erroe3"<<std::endl;
				curr->prev->next=curr->next;
				curr->next->prev=curr->prev;
			}
			delete temp;
		}
		count++;
		curr=curr->next;
	}
}

bool Calendar::conflict(const Event &e){
	CalendarNode* curr=head;
	while(curr!=NULL){
		if(e.conflict(curr->e))
		{
			return true;
		}
		curr=curr->next;
	}
	return false;
}

bool Calendar::busy_during(const DateTime &d) const{
	CalendarNode* curr=head;
	while(curr!=NULL){
		if(curr->e.conflict(d))
		{
			return true;
		}
		curr=curr->next;
	}
	return false;
}

bool Calendar::free_during(const DateTime &d) const{
	CalendarNode* curr=head;
	while(curr!=NULL){
		if(curr->e.conflict(d))
		{
			return false;
		}
		curr=curr->next;
	}
	return true;
}

std::string Calendar::toString() const{
	std::string ret="";
	CalendarNode* curr=head;
	while(curr!=NULL){
		ret+=curr->e.toString()+"\n";
		curr=curr->next;
	}
//	std::cout<<"count "<<count<<std::endl;
	return ret;
}

Event Calendar::next_event(const DateTime &d) const{
	Event e=Event();
	CalendarNode* curr=head;
	while(curr!=NULL){
		if(curr->e.getStart()>d || curr->e.getStart()==d)
		{
			return curr->e;
		}
		curr=curr->next;
	}
	return e;
}

Event Calendar::earliest_event() const{
	return head->e;
}

Event Calendar::last_event() const{
	return tail->e;
}

Event Calendar::longest_event() const{
	Event e=head->e;
	CalendarNode* curr=head;
	while(curr!=NULL){

		int* arr1=curr->e.getDuration(0);
		int* arr2=e.getDuration(0);
		for(int i=0;i<5;i++){
//			std::cout<<arr1[i]<<" "<<arr2[i]<<std::endl;
			if(arr1[i]>arr2[i])
			{
				e=curr->e;
				break;
			}
			if(arr1[i]<arr2[i])
			{
				break;
			}
		}
		curr=curr->next;
	}

	return e;
}

Event Calendar::shortest_event() const{
	Event e=head->e;
	CalendarNode* curr=head;
	while(curr!=NULL){

		int* arr1=curr->e.getDuration(0);
		int* arr2=e.getDuration(0);
		for(int i=0;i<5;i++){
			if(arr1[i]<arr2[i])
			{
				e=curr->e;
				break;
			}
			if(arr1[i]>arr2[i])
			{
				break;
			}
		}
		curr=curr->next;
	}

	return e;
}

Calendar::~Calendar() {
	CalendarNode* curr=head;
	while(curr!=NULL){
		CalendarNode* temp=curr;
		curr=curr->next;
		delete temp;
	}
}

