

#include "input.hpp"
#include "terminal.hpp"

void Input::editorProcessKeypress() {
    char c = Terminal::editorReadKey();
    
    if(c == Terminal::ctrl_key('q')) {
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);
        exit(0);
    }
}
