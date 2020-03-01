#include <Script/Script.hpp>
#include <Kbhit.h>
using namespace std;
namespace mwmp_input {
    string windowInputBuffer;
    void handler() {
        char c;
#ifndef WIN32 // on WIndows conio.h getch() and kbhit() are deprecated, use _getch() and _kbhit() instead
        while (kbhit()) {
            c = getch();
#else
        while (_kbhit()) {
            c = _getch();
#endif
            cout << c << flush;
            if (c == '\n' || c == '\r') { // handle carriage return as new line on Windows
                cout << endl;
                Script::Call<Script::CallbackIdentity("OnServerWindowInput")>(windowInputBuffer.c_str());
                windowInputBuffer.assign("");
            }
            else windowInputBuffer += c;
        }
    }
}
