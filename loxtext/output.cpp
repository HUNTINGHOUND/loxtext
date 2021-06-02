#include "output.hpp"

void Output::editorScroll() {
    E.rx = E.cx;
    if(E.cy < E.numsrows) {
        E.rx = editorRowCxtoRx(E.row[E.cy], E.cx);
    }
    
    if(E.cy < E.rowoff) {
        E.rowoff = E.cy;
    }
    if(E.cy >= E.rowoff + E.screenrows) {
        E.rowoff = E.cy - E.screenrows + 1;
    }
    if(E.rx < E.coloff) {
        E.coloff = E.rx;
    }
    if(E.rx >= E.coloff + E.screencols) {
        E.coloff = E.rx - E.screencols + 1;
    }
}

void Output::editorRefreashScreen() {
    editorScroll();
    std::string buffer = "";
    
    buffer += "\x1b[?25l";
    buffer += "\x1b[H";
    
    editorDrawRows(&buffer);
    editorDrawStatusBar(&buffer);
    editorDrawMessageBar(&buffer);
    
    buffer += "\x1b[";
    buffer += std::to_string((E.cy - E.rowoff) + 1);
    buffer += ";";
    buffer += std::to_string((E.rx - E.coloff) + 1);
    buffer += "H";
    
    buffer += "\x1b[?25h";
    
    write(STDOUT_FILENO, buffer.c_str(), buffer.size());
}

void Output::editorDrawRows(std::string* buffer) {
    int y;
    for (y = 0; y < E.screenrows; y++) {
        int filerow = y + E.rowoff;
        if(filerow >= E.numsrows) {
            if(E.numsrows == 0 && y == E.screenrows / 3) {
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
            }
        } else {
            int len = (int)E.row[filerow].render.size() - E.coloff;
            if(len < 0) len = 0;
            if(len > E.screencols) len = E.screencols;
            if(len != 0) buffer->append(E.row[filerow].render.substr(E.coloff, len));
        }
        
        buffer->append("\x1b[K");
        buffer->append("\r\n");
    }
}

void Output::editorUpdateRows(Erow& row) {
    row.render = "";
    
    for(int j = 0; j < row.chars.size(); j++) {
        if(row.chars[j] == '\t') {
            row.render += ' ';
            while(row.render.size() % tablen != 0) row.render += ' ';
        } else {
            row.render += row.chars[j];
        }
    }
}

int Output::editorRowCxtoRx(Erow &row, int cx) {
    int rx = 0;
    int j;
    for(j = 0; j < cx; j++) {
        if(row.chars[j] == '\t')
            rx += (tablen - 1) - (rx % tablen);
        rx++;
    }
    
    return rx;
}

void Output::editorDrawStatusBar(std::string* buffer) {
    buffer->append("\x1b[7m");
    
    std::stringstream status, rstatus;
    status << std::setw(20) << (E.filename.empty() ? "[No Name]" : E.filename) << " - " << E.numsrows << " lines";
    std::string statusStr = status.str();
    int len = (int)statusStr.size();
    
    rstatus << E.cy + 1 << "/" << E.numsrows;
    std::string rstatusStr = rstatus.str();
    int rlen = (int)rstatusStr.size();
    
    if(len > E.screencols) len = E.screencols;
    buffer->append(statusStr.substr(0, len));
    
    while(len < E.screencols) {
        if (E.screencols - len == rlen) {
            buffer->append(rstatusStr);
            break;
        } else {
            buffer->append(" ");
            len++;
        }
    }
    
    buffer->append("\x1b[m");
    buffer->append("\r\n");
}

void Output::editorSetStatusMessage(const std::string& fmt, std::vector<std::string> args) {
    E.statusmsg = "";
    int argsi = 0;
    for(int i = 0; i < fmt.size(); i++) {
        if(fmt[i] == '%') {
            E.statusmsg += args[argsi++];
        } else {
            E.statusmsg += fmt[i];
        }
    }
    E.statusmsg_time = time(nullptr);
}

void Output::editorDrawMessageBar(std::string *buffer) {
    buffer->append("\x1b[K");
    int msglen = (int)E.statusmsg.size();
    if(msglen > E.screencols) msglen = E.screencols;
    if(msglen && time(nullptr) - E.statusmsg_time < 5)
        buffer->append(E.statusmsg.substr(0,msglen));
}

void Output::editorRowInsertChar(Erow& row, int at, int c) {
    if(at < 0 || at > row.chars.size()) at = row.chars.size();
    
    std::string tobeinserted = "";
    tobeinserted += (char)c;
    row.chars.insert(at, tobeinserted);
    editorUpdateRows(row);
}
