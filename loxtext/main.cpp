#include "includes.hpp"
#include "terminal.hpp"
#include "input.hpp"
#include "output.hpp"
#include "fileio.hpp"



int main(int argc, char* argv[]) {
    Terminal::enableRawMode();
    Terminal::initEditor();
    if(argc >= 2) {
        std::string filename(argv[1]);
        FileIO::editorOpen(filename);
    }
    
    Output::editorSetStatusMessage("HELP: Ctrl-Q = quit | Ctrl-S = save", std::vector<std::string>{});
    
    while(true) {
        Output::editorRefreashScreen();
        Input::editorProcessKeypress();
    }
    
    return 0;
}
