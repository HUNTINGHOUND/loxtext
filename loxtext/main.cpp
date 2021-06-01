#include "includes.hpp"
#include "terminal.hpp"
#include "input.hpp"
#include "output.hpp"


int main() {
    Terminal::enableRawMode();
    Terminal::initEditor();
    
    while(true) {
        Output::editorRefreashScreen();
        Input::editorProcessKeypress();
    }
    
    return 0;
}
