
#ifndef terminal_hpp
#define terminal_hpp

#include "includes.hpp"

struct Erow {
    std::string chars;
    std::string render;
};


struct EditorConfig {
    int cx, cy;
    int rx;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numsrows;
    std::string statusmsg;
    time_t statusmsg_time;
    std::vector<Erow> row;
    termios og_termios;
    std::string filename;
};

extern EditorConfig E;

enum editorKey {
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    PAGE_UP,
    PAGE_DOWN,
    HOME_KEY,
    END_KEY,
    DEL_KEY
};

namespace Terminal {
void kill(const std::string& errorMessage);
char ctrl_key(char k);
void enableRawMode();
int editorReadKey();
void editorProcessKeypress();
int getWindowSize(int* rows, int* cols);
void initEditor();
int getCursorPosition(int* rows, int* cols);
};

#endif /* terminal_hpp */
