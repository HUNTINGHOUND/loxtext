#include "output.hpp"
#include "terminal.hpp"

void Output::editorRefreashScreen() {
    std::string buffer = "";
    
    buffer += "\x1b[?25l";
    buffer += "\x1b[H";
    
    editorDrawRows(&buffer);
    
    buffer += "\x1b[H";
    buffer += "\x1b[?25h";
    
    write(STDOUT_FILENO, buffer.c_str(), buffer.size());
}

void Output::editorDrawRows(std::string* buffer) {
    int y;
    for (y = 0; y < E.screenrows; y++) {
        if(y == E.screenrows / 3) {
            std::string welcome = "Lox builtin text editor -- version ";
            welcome += EDITOR_VERSION;
            
            int welcomelen = (int)welcome.size();
            if(welcome.size() < E.screencols) welcomelen = E.screencols;
            
            int padding = (E.screencols - welcomelen) / 2;
            if(padding) {
                buffer->append("~");
                padding--;
            }
            while(padding--) buffer->append(" ");
            
            buffer->append(welcome.substr(0,welcomelen));
            
        } else {
            
            buffer->append("~");
            buffer->append("\x1b[K");
        }
        
        if(y < E.screenrows - 1) {
            buffer->append("\r\n", 2);
        }
        
    }
}
