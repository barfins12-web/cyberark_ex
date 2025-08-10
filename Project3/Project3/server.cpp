#include <Windows.h>
#include <iostream>

struct HandleDeleter {
    using pointer = HANDLE;
    void operator() (HANDLE h) {
        if (INVALID_HANDLE_VALUE != h) {
            CloseHandle(h);
        }
    }

};

using AutoHandle = std::unique_ptr<HANDLE, HandleDeleter>;


int main(void){
    bool bConnected = false;

    auto hPipe = AutoHandle(CreateNamedPipe(L"\\\\.\\pipe\\nhsupspipe",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        NULL,
        0,
        0,
        NULL));

    // failed to create pipe?
    if (hPipe.get() == INVALID_HANDLE_VALUE) {
        return -1;
    }

    // Wait for the client to connect; if it succeeds, 
    // the function returns a nonzero value. If the function
    // returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 
    bConnected = ConnectNamedPipe(hPipe.get(), NULL) ? true : (GetLastError() == ERROR_PIPE_CONNECTED);
    BYTE message[100000];
    if (bConnected) {
        while (true) {
            unsigned long ulBytesRead = 0;
            // read client requests from the pipe. 
            bool bReadOk = ReadFile(hPipe.get(),
                &message,
                sizeof(message),
                &ulBytesRead,
                NULL);

            // bail if read failed [error or client closed connection]
            if (!bReadOk || ulBytesRead == 0)
                break;
            message[ulBytesRead] = '\0';
            std::cout << message << std::endl;

            // all ok, process the message received

        }
    }


    return 0;
}