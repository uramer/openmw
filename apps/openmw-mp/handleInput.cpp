#include <Script/Script.hpp>
#include <Kbhit.h>
using namespace std;
namespace mwmp_input {
    string windowInputBuffer;
    void handler() {
        char c;
#ifndef WIN32
        while (kbhit()) {
            c = getch();
#else // on Windows conio.h getch() and kbhit() are deprecated, use _getch() and _kbhit() instead
        while (_kbhit()) {
            c = _getch();
#endif
            cout << c << flush;
            if (c == '\n' || c == '\r') { // handle carriage return as new line on Windows
                cout << endl;
                Script::Call<Script::CallbackIdentity("OnServerWindowInput")>(windowInputBuffer.c_str());
                windowInputBuffer.assign("");
            }
            else if (c == '\b') {
                windowInputBuffer.erase(windowInputBuffer.size() - 1);
            }
            else windowInputBuffer += c;
        }
    }
}
