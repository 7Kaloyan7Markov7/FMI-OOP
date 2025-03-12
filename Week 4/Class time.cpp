#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS
{
	const int DEFAULT_TIME = 0;
	const int HOUR_MULTIPLIER = 3600;
	const int MIN_MULTIPLIER = 60;
	const int MAX_POSSIBLE_SECONDS = 24 * 3600;
	const int MAX_MINUTES_AND_SECONDS = 60;
	const int MAX_HOURS_IN_A_DAY = 24;
	const int PARTY_START = 23;
	const int PARTY_END = 6;
	const int MAX_TIME_SIZE = 10;
}

class Time
{
private:
	int hours;
	int minutes;
	int seconds;

	int hoursToSeconds(int hours) const
	{
		return hours * GLOBAL_CONSTANTS::HOUR_MULTIPLIER;
	} 

	int minutesToSeconds(int minutes) const
	{
		return minutes * GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	int getAllSeconds(int hours, int minutes, int seconds) const
	{
		return hoursToSeconds(hours) + minutesToSeconds(minutes) + seconds;
	}

	//getting the total amount of seconds in our time^

	int secToHours(int seconds) const
	{
		return seconds / GLOBAL_CONSTANTS::HOUR_MULTIPLIER;
	}

	int secToMinutes(int seconds) const
	{
		return (seconds % GLOBAL_CONSTANTS::HOUR_MULTIPLIER) / GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	int getSec(int seconds) const
	{
		return seconds % GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	//converting all seconds int hours,minutes,seconds format ^

	int getRemainingSeconds(int hours, int minutes, int seconds) const
	{
		return GLOBAL_CONSTANTS::MAX_POSSIBLE_SECONDS - getAllSeconds(hours, minutes, seconds);
	}

	//getting remaining seconds ^

	void addOneHour()
	{
		this->hours++;
		if (this->hours == GLOBAL_CONSTANTS::MAX_HOURS_IN_A_DAY)
			this->hours %= GLOBAL_CONSTANTS::MAX_HOURS_IN_A_DAY;
	}

	void addOneMinute()
	{
		this->minutes++;
		if (this->minutes == GLOBAL_CONSTANTS::MAX_MINUTES_AND_SECONDS)
		{
			this->minutes %= GLOBAL_CONSTANTS::MAX_MINUTES_AND_SECONDS;
			addOneHour();
		}
	}

	void printHours() const
	{
		if (this->hours < 10) std::cout << "0";
		std::cout << this->hours << ":";
	} 

	void printMinutes() const
	{
		if (this->minutes < 10) std::cout << "0";
		std::cout << this->minutes << ":";
	} 

	void printSeconds()const
	{
		if (this->seconds < 10) std::cout << "0";
		std::cout << this->seconds;
	} 
	//print ^

	int getSecDifference(int seconds) const
	{
		return this->seconds - seconds;
	}

	int getMinuteDifference(int minutes) const
	{
		return this->minutes - minutes;
	}

	int getHourDifference(int hours) const
	{
		return this->hours - hours;
	}

public:
	Time() : hours(GLOBAL_CONSTANTS::DEFAULT_TIME),
		 minutes(GLOBAL_CONSTANTS::DEFAULT_TIME),
		seconds(GLOBAL_CONSTANTS::DEFAULT_TIME) {};

	Time(int hours, int minutes, int seconds)
	{
		setHours(hours);
		setMinutes(minutes);
		setSeconds(seconds);
	}

	void setHours(int hours)
	{
		if (hours < 0 || hours > 23) return;
		this->hours = hours;
	}

	void setMinutes(int minutes)
	{
		if (minutes < 0 || minutes > 59) return;
		this->minutes = minutes;
	}

	void setSeconds(int seconds)
	{
		if (seconds < 0 || seconds > 59) return;
		this->seconds = seconds;
	}
	//setters ^
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
	//getters ^
	const Time getRemainingTime() const
	{
		if (!this->hours && !this->minutes && !this->seconds) return { 0,0,0 };

		int remainingSeconds = getRemainingSeconds(this->hours, this->minutes, this->seconds);
		int remainingHours = secToHours(remainingSeconds);
		int remainingMinutes = secToMinutes(remainingSeconds);
		int seconds = getSec(remainingSeconds);

		return { remainingHours ,remainingMinutes, seconds };
	}

	void addOneSecond()
	{
		this->seconds++;
		if (this->seconds == GLOBAL_CONSTANTS::MAX_MINUTES_AND_SECONDS)
		{
			this->seconds %= GLOBAL_CONSTANTS::MAX_MINUTES_AND_SECONDS;
			addOneMinute();
		}
	}

	bool isItDinnerTime() const
	{
		if (this->hours < 20 || this->hours > 22) return false;
		if (this->hours == 20 && this->minutes < 30) return false;
		if (this->hours == 22 && this->minutes > 0) return false;

		return true;
	}

	bool isItPartyTime() const
	{
		if (this->hours < GLOBAL_CONSTANTS::PARTY_START && this->hours > GLOBAL_CONSTANTS::PARTY_END) return false;
		if (this->hours == GLOBAL_CONSTANTS::PARTY_END && (this->minutes > 0 || this->seconds > 0)) return false;

		return true;
	}

	const Time getDifferenceOfTimes(const Time& other) const
	{
		int newSeconds = getSecDifference(other.seconds);
		int newMinutes = getMinuteDifference(other.minutes);
		int newHours = getHourDifference(other.hours);

		if (newSeconds < 0)
		{
			newSeconds = 60 + newSeconds;
			newMinutes--;
		}

		if (newMinutes < 0)
		{
			newMinutes = 60 + newMinutes;
			newHours--;
		}

		if (newHours < 0)
		{
			newHours = 24 + newHours;
		}

		return { newHours,newMinutes,newSeconds };
	}

	void compareTimes(const Time& other) const
	{
		int thisTotalSeconds = getAllSeconds(this->hours, this->minutes, this->seconds);
		int otherTotalSeconds = getAllSeconds(other.hours, other.minutes, other.seconds);

		if (thisTotalSeconds > otherTotalSeconds) std::cout << "Current time is later";
		else if (thisTotalSeconds < otherTotalSeconds) std::cout << "Current time is earlier";
		else std::cout << "Times are equal";
	}

	void printTime() const
	{
		printHours();
		printMinutes();
		printSeconds();
	}
};

namespace GLOBAL_FUNCTIONS
{
	void bubbleSort(Time* arrTime)
	{
		for (int i = 0; i < GLOBAL_CONSTANTS::MAX_TIME_SIZE - 1; ++i)
		{
			for (int j = 0; j < GLOBAL_CONSTANTS::MAX_TIME_SIZE - i - 1; ++j)
			{
				
			}
		}
	}
}

int main()
{

	return 0;
}
