/*
 * Event.h
 *
 *  Created on: May 31, 2020
 *      Author: BilalZumar
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include "DateTime.h"

class Event {
private:
	std::string name;
	std::string location;
	DateTime start;
	DateTime end;
public:
	Event();
	Event(std::string name, std::string location, DateTime start, DateTime end);
	Event(const Event &obj);
	void operator+(const Event &obj);
	bool conflict(const Event &other) const;
	bool conflict(const DateTime &other) const;
	void setName(const std::string &name);
	void setLocation(const std::string &location);
	void setStart(const DateTime &start);
	void setEnd(const DateTime &end);
	std::string getName() const;
	std::string getLocation() const;
	DateTime getStart() const;
	DateTime getEnd() const;
	std::string getDuration() const;
	int* getDuration(int i) const;
	std::string toString() const;
	virtual ~Event();
};

#endif /* EVENT_H_ */
