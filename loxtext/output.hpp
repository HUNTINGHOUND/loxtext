#ifndef output_hpp
#define output_hpp

#include "includes.hpp"
#include "terminal.hpp"

const int tablen = 4;

namespace Output {
int editorRowCxtoRx(Erow& row, int cx);
void editorRefreashScreen();
void editorDrawRows(std::string* buffer);
void editorScroll();
void editorUpdateRows(Erow& row);
void editorDrawStatusBar(std::string* buffer);
void editorSetStatusMessage(const std::string& fmt, std::vector<std::string> args);
void editorDrawMessageBar(std::string* buffer);
void editorRowInsertChar(Erow& row, int at, int c);
}

#endif /* output_hpp */
