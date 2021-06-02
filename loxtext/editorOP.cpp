//
//  editorOP.cpp
//  loxtext
//
//  Created by Morgan Xu on 6/2/21.
//


#include "editorOP.hpp"
#include "output.hpp"

void EditorOP::editorInsertChar(int c) {
    if(E.cy == E.numsrows) {
        E.row.push_back(Erow{"",""});
        Output::editorUpdateRows(E.row.back());
    }
    
    Output::editorRowInsertChar(E.row[E.cy], E.cx, c);
    E.cx++;
}
