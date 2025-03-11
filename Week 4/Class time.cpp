#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int DEFAULT_TIME = 0;
	const int HOUR_MULTIPLIER = 3600;
	const int MIN_MULTIPLIER = 60;
	const int TOTAL_SECONDS = 24 * 3600;
}

class Time
{
private:
	int hours;
	int minutes;
	int seconds;

	int hoursToSeconds(int hours)
	{
		return hours * GLOBAL_CONSTANTS::HOUR_MULTIPLIER;
	}
	
	int minutesToSeconds(int minutes)
	{
		return minutes * GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	int getSeconds(int allSeconds)
	{
		return allSeconds % GLOBAL_CONSTANTS::HOUR_MULTIPLIER
	}

	void setMinutes(int minutes)
	{
		if (minutes < 0 || minutes > 59) return;
		this->minutes = minutes;
	}

	void setSeconds(int seconds)
	{
		if (seconds < 0 || seconds > 23) return;
		this->seconds = seconds;
	}

	int getHours() const
	{
		return this->hours;
	}

	int getMinutes() const
	{
		return this->minutes;
	}

	int getSeconds() const
	{
		return this->seconds;
	}

	const Time getRemainingTime() const
	{
		return {};
	}

};

int main()
{
	Time test(15, 34, 40);

	return 0;
}
