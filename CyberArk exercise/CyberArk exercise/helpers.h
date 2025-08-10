#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "ProcessMessage.h"

constexpr auto DIGITS_NUMBER = 3;
constexpr auto FIRST_DIGIT = 1;
constexpr auto GET_LAST_DIGIT = 10;
constexpr auto REMOVE_LAST_DIGIT = 10;
constexpr auto MAX_RAND_NUMBER = 1000;
std::string sendAll = "";

void printVectorValues(const std::vector<uint16_t>& vec) {
	for (uint16_t i = 0; i < vec.size(); i++) {
		sendAll += std::to_string((vec[i])) + " ";
	}
	std::cout << std::endl;
}
std::vector<uint16_t> getRandomValues(const uint16_t amount) {
	std::srand(unsigned(std::time(nullptr)));
	std::vector<uint16_t>  v(amount);
	for (int i = 0; i < amount; ++i)
		v[i] = rand() % MAX_RAND_NUMBER;
	return v;
}

bool isOdd(const uint16_t number) {
	return number % 2 == 1;
}

bool startsWithOne(uint16_t number) {
	uint16_t firstDigit = number % GET_LAST_DIGIT;
	while (number > 10) {
		number /= REMOVE_LAST_DIGIT;
		firstDigit = number % GET_LAST_DIGIT;
	}

	return FIRST_DIGIT == firstDigit;
}

std::pair<uint16_t, uint16_t> containsThreeDigits(uint16_t number) {
	uint16_t countDigits = 0;
	uint16_t multi = 1;
	
	while (number > 0 and countDigits <= DIGITS_NUMBER + 1) {
		countDigits++;
		multi *= number % GET_LAST_DIGIT;
		number /= REMOVE_LAST_DIGIT;
		
	}
	
	return { countDigits, multi };
}
void  categorizeNumber(const uint16_t currentNumber) {
	if (isOdd(currentNumber)) {
		sendAll += std::to_string(currentNumber) + ": This is an odd number\n";
	}
	else if (startsWithOne(currentNumber)) {
		sendAll += std::to_string(currentNumber) + ": starts with 1\n";
		sendAll += "Origin values: \n";
		auto randomVec = getRandomValues(currentNumber);
		printVectorValues(randomVec);
		sendAll += "Sorted values: \n";
		auto sortedVec = randomVec;
		stable_sort(sortedVec.begin(), sortedVec.end());
		printVectorValues(sortedVec);
	}
	else {

		auto result = containsThreeDigits(currentNumber);
		if (DIGITS_NUMBER == result.first) {
			sendAll += std::to_string(currentNumber) +": the digit's multiplications are equal to: " + std::to_string(result.second) + "\n";

		}
		else {
			sendAll += std::to_string(currentNumber) +": this number belongs to the others\n";
		}
	}



}