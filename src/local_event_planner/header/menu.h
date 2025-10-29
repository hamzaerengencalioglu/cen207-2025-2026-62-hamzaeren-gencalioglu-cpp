#pragma once

#include "../../utility/header/commonTypes.h"

// Test modu bayrağı (TANIMI menu.cpp içinde)
extern bool isTestEnvironmentMenu;

// Tuş kodları
enum Key {
	NONE = 0,
	UP_ARROW = 1,
	DOWN_ARROW = 2,
	ENTER = 3
};

// API
int getInput();
int printMenu(const char menuItems[][30], int menuSize, int selectedIndex);
int runMenu(const char menuItems[][30], int menuSize);
int firstMenu();
int mainMenu(const int userID, const char* userName);