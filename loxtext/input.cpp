

#include "input.hpp"
#include "terminal.hpp"
#include "editorOP.hpp"

void Input::editorProcessKeypress() {
    int c = Terminal::editorReadKey();
    
    if(c == Terminal::ctrl_key('q')) {
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);
        exit(0);
    } else if (c == Terminal::ctrl_key('h')) {
        
    } else if (c == Terminal::ctrl_key('l')) {
        
    }
    
    switch (c) {
        case '\r':
            break;
            
        case PAGE_UP:
        case PAGE_DOWN: {
            if (c == PAGE_UP) {
                E.cy = E.rowoff;
            } else if (c == PAGE_DOWN) {
                E.cy = E.rowoff + E.screenrows - 1;
                if(E.cy > E.numsrows) E.cy = E.numsrows;
            }
            
            int times = E.screenrows;
            while(times--) {
                editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
            }
            
            break;
        }
            
        case ARROW_LEFT:
        case ARROW_RIGHT:
        case ARROW_UP:
        case ARROW_DOWN:
            editorMoveCursor(c);
            break;
            
        case HOME_KEY:
            E.cx = 0;
            break;
        case END_KEY:
            if(E.cy < E.numsrows)
                E.cx = (int)E.row[E.cy].chars.size();
            break;
            
        case BACKSPACE:
        case DEL_KEY:
            
            break;
            
        case '\x1b':
            break;
            
            
        default:
            EditorOP::editorInsertChar(c);
            break;
    }
}

void Input::editorMoveCursor(int key) {
    Erow* row = (E.cy >= E.numsrows) ? nullptr : &E.row[E.cy];
    
    switch (key) {
        case ARROW_LEFT:
            if(E.cx > 0) {
                E.cx--;
            } else if(E.cy > 0) {
                E.cy--;
                E.cx = (int)E.row[E.cy].chars.size();
            }
            break;
        case ARROW_RIGHT:
            if(row && E.cx < row->chars.size()) {
                E.cx++;
            } else if(row && E.cx == row->chars.size()) {
                E.cy++;
                E.cx = 0;
            }
            break;
        case ARROW_UP:
            if(E.cy > 0) E.cy--;
            break;
        case ARROW_DOWN:
            if(E.cy < E.numsrows) E.cy++;
            break;
    }
    
    row = (E.cy >= E.numsrows) ? nullptr : &E.row[E.cy];
    int rowlen = row ? (int)row->chars.size() : 0;
    if(E.cx > rowlen) {
        E.cx = rowlen;
    }
}
