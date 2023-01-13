#include <chrono>
#include <cstring>
#include <string>
#include <thread>
#include <Windows.h>


int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while (true) {
        // async delay
        std::this_thread::sleep_for(std::chrono::seconds(60));

        // press space in case video is running
        INPUT space = { 0 };
        space.type = INPUT_KEYBOARD;
        space.ki.wVk = VK_SPACE;
        SendInput(1, &space, sizeof(INPUT)); // Send KeyDown
        space.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &space, sizeof(INPUT)); // Send KeyUp

        // current time
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        // elapsed time
        int elapsed_time = std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() / 60;
        // initialise message
        std::wstring time = L"Is the baby hungry?\nMinutes since last feeding: " + std::to_wstring(elapsed_time);
        // generate windows box
        MessageBox(nullptr, (time).c_str(), TEXT("Message"), MB_OK);
    }
}