#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

#include "../../local_event_planner/header/brent_hashing.h"

int loadUsersFromBinaryFile(HashTable* ht, const char* filename);
int saveUsersToBinaryFile(const HashTable* ht, const char* filename);
int getNextID(const char* filename, size_t recordSize);

char* getFormattedDate(int daysToAdd);

#endif // FILE_UTILITY_H