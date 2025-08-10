#include "ProcessMessage.h"


ProcessMessage:: ProcessMessage() noexcept  {

    this->pipe = AutoHandle(CreateFile(L"\\\\.\\pipe\\nhsupspipe",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL));

    if (INVALID_HANDLE_VALUE == pipe.get()) {
        std::cout << "Error creating named pipe" << std::endl;

    }

}


void ProcessMessage::sendMessage(std::string message)  {
    unsigned long ulBytesWritten = 0;
    bool bWriteOk = WriteFile(this->pipe.get(),
        reinterpret_cast<LPCVOID>(message.data()),
        message.size(),
        &ulBytesWritten,
        NULL);

    if (!bWriteOk || ulBytesWritten < 3) {
        return;
    }

}