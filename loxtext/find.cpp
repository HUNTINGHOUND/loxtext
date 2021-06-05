#include "find.hpp"
#include "output.hpp"
#include "input.hpp"

void Find::editorFind() {
    int og_cx = E.cx;
    int og_cy = E.cy;
    int og_coloff = E.coloff;
    int og_rowoff = E.rowoff;
    
    std::function<void(std::string&, int)> callback = editorFindCallback;
    std::string query = Input::editorPrompt("Search: % (ESC to cancel)", &callback);
    if(!query.empty()) return;
    
    E.cx = og_cx;
    E.cy = og_cy;
    E.coloff = og_coloff;
    E.rowoff = og_rowoff;
}

void Find::editorFindCallback(std::string& query, int key) {
    static int last_matchy = -1;
    static int last_matchx = -1;
    static int direction = 1;
    
    std::fstream log("log.txt");
    log << "query is: " << query << "\n";
    
    if(key == '\r' || key == '\x1b') {
        last_matchy = -1;
        last_matchx = -1;
        direction = 1;
        return;
    } else if(key == ARROW_RIGHT || key == ARROW_DOWN) {
        log << "Input key: arrow right or down\n";
        direction = 1;
    } else if(key == ARROW_LEFT || key == ARROW_UP) {
        log << "Input key: arrow left or up\n";
        direction = -1;
    } else {
        last_matchy = -1;
        last_matchx = -1;
        direction = 1;
    }
    
    if(last_matchy == -1) direction = 1;
    int current = last_matchy;
    if(current == -1) current = 0;
    for(int i = 0; i <= E.numsrows; i++) {
        log << "last x = " << last_matchx << "\n";
        log << "last y = " << last_matchy << "\n";
        log << "direction = " << direction << "\n";
        log << "current = " << current << "\n";
        Erow* row = &E.row[current];
        
        size_t pos;
        if(i == 0 && last_matchx != -1) {
            if(direction == 1) {
                log << "here \n";
                if(last_matchx == row->render.size()) pos = std::string::npos;
                else {
                    pos = row->render.substr(last_matchx + 1, std::string::npos).find(query);
                    pos += pos == std::string::npos ? 0 : last_matchx + 1;
                    log << "pos here = " << pos << '\n';
                }
            } else {
                if(last_matchx == 0) pos = std::string::npos;
                else pos = row->render.substr(0, last_matchx + query.size() - 1).rfind(query);
            }
        } else {
            if(direction == 1) pos = row->render.find(query);
            else pos = row->render.rfind(query);
        }
        
        if(pos != std::string::npos) {
            log << "found pos = " << pos << "\n";
            last_matchy = current;
            last_matchx = pos;
            E.cy = current;
            E.cx = Output::editorRowRxToCx(*row, pos);
            E.rowoff = E.numsrows;
            break;
        }
        current += direction;
        if(current == -1) current = E.numsrows - 1;
        else if(current == E.numsrows) current = 0;
    }
    log << "===================================\n\n";
}
