#include "includes.h"


/// <summary>Represents an entry in the list.</summary>
typedef struct ListElement {
	struct ListElement* previous;
	struct ListElement* next;
	char name[INPUT_LENGTH + 1];
	char hobby[INPUT_LENGTH + 1];
	char postcode[INPUT_LENGTH_PLZ + 1];
	char city[INPUT_LENGTH + 1];
}ListElement;

/// <summary>Represents the container containing ervery important ListItem.</summary>
typedef struct {
	unsigned int elementCount, maxElementsPerPage;
	bool pointersShown, autosave, search_caseSensitive, sort_ascending;
	ListElement *first, *current;
}ListContainer;

/// <summary>This function will be called once the LinkedList is accessed from the menu.</summary>
/// <param name="c">The container containing every important ListItem.</param>
void mainMenu(ListContainer* c);


/* -----[Submenu]----- */

/// <summary>Displays a menu wih options to show the elements in a list or as pages.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void submenu_show(ListContainer* container);

/// <summary>Displays a menu wih options to add a single element or a specific amount of elements.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void submenu_add(ListContainer* container);

/// <summary>Displays a menu wih options to remove a single element, a range of elements, or all elements.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void submenu_remove(ListContainer* container);

/// <summary>Displays a menu wih options to sort after every parameter of a ListItem.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void submenu_sort(ListContainer* container);

/// <summary>Displays a menu wih options to save to the default file, a custom file or turn autosave on/off.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void submenu_save(ListContainer* container);

/// <summary>Displays a menu wih options to restore contens from the default file, the latest autosave or a custom path</summary>
/// <param name="container">The container containing every important ListItem.</param>
void submenu_get(ListContainer* container);

/// <summary>Displays a menu with all settings</summary>
/// <param name="container">The container containing every important ListItem.</param>
void submenu_settings(ListContainer* container);


/* -----[Show]----- */

/// <summary>Prints out all elements and their contents to the console.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void showList(ListContainer* container);

/// <summary>Prints out a single element to the console. Supports paging.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void showPage(ListContainer* container);


/* -----[Add]----- */

/// <summary>Adds a new element at the end of the list.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void addElement(ListContainer* container);

/// <summary>Adds a new element at a specific position.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void addElementAt(ListContainer* container);

/// <summary>Adds mutiple elements at the end of the list.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void addMultipleElements(ListContainer* container);

/// <summary>Clones an existing element and adds it to the list.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void cloneElement(ListContainer* container);

/// <summary>Lets the user fill out the contents of the element.</summary>
/// <param name="container">The container containing every important ListItem.</param>
ListElement* fillElement(ListContainer*container);

/// <summary>Links the new element in the list to the corresponding elements.</summary>
/// <param name="container">The container containing every important ListItem.</param>
/// <param name="element">The new element.</param>
/// <param name="position">The position the item should be added at.</param>
void linkElement(ListContainer* container, ListElement* element, int position);


/* -----[Remove]----- */

/// <summary>Removes a specific element and links the other elements back together</summary>
/// <param name="toBeDeleted">The element which will be removed.</param>
/// <param name="container">The container containing every important ListItem.</param>
void removeElement(ListElement* toBeDeleted, ListContainer* container);

/// <summary>Removes a single element at a specific position</summary>
/// <param name="container">The container containing every important ListItem.</param>
void removeElementAt(ListContainer* container);

/// <summary>Removes all elements in a specified range</summary>
/// <param name="container">The container containing every important ListItem.</param>
void removeElementsInRange(ListContainer* container);

/// <summary>Removes all elements of the list</summary>
/// <param name="container">The container containing every important ListItem.</param>
void removeAllElements(ListContainer* container);

void removeIdenticalElements(ListContainer* container);


/* -----[Search]----- */

/// <summary>Initiates the search for a specific content.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void searchElement(ListContainer* container);

/// <summary>Searches for a specific element fulfilling the criteria.</summary>
/// <param name="token">The category which will be searched in.</param>
/// <param name="value">The value which will be searched for.</param>
/// <param name="container">The container containing every important ListItem.</param>
void searchFor(char* token, char* value, ListContainer* container);


/* -----[Sort]----- */

/// <summary>Sorts the elements after the name.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void sortName(ListContainer* container);

/// <summary>Sorts the elements after the hobby.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void sortHobby(ListContainer* container);

/// <summary>Sorts the elements after the postcode.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void sortPLZ(ListContainer* container);

/// <summary>Sorts the elements after the city.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void sortCity(ListContainer* container);

/// <summary>Starts the sorting with the given criteria.</summary>
/// <param name="container">The container containing every important ListItem.</param>
/// <param name="criteria">The criteria to be sorted after.</param>
void sort(ListContainer* container, char* criteria);

/// <summary>Sorts the list with a recursion quicksort.</summary>
/// <param name="container">The container containing every important ListItem.</param>
/// <param name="left">The left index.</param>
/// <param name="right">The right index.</param>
/// <param name="sortType">The criteria to be sorted after.</param>
void quicksort(ListContainer* container, int left, int right, char* sortType);

/// <summary>Swaps the content of two elements.</summary>
/// <param name="element1">The first element.</param>
/// <param name="element2">The second element.</param>
void swapElements(ListElement* element1, ListElement* element2);


/* -----[File Handling]----- */

/// <summary>Gets the user input for file saving / restoring.</summary>
/// <param name="message">The message to be printed to the user.</param>
char* getPath(char* message);

/// <summary>Saves the entries of the list to the default .txt-file.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void saveContent(ListContainer* container);

/// <summary>Saves the entries of the list to a custom .txt-file.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void saveContentTo(ListContainer* container);

/// <summary>Prints out the content of the list to a file with a given path.</summary>
/// <param name="path">The path of the file.</param>
/// <param name="container">The container containing every important ListItem.</param>
void writeFile(char* path, ListContainer* container);

/// <summary>Restores a previously saved list from the default file.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void getContent(ListContainer* container);

/// <summary>Restores a previously saved list from a custom file.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void getContentFrom(ListContainer* container);

/// <summary>Restores a previously autosaved list.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void restoreAutosave(ListContainer* container);

/// <summary>Reads the contents of a file.</summary>
/// <param name="path">The path of the file.</param>
/// <param name="container">The container containing every important ListItem.</param>
bool readFile(char* path, ListContainer* container);


/* -----[Settings]----- */

/// <summary>Switches the given bool and prints a success message</summary>
/// <param name="message">The message to be printed.</param>
/// <param name="value">The bool to be changed.</param>
void switchBool(char* message, bool* value);

/// <summary>Turns pointers in the print functions on/off</summary>
/// <param name="container">The container containing every important ListItem.</param>
void switchPointersShown(ListContainer* container);

/// <summary>Turns autosave on/off.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void switchAutosave(ListContainer* container);

/// <summary>Turns case sensitve search on/off.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void switchCaseSensitive(ListContainer* container);

/// <summary>Allows the user to change the maximum elements per page when printing the list view.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void changeMaxElementsPerPage(ListContainer* container);

/// <summary>Allows the user to change the maximum elements per page when printing the list view.</summary>
/// <param name="container">The container containing every important ListItem.</param>
void switchSortOrder(ListContainer* container);


/* -----[Utility]----- */

/// <summary>Gets the user input and, if given, checks if the position is valid.</summary>
/// <param name="toWrite">The adress of the integer.</param>
/// <param name="message">The message to be displayed to the user.</param>
/// <param name="performCheck">Specifies whether the entered position is valid.</param>
/// <param name="container">The container containing every important ListItem.</param>
bool getPosition(int* toWrite, char* message, bool performCheck, ListContainer* container);

/// <summary>Returns the element at the specified position.</summary>
/// <param name="container">The container containing every important ListItem.</param>
/// <param name="position">The position of the item which will be returned.</param>
ListElement* getElementAt(ListContainer* container, int position);

/// <summary>Returns whether the list contains any items.</summary>
/// <param name="container">The container containing every important ListItem.</param>
bool firstElementCreated(ListContainer* container);

/// <summary>Returns whether there can be an item at the specified position.</summary>
/// <param name="container">The container containing every important ListItem.</param>
/// <param name="position">The position which needs the be verified.</param>
bool isElementAt(ListContainer* container, unsigned int position);

/// <summary>Creates a Yes / No Dialog.</summary>
/// <param name="message">The message which will be displayed to the user.</param>
/// <param name="element">The element which will be printed out if specified.</param>
/// <param name="printInfo">Specifies whether the element will be printed to the console.</param>
bool yesNoDialog(char* message, ListElement* element, bool printInfo);

/// <summary>Returns whether the specified item has a successor.</summary>
/// <param name="container">The container containing every important ListItem.</param>
bool hasNextElement(ListElement* item);

/// <summary>Returns whether the specified item has a predecessor.</summary>
/// <param name="container">The container containing every important ListItem.</param>
bool hasPreviousElement(ListElement* item);

/// <summary>Clears the input buffer.</summary>
void clearBuffer(void);
