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
	const int MAX_NUMBER_OF_TIMES = 10;
}

class Time
{
private:
	int hours;
	int minutes;
	int seconds;
	int timeInSeconds;

	int hoursToSeconds(int hours) const
	{
		return hours * GLOBAL_CONSTANTS::HOUR_MULTIPLIER;
	}

	int minutesToSeconds(int minutes) const
	{
		return minutes * GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	int getAllSeconds() const
	{
		return hoursToSeconds(this->hours) + minutesToSeconds(this->minutes) + this->seconds;
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

	int getSecRem(int seconds) const
	{
		return seconds % GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	//converting all seconds int hours,minutes,seconds format ^

	int getRemainingSeconds() const
	{
		return GLOBAL_CONSTANTS::MAX_POSSIBLE_SECONDS - this->timeInSeconds;
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

public:
	Time() : hours(GLOBAL_CONSTANTS::DEFAULT_TIME),
		minutes(GLOBAL_CONSTANTS::DEFAULT_TIME),
		seconds(GLOBAL_CONSTANTS::DEFAULT_TIME),
		timeInSeconds(GLOBAL_CONSTANTS::DEFAULT_TIME){};

	Time(int hours, int minutes, int seconds)
	{
		setHours(hours);
		setMinutes(minutes);
		setSeconds(seconds);
		this->timeInSeconds = getAllSeconds();
	}

	void setHours(int hours)
	{
		if (hours < 0 || hours > 23) return;
		this->hours = hours;
		this->timeInSeconds = getAllSeconds();
	}

	void setMinutes(int minutes)
	{
		if (minutes < 0 || minutes > 59) return;
		this->minutes = minutes;
		this->timeInSeconds = getAllSeconds();
	}

	void setSeconds(int seconds)
	{
		if (seconds < 0 || seconds > 59) return;
		this->seconds = seconds;
		this->timeInSeconds = getAllSeconds();
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

		int remainingSeconds = getRemainingSeconds();
		int remainingHours = secToHours(remainingSeconds);
		int remainingMinutes = secToMinutes(remainingSeconds);
		int seconds = getSecRem(remainingSeconds);

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
		return (this->hours >= GLOBAL_CONSTANTS::PARTY_START
			|| this->hours < GLOBAL_CONSTANTS::PARTY_END);
	}

	const Time getDifferenceOfTimes(const Time& other) const
	{
		int diffInSeconds = this->timeInSeconds - other.timeInSeconds;
		diffInSeconds = diffInSeconds < 0 ? -diffInSeconds : diffInSeconds;
		//Няма да използвам abs! никога!!!

		int newSeconds = getSecRem(diffInSeconds);
		int newMinutes = secToMinutes(diffInSeconds);
		int newHours = secToHours(diffInSeconds);

		return { newHours,newMinutes,newSeconds };
	}

	bool compareTimes(const Time& other) const
	{
		return this-> timeInSeconds >= other.timeInSeconds;
	}

	void printTime() const
	{
		printHours();
		printMinutes();
		printSeconds();
		std::cout << std::endl;
	}
};

struct Times
{
	Time times[GLOBAL_CONSTANTS::MAX_NUMBER_OF_TIMES];
	int currentTimes;
};

namespace GLOBAL_FUNCTIONS
{
	void swapTimes(Time& t1, Time& t2)
	{
		Time temp = t1;
		t1 = t2;
		t2 = temp;
	}

	void bubbleSort(Time* arrTime,int size)
	{
		for (int i = 0; i < size - 1; ++i)
		{
			for (int j = 0; j < size - i - 1; ++j)
			{
				if (arrTime[j].compareTimes(arrTime[j + 1]))
					swapTimes(arrTime[j], arrTime[j + 1]);
			}
		}
	}
}

int main()
{
	Time t1(23, 41, 41);
	Time t2(23, 41, 41);
	Time t3(23, 34, 40);
	Time t4(22, 16, 40);
	Time t5(9, 54, 40);
	Time t6(8, 40, 40);
	Time t7(17, 40, 40);
	Time t8(6, 40, 40);
	Time t9(15, 40, 40);
	Time t10(14, 23, 44);

	Time times[10] = { t1,t2,t3,t4,t5,t6,t7,t8,t9,t10 };

	for (int i = 0; i < 10; ++i)
	{
		times[i].printTime();
	}

	GLOBAL_FUNCTIONS::bubbleSort(times, GLOBAL_CONSTANTS::MAX_NUMBER_OF_TIMES);
	std::cout << "after" << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		times[i].printTime();
	}

	return 0;
}
