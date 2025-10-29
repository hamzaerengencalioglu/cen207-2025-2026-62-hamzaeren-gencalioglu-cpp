#include "../header/menu.h"
#include <user_authentication.h>

/**
 *  @name   isTestEnvironmentMenu
 *
 *  @brief  Global flag to indicate test environment for menu operations.
 *
 *  @details
 *  When set to true, interactive input and screen operations are bypassed.
 *  This allows unit testing of menu functions without user interaction.
 *
 *  @note   Used by getInput(), printMenu(), runMenu(), and firstMenu().
 */
bool isTestEnvironmentMenu = false;

#ifndef _WIN32
// Unix-like sistemler için güvenli getch
static int getch_unix() {
	termios oldt{}, newt{};
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= static_cast<unsigned>(~(ICANON | ECHO));
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	int ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#endif

/**
 *  @name   getInput
 *
 *  @brief  Captures keyboard input and maps it to menu navigation constants.
 *
 *  @details
 *  - Handles both Windows (`_getch`) and Unix-like input methods.
 *  - Maps arrow keys to predefined constants: `UP_ARROW`, `DOWN_ARROW`.
 *  - Returns `ENTER` when the Enter key is pressed.
 *  - Returns `NONE` for any other key.
 *
 *  @retval [\b int] One of the following:
 *          - `UP_ARROW`    : User pressed the up key.
 *          - `DOWN_ARROW`  : User pressed the down key.
 *          - `ENTER`       : User pressed Enter.
 *          - `NONE`        : No valid navigation input detected.
 *
 *  @note   If `isTestEnvironmentMenu` is true, always returns ENTER.
 */
int getInput() 
{
	if (isTestEnvironmentMenu) 
		return ENTER;

#ifdef _WIN32
	int ch = _getch();

	if (ch == 0 || ch == 224) 
	{
		ch = _getch();
		switch (ch) {
		case 72: return UP_ARROW;
		case 80: return DOWN_ARROW;
		default: return NONE;
		}
	}
	if (ch == 13) return ENTER;
	return NONE;
#else
	int ch = getch_unix();
	if (ch == 27) { // ESC [
		int ch2 = getch_unix();
		if (ch2 == '[') 
		{
			int ch3 = getch_unix();
			switch (ch3) {
			case 'A': return UP_ARROW;
			case 'B': return DOWN_ARROW;
			default:  return NONE;
			}
		}
	}
	if (ch == '\n') return ENTER;
	return NONE;
#endif
}

/**
 *  @name   printMenu
 *
 *  @brief  Displays the menu with highlighting for the currently selected item.
 *
 *  @param  [in] menuItems     [\b const char[][30]]  Array of menu item labels.
 *  @param  [in] menuSize      [\b int]               Total number of items.
 *  @param  [in] selectedIndex [\b int]               Index of the highlighted item.
 *
 *  @retval [\b int] 1 on successful print.
 *
 *  @details
 *  Clears the console screen, prints all menu items, and prefixes the selected
 *  one with a “>” marker. Also shows navigation instructions.
 *
 *  @note   If `isTestEnvironmentMenu` is true, skips rendering and returns 1.
 */
int printMenu(const char menuItems[][30], int menuSize, int selectedIndex) 
{
	if (isTestEnvironmentMenu) 
		return 1;

	CLEAR_SCREEN();
	std::printf("=== MENU ===\n");
	for (int i = 0; i < menuSize; ++i) 
	{
		std::printf("%s %s\n", (i == selectedIndex ? ">" : " "), menuItems[i]);
	}
	std::printf("\nYön tuşlarıyla gez, ENTER ile seç.\n");
	return 1;
}

/**
 *  @name   runMenu
 *
 *  @brief  Handles menu navigation and selection logic.
 *
 *  @param  [in] menuItems [\b const char[][30]]  Array of menu labels.
 *  @param  [in] menuSize  [\b int]               Number of menu items.
 *
 *  @retval [\b int] Index of the selected menu item when Enter is pressed.
 *
 *  @details
 *  Continuously displays the menu and processes user key input using
 *  `getInput()`. Updates the highlighted index according to arrow key input.
 *  When Enter is pressed, clears the screen and returns the current selection.
 *
 *  @note
 *  - If `isTestEnvironmentMenu` is true, returns 0 immediately.
 *  - Uses circular navigation (wraps from first to last item and vice versa).
 *
 *  @complexity  O(menuSize) per full redraw cycle.
 */
int runMenu(const char menuItems[][30], int menuSize) 
{
	if (isTestEnvironmentMenu) 
		return 0;

	int selectedIndex = 0;
	while (true) 
	{
		printMenu(menuItems, menuSize, selectedIndex);
		int input = getInput();

		switch (input) 
		{
		case UP_ARROW:
			selectedIndex = (selectedIndex - 1 + menuSize) % menuSize;
			break;
		case DOWN_ARROW:
			selectedIndex = (selectedIndex + 1) % menuSize;
			break;
		case ENTER:
			CLEAR_SCREEN();
			return selectedIndex;
		default:
			break;
		}
	}
}

/**
 *  @name   firstMenu
 *
 *  @brief  Displays the initial user interaction menu (Register/Login/Guest/Exit).
 *
 *  @retval [\b int] 0 on exit or test termination.
 *
 *  @details
 *  Presents four main options:
 *  - Register → Calls `initiateUserRegistration()`
 *  - Login → Calls `initiateUserLogin()`
 *  - Guest Mode → Placeholder for guest functionality
 *  - Exit → Terminates the program
 *
 *  Handles looping user input until Exit is chosen.
 *
 *  @note
 *  - When in test mode, the menu returns immediately for automation.
 *  - Uses `runMenu()` for navigation logic.
 *
 *  @warning
 *  Future implementations should define `guestMenu()` before activation.
 */
int firstMenu()
{
	const char mainMenuItems[][30] = 
	{
		"Register",
		"Login",
		"Guest Mode",
		"Exit"
	};

	while (true) 
	{
		int selection = runMenu(mainMenuItems, sizeof(mainMenuItems) / sizeof(mainMenuItems[0]));

		switch (selection) 
		{
		case 0:
			if (isTestEnvironmentMenu) return 0;
			initiateUserRegistration();
			break;
		case 1:
			if (isTestEnvironmentMenu) return 0;
			initiateUserLogin();
			break;
		case 2:
			if (isTestEnvironmentMenu) return 0;
			//guestMenu();
			break;
		case 3:
			printf("Exiting...\n");
			return 0;
		default:
			printf("Invalid selection!\n");
			break;
		}
	}
}

int mainMenu(const int userID, const char* userName)
{
	const char mainMenuItems[][30] = 
	{
		"add event",
		"view events",
		"logout"

	};
	return 1;
}