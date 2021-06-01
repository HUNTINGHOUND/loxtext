
#ifndef terminal_hpp
#define terminal_hpp

#include "includes.hpp"

struct EditorConfig {
    int cx, cy;
    int screenrows;
    int screencols;
    termios og_termios;
};

extern EditorConfig E;

namespace Terminal {
void kill(const std::string& errorMessage);
char ctrl_key(char k);
void enableRawMode();
char editorReadKey();
void editorProcessKeypress();
int getWindowSize(int* rows, int* cols);
void initEditor();
int getCursorPosition(int* rows, int* cols);
};

#endif /* terminal_hpp */
