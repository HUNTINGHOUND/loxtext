//
//  fileio.cpp
//  loxtext
//
//  Created by Morgan Xu on 6/1/21.
//

#include "fileio.hpp"
#include "terminal.hpp"
#include "output.hpp"

void FileIO::editorOpen(std::string& filename) {
    E.filename = filename;
    
    std::fstream file(filename);
    if(!file.is_open()) Terminal::kill("fstream open");
    
    std::string line("");
    while(std::getline(file, line)) {
        E.row.push_back(Erow{line, ""});
        Output::editorUpdateRows(E.row.back());
        E.numsrows++;
    }
    file.close();
}

bool FileIO::editorRowstoString(std::string* buffer, int& rowsread) {
    while(rowsread < E.numsrows) {
        if(buffer->size() + E.row[rowsread].chars.size() >= buffer->max_size()) {
            //max sized exceeded
            return false;
        }
        
        buffer->append(E.row[rowsread++].chars);
    }
    
    //all rows read
    return true;
}

void FileIO::editorSave() {
    
}
