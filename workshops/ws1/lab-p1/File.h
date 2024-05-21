#ifndef FILE_H 
#define FILE_H

#include "ShoppingRec.h"

bool openFileForRead();
bool openFileForOverwrite();
void closeFile();
bool freadShoppingRec(ShoppingRec* rec);
void fwriteShoppintRec(const ShoppingRec* rec);

#endif