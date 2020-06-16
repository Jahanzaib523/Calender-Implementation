/*
 * Calendar.h
 *
 *  Created on: Jun 1, 2020
 *      Author: BilalZumar
 */

#ifndef CALENDAR_H_
#define CALENDAR_H_

#include "Event.h"
#include "DateTime.h"

class Calendar {
private:

	struct CalendarNode {
		Event e;
		struct CalendarNode* next;
		struct CalendarNode* prev;
		CalendarNode(Event e);
		CalendarNode(const CalendarNode &obj);
		void operator=(const CalendarNode &obj);
		virtual ~CalendarNode();
	};

	CalendarNode *head;
	CalendarNode *tail;


public:
	Calendar();
	Calendar(const Calendar &obj);
	void operator=(const Calendar &obj);
	bool add_event(const Event &e);
	void remove_event(const Event &e);
	void make_space(const DateTime &start, const DateTime &end);
	bool conflict(const Event &e);
	bool busy_during(const DateTime &d) const;
	bool free_during(const DateTime &d) const;
	std::string toString() const;
	Event next_event(const DateTime &d) const;
	Event earliest_event() const;
	Event last_event() const;
	Event longest_event() const;
	Event shortest_event() const;
	virtual ~Calendar();
};

#endif /* CALENDAR_H_ */
