#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include "timer.h"
#include <fstream>

struct Logger {
	inline static int copiesMade;
	inline static int constructed;
	Logger() {
		//std::cout << "Constructed" << std::endl;
	}
	~Logger() noexcept {
		//std::cout << "Destructed" << std::endl;
	}
	Logger(const Logger& logger) {
		//std::cout << "Copy-constructed" << std::endl;
		Logger::copiesMade++;
	}
	static void resetCopies() {
		Logger::copiesMade = 0;
	}
	static void resetConstructed() {
		Logger::constructed = 0;
	}
	static void printAndReset() {
		std::cout << "Copies made: " << Logger::copiesMade << std::endl;
		std::cout << "Constructed: " << Logger::constructed << "\n" << std::endl;
		resetCopies();
		resetConstructed();
	}
};

template <typename Collection>
void logCollectionParams(const Collection& collection) {
	std::cout << "\n" << "Current params:" << "\n" << "Size = " << collection.size() <<
		"\n" << "Capacity = " << collection.capacity() << "\n" << std::endl;
}


void test1() {
	std::cout << "Testing task 1" << std::endl;
	{
		std::cout << "Default constructing: " << std::endl;
		std::vector<Logger> loggers;
		logCollectionParams(loggers);
		Logger::printAndReset();

		for (int i = 1; i <= 10; ++i) {
			std::cout << "Pushing back element #" << i << ": " << std::endl;
			loggers.push_back(std::move(Logger()));
			logCollectionParams(loggers);
			Logger::printAndReset();
		}

		std::cout << "As we can see, in VS vector is 1.5x resized, "
			"to be more precise,\nin size + size / 2 times.\n"
			"Let us try to resize it up to 50 elements." << std::endl;
		loggers.resize(50);
		logCollectionParams(loggers);
		Logger::printAndReset();

		std::cout << "As we can see, capacity became the same as size.\n"
			"Let us now add one more element" << std::endl;
		loggers.push_back(std::move(Logger()));
		logCollectionParams(loggers);
		Logger::printAndReset();

		std::cout << "That's pure 1.5x.\n"
			"Let us figure out how big is maximum size. It equals "
			<< loggers.max_size() << ".\nLet us resize?\n"
			"It will take a lot of time.\n"
			"Better use the data which has been collected already"
			"\nunless you want to test it on your machine."
			"\nOtherwise just close the window." << std::endl;
		system("pause");

		loggers = std::vector<Logger>();
		std::ofstream data;
		data.open("data.csv");


		for (int i = 10; i >= 1; --i) {
			Timer<std::chrono::milliseconds> t;
			std::cout << "Resizing to " << i * 10 << " percent of maximum size: " << std::endl;
			try {
				loggers.assign(loggers.max_size() / 10 * i, Logger());
			}
			catch (std::exception& ex) {
				std::cout << "We can't resize to " << i * 10 << " percent of maximum size!" << std::endl;
				std::cout << ex.what();
				continue;
			}
			logCollectionParams(loggers);
			data << Logger::copiesMade + Logger::constructed << ", " << t.getDuration() << std::endl;
			Logger::printAndReset();
		}
		data.close();
	}
}