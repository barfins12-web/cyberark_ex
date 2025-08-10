#include "helpers.h"
#include <tchar.h>

int main() {
	const uint16_t vecSize = 5;
	const auto vec = getRandomValues(vecSize);
	printVectorValues(vec);

	for (uint16_t i = 0; i < vecSize; i++) {
		const auto currentNumber = vec[i];
		categorizeNumber(currentNumber);
	}
	auto pm = ProcessMessage();
	pm.sendMessage(sendAll);
	
	return 0;
}