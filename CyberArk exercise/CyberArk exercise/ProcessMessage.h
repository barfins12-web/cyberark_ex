#pragma once
#include <Windows.h>
#include <iostream>

const auto BUFSIZE = 1024;
struct HandleDeleter {
	using pointer = HANDLE;
	void operator() (HANDLE h) {
		if (INVALID_HANDLE_VALUE != h) {
			CloseHandle(h);
		}
	}

};

using AutoHandle = std::unique_ptr<HANDLE, HandleDeleter>;

class ProcessMessage
{
public:
	ProcessMessage() noexcept;
	ProcessMessage(ProcessMessage& other) = delete;
	ProcessMessage(ProcessMessage&& other) = delete;
	ProcessMessage operator=(const ProcessMessage& other) = delete;
	ProcessMessage operator=(const ProcessMessage&& other) = delete;
	void sendMessage(std::string message) ;
	~ProcessMessage(){	}

private:
	AutoHandle pipe;

};

