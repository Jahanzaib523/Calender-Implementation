/*
 * DateTime.h
 *
 *  Created on: May 31, 2020
 *      Author: BilalZumar
 */

#ifndef DATETIME_H_
#define DATETIME_H_

#include <string>

class DateTime {
private:
	std::string months[12]={"Jan","Feb","Mar","Apr","May","June","July","Aug","Sep","Oct","Nov","Dec"};
	int year;
	int month;
	int day;
	int hour;
	int minute;
public:
	DateTime();
	DateTime(int year, int month, int day, int hour, int minute);
	DateTime(const DateTime &obj);
	void operator=(const DateTime &obj);
	bool operator<(const DateTime &obj) const;
	bool operator>(const DateTime &obj) const;
	bool operator==(const DateTime &obj) const;
	std::string timeString() const;
	std::string monthDayString() const;
	virtual ~DateTime();
	int getDay() const;
	int getHour() const;
	int getMinute() const;
	int getMonth() const;
	int getYear() const;
};

#endif /* DATETIME_H_ */
