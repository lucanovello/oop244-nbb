#ifndef UTILS_H 
#define UTILS_H

void flushkeys();
bool ValidYesResponse(char ch);
bool yes();
void readCstr(char cstr[], int len);
int readInt(int min, int max);

#endif