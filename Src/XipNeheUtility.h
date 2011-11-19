#ifndef XIP_NEHE_UTILITY_H
#define XIP_NEHE_UTILITY_H

#include <string>

//std::string convertRGBtoHex(const int num);
//std::string convertRGBtoHex(const int r,const int g,const int b); 
unsigned int convertRGBtoHex(const int r,const int g,const int b);

//fix me: part of XipOverlay but function not exported...
int getFontFile(const char*	lpszFontName,char* lpszDisplayName, int nDisplayNameSize, char* lpszFontFile, int	nFontFileSize );

#endif //XIP_NEHE_UTILITY_H