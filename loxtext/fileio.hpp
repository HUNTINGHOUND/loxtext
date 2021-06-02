//
//  fileio.hpp
//  loxtext
//
//  Created by Morgan Xu on 6/1/21.
//

#ifndef fileio_hpp
#define fileio_hpp

#include "includes.hpp"

namespace FileIO {
void editorOpen(std::string& filename);
bool editorRowstoString(std::string* buffer, int& rowsread);
void editorSave();
}


#endif /* fileio_hpp */
