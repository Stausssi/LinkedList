#include "linkedList.h"

int main(void) {
	ListContainer *container = malloc(sizeof(ListContainer));

	container->first = 0;
	container->current = 0;
	container->elementCount = 0;
	container->maxElementsPerPage = 25;
	container->pointersShown = false;
	container->autosave = true;
	container->search_caseSensitive = true;
	container->sort_ascending = true;

	mainMenu(container);
}


/* -----[Show]----- */

void showList(ListContainer* container) {
	int position = 0, start;
	char key;
	ListElement* helpElement = container->first;

	printf("Die Liste enth"ä"lt folgende Elemente:\n\n");
	do {
		system("cls");

		printf(
			"%8s %21s %10s %22s %25s",
			"Position",
			"Name der Person",
			"Postleitzahl",
			"Stadt",
			"Hobby"
		);

		if (container->pointersShown) printf(" | %8s %8s %8s", "Zeiger", "Davor", "Danach");

		start = ++position;
		putchar('\n');

		do {
			printf(
				" %3d %25s %9s %25s %25s",
				position++,
				helpElement->name,
				helpElement->postcode,
				helpElement->city,
				helpElement->hobby
			);

			if (container->pointersShown) printf(" | %p %p %p", helpElement, helpElement->previous, helpElement->next);

			putchar('\n');

			helpElement = helpElement->next;
		} while (helpElement != 0 && position - start < container->maxElementsPerPage);

		printf("\nZeige die Eintr"ä"ge %d-%d.\n", start, position-- - 1);

		if (position < container->elementCount) {
			printf("Weiter mit beliebiger Taste, beenden mit 'q'!");
			key = _getch();
		}
		else
			key = 'q';
	} while (key != 'q' && key != 'Q');
}

void showPage(ListContainer* container) {
	int pageIndex = 1;
	ListElement* helpElement = container->first;
	char input;

	do {
		system("cls");

		printf("Seiten wechseln mit 'a'/'d', beenden mit 'q'!\n\n");

		printf("Element %d:\n", pageIndex);

		printf("- %-7s %s\n- %-7s %s\n- %-7s %s\n- %-7s %s\n",
			"Name:", helpElement->name,
			"Hobby:", helpElement->hobby,
			"PLZ:", helpElement->postcode,
			"Stadt:", helpElement->city
		);

		if (container->pointersShown)
			printf(
				"\n- %-7s %p\n  - %-7s %p\n  - %-7s %p",
				"Zeiger:", helpElement,
				"Davor:", helpElement->previous,
				"Danach:", helpElement->next
			);

		putchar('\n');
		printf("> ");

		input = tolower(_getch());

		if (input == 'a' && pageIndex > 1) {
			pageIndex--;
			helpElement = helpElement->previous;
		}
		if (input == 'd' && pageIndex < container->elementCount) {
			pageIndex++;
			helpElement = helpElement->next;
		}

	} while (input != 'q');
}


/* -----[Add]----- */

void addElement(ListContainer* container) {
	linkElement(container, fillElement(container), container->elementCount + 1);

	printf("Neues Element wurde hinzugef"ü"gt!");
}

void addElementAt(ListContainer* container) {
	int pos = 0;

	getPosition(&pos, "An welcher Stelle soll das Element hinzugef"ü"gt werden", false, container);

	if (pos >= 1 && pos <= container->elementCount + 1) {
		linkElement(container, fillElement(container), pos);
		printf("Neues Element wurde hinzugef"ü"gt!");
	}
	else
		printf("Die angegebene Position %d ist ung"ü"ltig!", pos);
}

void addMultipleElements(ListContainer* container) {
	int count;

	getPosition(&count, "Wie viele Elemente sollen hintereinander hinzugef"ü"gt werden", false, container);

	if (count <= 10)
		for (int i = 0; i < count; i++) {
			system("cls");
			addElement(container);
		}
	else
		printf("Es k"ö"nnen maximal 10 Elemente nacheinander eingef"ü"gt werden");
}

void cloneElement(ListContainer* container) {
	int pos;

	if (getPosition(&pos, "Welche Position soll dupliziert werden", true, container)) {
		ListElement
			* clonedElement = malloc(sizeof(ListElement)),
			* toBeCloned = getElementAt(container, pos);

		if (yesNoDialog("Soll dieses Element dupliziert werden", toBeCloned, true)) {

			clonedElement->next = NULL;
			clonedElement->previous = NULL;

			if (yesNoDialog("Soll dieses Element noch bearbeitet werden", clonedElement, false)) {
				printf("Um ein Wert nicht zu "ü"berschreiben einfach leer lassen!\n\n");
				clonedElement = fillElement(container);

				if (strcmp(clonedElement->name, "") == 0) strcpy(clonedElement->name, toBeCloned->name);
				if (strcmp(clonedElement->hobby, "") == 0) strcpy(clonedElement->hobby, toBeCloned->hobby);
				if (strcmp(clonedElement->postcode, "") == 0) strcpy(clonedElement->postcode, toBeCloned->postcode);
				if (strcmp(clonedElement->city, "") == 0) strcpy(clonedElement->city, toBeCloned->city);
			}
			else {
				strcpy(clonedElement->name, toBeCloned->name);
				strcpy(clonedElement->hobby, toBeCloned->hobby);
				strcpy(clonedElement->postcode, toBeCloned->postcode);
				strcpy(clonedElement->city, toBeCloned->city);
			}
			getPosition(&pos, "An welcher Stelle soll das Element eingef"ü"gt werden", false, container);

			if (pos >= 1 && pos <= container->elementCount + 1) {
				linkElement(container, clonedElement, pos);

				printf("Das Element wurde erfolgreich dupliziert und an der Stelle %d eingef"ü"gt!", pos);
			}
			else
				printf("Die angegebene Position %d ist ung"ü"ltig!", pos);
		}
		else
			printf("Vorgang abgebrochen!");
	}
	else
		printf("Die angegebene Position %d existiert nicht!", pos);
}

void linkElement(ListContainer* container, ListElement* item, int position) {
	container->current = item;

	if (position == 1) {
		if (firstElementCreated(container)) {
			container->first->previous = container->current;
			container->current->next = container->first;
		}
		container->first = container->current;
	}
	else {
		container->current->next = getElementAt(container, position);
		container->current->previous = getElementAt(container, position - 1);

		if (container->current->previous != NULL) container->current->previous->next = container->current;
		if (container->current->next != NULL) container->current->next->previous = container->current;
	}

	container->elementCount++;

	if (container->autosave) writeFile(DEFAULT_PATH_AUTOSAVE, container);
}

ListElement* fillElement(ListContainer* container) {
	ListElement* helpElement = malloc(sizeof(ListElement));

	printf("Bitte gebe den Namen ein: ");
	gets_s(helpElement->name, INPUT_LENGTH);

	printf("Bitte gebe deren Hobby an: ");
	gets_s(helpElement->hobby, INPUT_LENGTH);

	printf("Bitte gebe die Postleitzahl ein: ");
	gets_s(helpElement->postcode, INPUT_LENGTH_PLZ);

	printf("Bitte gebe die entsprechende Stadt ein: ");
	gets_s(helpElement->city, INPUT_LENGTH);

	helpElement->next = NULL;
	helpElement->previous = NULL;

	return helpElement;
}


/* -----[Remove]----- */

void removeElement(ListElement* toBeDeleted, ListContainer* container) {
	ListElement
		* helpElementNext,
		* helpElementPrevious;

	if (hasNextElement(toBeDeleted) && hasPreviousElement(toBeDeleted)) {
		helpElementNext = toBeDeleted->next;
		helpElementPrevious = toBeDeleted->previous;

		helpElementNext->previous = helpElementPrevious;
		helpElementPrevious->next = helpElementNext;
	}
	else if (hasNextElement(toBeDeleted)) {
		helpElementNext = toBeDeleted->next;
		helpElementNext->previous = 0;

		container->first = helpElementNext;
	}
	else if (hasPreviousElement(toBeDeleted)) {
		helpElementPrevious = toBeDeleted->previous;
		helpElementPrevious->next = 0;

		container->current = helpElementPrevious;
	}
	else {
		container->first = NULL;
		container->current = NULL;
	}

	free(toBeDeleted);

	container->elementCount--;

	if (container->autosave) writeFile(DEFAULT_PATH_AUTOSAVE, container);
}

void removeElementAt(ListContainer* container) {
	int pos, ctr = 0;

	if (getPosition(&pos, "An welcher Stelle soll das Element entfernt werden", true, container)) {
		ListElement* toBeDeleted = getElementAt(container, pos);

		if (yesNoDialog("Soll folgendes Element entfernt werden", toBeDeleted, true)) {
			printf("Entferne Element an der Stelle %d...\n", pos);

			removeElement(toBeDeleted, container);

			printf("Das Element wurde erfolgreich entfernt!");
		}
		else
			printf("Vorgang abgebrochen!");
	}
	else
		printf("Die angegebene Position %d existiert nicht!", pos);
}

void removeElementsInRange(ListContainer* container) {
	int lower, upper;

	if (getPosition(&lower, "Wie lautet der Startpunkt des Bereiches", true, container)) {
		if (getPosition(&upper, "Wie lautet der Endpunkt des Bereiches", true, container)) {
			if (upper > lower) {
				printf("Entferne alle Elemente im Bereich %d-%d...\n", lower, upper);

				for (int i = lower; i <= upper; i++) removeElement(getElementAt(container, lower), container);

				printf("Alle Elemente im Bereich %d-%d wurden entfernt!", lower, upper);
			}
			else
				printf("Der angegebene Bereich ist ung"ü"ltig!");
		}
		else
			printf("Die angegebene Position %d exisitert nicht!", upper);
	}
	else
		printf("Die angegebene Position %d exisitert nicht!", lower);
}

void removeAllElements(ListContainer* container) {
	printf("Entferne alle Elemente der Liste...\n");

	for (int i = 0; i <= container->elementCount + i; i++) removeElement(getElementAt(container, 1), container);

	printf("Alle Elemente wurden erfolgreich entfernt!");
}

void removeIdenticalElements(ListContainer* container) {
	ListElement* compare, * compareWith;

	for (int i = 1; i <= container->elementCount; i++) {
		compare = getElementAt(container, i);
		for (int x = i + 1; x <= container->elementCount; x++) {
			compareWith = getElementAt(container, x);

			if (strcmp(compare->name, compareWith->name) == 0 &&
				strcmp(compare->hobby, compareWith->hobby) == 0 &&
				strcmp(compare->postcode, compareWith->postcode) == 0 &&
				strcmp(compare->city, compareWith->city) == 0) {

				if (yesNoDialog("Folgender Datensatz liegt doppelt vor. Soll das zweite Vorkommen entfernt werden", compareWith, true))
					removeElement(compareWith, container);
			}
		}
	}

	printf("Alle doppelte Datens"ä"tze wurden entfernt!");
}

/* -----[Search]----- */

void searchElement(ListContainer* container) {
	if (!firstElementCreated(container))
		printf("Es befinden sich noch keine Elemente in der Liste!");
	else {
		bool tokenFound = false;

		printf("Die Suche funktioniert wie folgt:\n");
		printf("'PARAM:Wert'\n");
		printf("Korrekte Parameter sind 'NAME', 'PLZ', 'STADT', 'HOBBY'.\n\n");

		char input[INPUT_LENGTH * 2 + 1];
		printf("Nach was m\x94\chtest du suchen? ");
		gets_s(input, INPUT_LENGTH * 2);

		system("cls");

		char* token = strtok(input, ",:");

		for (int i = 0; token[i]; i++) token[i] = toupper(token[i]);

		while (token != NULL) {
			if (strcmp(token, "NAME") == 0 || strcmp(token, "PLZ") == 0 || strcmp(token, "STADT") == 0 || strcmp(token, "HOBBY") == 0) {
				tokenFound = true;
				char* value = strtok(NULL, ",:");

				if (value != NULL) {
					printf("Es wird nach '%s' gesucht...\n", value);
					searchFor(token, value, container);

					printf("\nDie Suche nach '%s' ist abgeschlossen!\n", value);
				}
			}

			token = strtok(NULL, ",:");
		}

		if (!tokenFound) printf("Es konnte kein Parameter gefunden werden!");
	}
}
void searchFor(char* token, char* value, ListContainer* container) {
	container->current = container->first;
	int pos = 1;
	bool entryFound;

	char toSearch[INPUT_LENGTH + 1];
	strcpy(toSearch, value);
	if (!container->search_caseSensitive) for (int i = 0; toSearch[i]; i++) toSearch[i] = tolower(toSearch[i]);

	while (container->current != NULL) {
		entryFound = false;

		char name[INPUT_LENGTH + 1];
		strcpy(name, container->current->name);
		if (!container->search_caseSensitive) for (int i = 0; name[i]; i++) name[i] = tolower(name[i]);

		char hobby[INPUT_LENGTH + 1];
		strcpy(hobby, container->current->hobby);
		if (!container->search_caseSensitive) for (int i = 0; hobby[i]; i++) hobby[i] = tolower(hobby[i]);

		char city[INPUT_LENGTH + 1];
		strcpy(city, container->current->city);
		if (!container->search_caseSensitive) for (int i = 0; city[i]; i++) city[i] = tolower(city[i]);

		char plz[INPUT_LENGTH_PLZ + 1];
		strcpy(plz, container->current->postcode);
		if (!container->search_caseSensitive) for (int i = 0; plz[i]; i++) plz[i] = tolower(plz[i]);


		if (strcmp(token, "NAME") == 0) {
			if (strstr(name, toSearch) != 0) {
				entryFound = true;
			}
		}
		else if (strcmp(token, "PLZ") == 0) {
			if (strstr(plz, toSearch) != 0) {
				entryFound = true;
			}
		}
		else if (strcmp(token, "STADT") == 0) {
			if (strstr(city, toSearch) != 0) {
				entryFound = true;
			}
		}
		else if (strcmp(token, "HOBBY") == 0) {
			if (strstr(hobby, toSearch) != 0) {
				entryFound = true;
			}
		}

		if (entryFound)
			printf(
				"\nPosition %d:\n- Name:  %s\n- PLZ:   %s\n- Stadt: %s\n- Hobby: %s\n",
				pos,
				container->current->name,
				container->current->postcode,
				container->current->city,
				container->current->hobby
			);

		pos++;
		container->current = container->current->next;
	}
}


/* -----[Sort]----- */

void sortName(ListContainer* container) { sort(container, SORT_NAME); }
void sortHobby(ListContainer* container) { sort(container, SORT_HOBBY); }
void sortPLZ(ListContainer* container) { sort(container, SORT_PLZ); }
void sortCity(ListContainer* container) { sort(container, SORT_CITY); }

void sort(ListContainer* container, char* criteria) {
	quicksort(container, 0, container->elementCount, criteria);
	printf("Die Liste wurde erfolgreich nach %s sortiert!", criteria);

	if (container->autosave) writeFile(DEFAULT_PATH_AUTOSAVE, container);
}

void quicksort(ListContainer* container, int left, int right, char* sortType) {
	int index_l, index_r, med;
	index_l = left;
	index_r = right;
	med = (index_l + index_r) / 2;

	bool sortAsc = container->sort_ascending;

	while (index_l < index_r) {
		ListElement
			* elLeft = getElementAt(container, index_l),
			* elRight = getElementAt(container, index_r),
			* elMed = getElementAt(container, med);

		if (strcmp(sortType, SORT_NAME) == 0) {
			while ((strcmp(elLeft->name, elMed->name) < 0 && sortAsc) || (strcmp(elLeft->name, elMed->name) > 0 && !sortAsc)) {
				elLeft = elLeft->next;
				index_l++;
			}

			while ((strcmp(elRight->name, elMed->name) > 0 && sortAsc) || (strcmp(elRight->name, elMed->name) < 0 && !sortAsc)) {
				elRight = elRight->previous;
				index_r--;
			}
		}
		else if (strcmp(sortType, SORT_HOBBY) == 0) {
			while ((strcmp(elLeft->hobby, elMed->hobby) < 0 && sortAsc) || (strcmp(elLeft->hobby, elMed->hobby) > 0 && !sortAsc)) {
				elLeft = elLeft->next;
				index_l++;
			}

			while ((strcmp(elRight->hobby, elMed->hobby) > 0 && sortAsc) || (strcmp(elRight->hobby, elMed->hobby) < 0 && !sortAsc)) {
				elRight = elRight->previous;
				index_r--;
			}
		}
		else if (strcmp(sortType, SORT_PLZ) == 0) {
			while ((strcmp(elLeft->postcode, elMed->postcode) < 0 && sortAsc) || (strcmp(elLeft->postcode, elMed->postcode) > 0 && !sortAsc)) {
				elLeft = elLeft->next;
				index_l++;
			}

			while ((strcmp(elRight->postcode, elMed->postcode) > 0 && sortAsc) || (strcmp(elRight->postcode, elMed->postcode) < 0 && !sortAsc)) {
				elRight = elRight->previous;
				index_r--;
			}
		}
		else if (strcmp(sortType, SORT_CITY) == 0) {
			while ((strcmp(elLeft->city, elMed->city) < 0 && sortAsc) || (strcmp(elLeft->city, elMed->city) > 0 && !sortAsc)) {
				elLeft = elLeft->next;
				index_l++;
			}

			while ((strcmp(elRight->city, elMed->city) > 0 && sortAsc) || (strcmp(elRight->city, elMed->city) < 0 && !sortAsc)) {
				elRight = elRight->previous;
				index_r--;
			}
		}

		if (elLeft != elRight)	swapElements(elLeft, elRight, container);

		if (index_l == med) med = index_r;
		else if (index_r == med) med = index_l;

		if (index_l < med) index_l++;
		if (index_r > med) index_r--;
	}

	if (left < med - 1) quicksort(container, left, med - 1, sortType);
	if (right > med + 1) quicksort(container, med + 1, right, sortType);
}

void swapElements(ListElement* element1, ListElement* element2) {
	char temp[INPUT_LENGTH + 1];

	strcpy(temp, element1->name);
	strcpy(element1->name, element2->name);
	strcpy(element2->name, temp);

	strcpy(temp, element1->hobby);
	strcpy(element1->hobby, element2->hobby);
	strcpy(element2->hobby, temp);

	strcpy(temp, element1->postcode);
	strcpy(element1->postcode, element2->postcode);
	strcpy(element2->postcode, temp);

	strcpy(temp, element1->city);
	strcpy(element1->city, element2->city);
	strcpy(element2->city, temp);
}


/* -----[File Handling]----- */

char* getPath(char* message) {
	char temp[MAX_PATH_LENGTH + 1];

	printf("%s?\n> ", message);
	gets_s(temp, MAX_PATH_LENGTH);

	return _strdup(temp);
}

void saveContent(ListContainer* container) { writeFile(DEFAULT_PATH, container); }

void saveContentTo(ListContainer* container) { writeFile(getPath("In welcher Datei sollen die Eintr"ä"ge gespeichert werden"), container); }

void writeFile(char* path, ListContainer* container) {
	ListElement* helpElement = container->first;
	FILE* file = fopen(path, "w");

	if (file != NULL) {
		if (strcmp(path, DEFAULT_PATH_AUTOSAVE) != 0) printf("Elemente werden in '%s' gespeichert...\n", path);

		while (helpElement != 0) {
			fprintf(file,
				"%s,%s,%s,%s;\n",
				helpElement->name,
				helpElement->postcode,
				helpElement->city,
				helpElement->hobby
			);

			helpElement = helpElement->next;
		}

		fclose(file);

		if (strcmp(path, DEFAULT_PATH_AUTOSAVE) != 0) printf("Erfolgreich gespeichert!");
	}
	else
		printf("Konnte den Pfad %s nicht finden. "Ü"berprüfe ob die evtl. angegebenen Ordner vorliegen!", path);
}


void getContent(ListContainer* container) { readFile(DEFAULT_PATH, container); }

void restoreAutosave(ListContainer* container) {
	if (!firstElementCreated(container)) readFile(DEFAULT_PATH_AUTOSAVE, container);
	else printf("Der Autosave kann nur in eine leere Liste widerhergestellt werden!");
}

void getContentFrom(ListContainer* container) { readFile(getPath("Von welcher Datei soll der Datensatz wiederhergestellt werden"), container); }

bool readFile(char* path, ListContainer* container) {
	FILE* file;
	file = fopen(path, "r");

	if (file != NULL) {
		printf("Elemente werden aus '%s' widerhergestellt...\n", path);
		char temp[INPUT_LENGTH * 3 + 15 + 1];

		fgets(temp, INPUT_LENGTH * 3 + 15, file);
		while (!feof(file)) {
			ListElement* helpElement = malloc(sizeof(ListElement));

			if (strncmp(temp, "***", 3) != 0 && strcmp(temp, "\n") != 0) {
				char* token = strtok(temp, ",;\n");
				int x = 0;
				while (token != NULL) {
					switch (x++) {
					case 0:
						strcpy(helpElement->name, token);
						break;
					case 1:
						strcpy(helpElement->postcode, token);
						break;
					case 2:
						strcpy(helpElement->city, token);
						break;
					case 3:
						strcpy(helpElement->hobby, token);
						break;
					}
					token = strtok(NULL, ",;\n");
				}

				helpElement->next = NULL;
				helpElement->previous = NULL;

				linkElement(container, helpElement, container->elementCount + 1);
			}

			fgets(temp, INPUT_LENGTH * 3 + 15, file);
		}
		fclose(file);

		printf("Der Datensatz wurde erfolgreich aus '%s' widerhergestellt!", path);
	}
	else
		printf("Die Textdatei '%s' konnte nicht gefunden werden!", path);
}


/* -----[Settings]----- */

void switchBool(char* message, bool* value) {
	char info[3] = { 0 };
	*value = !*value;
	if (*value == 0) strcpy(info, "de");

	printf("%s wurde erfolgreich %saktiviert!", message, info);
}

void switchPointersShown(ListContainer* container) { switchBool("Die Zeigerdarstellung", &container->pointersShown); }

void switchAutosave(ListContainer* container) { switchBool("Automatisches Speichern", &container->autosave); }

void switchCaseSensitive(ListContainer* container) { switchBool("Die Beachtung von Gro"ß"- und Kleinschreibung bei der Suche von Elementen", &container->search_caseSensitive); }

void switchSortOrder(ListContainer* container) {
	char info[12] = { 0 };
	container->sort_ascending = !container->sort_ascending;
	if (container->sort_ascending) strcpy(info, "aufsteigend");
	else strcpy(info, "absteigend");

	printf("Die Sortierung erfolgt nun %s!", info);
}

void changeMaxElementsPerPage(ListContainer* container) {
	char key;

	do {
		system("cls");

		printf("Gr"ö""ß"e "ä"ndern mit '+' und '-', beenden mit 'q'!\n\n");
		printf("Aktuell werden maximal %d Elemente pro Seite angezeigt!\n", container->maxElementsPerPage);

		key = _getch();

		if (key == '+' && container->maxElementsPerPage < 500) container->maxElementsPerPage++;
		if (key == '-' && container->maxElementsPerPage > 2) container->maxElementsPerPage--;
	} while (key != 'q' && key != 'Q');
}


/* -----[Utility]----- */

bool getPosition(int* toWrite, char* message, bool performCheck, ListContainer* container) {
	system("cls");

	printf("%s? ", message);
	scanf_s("%d", toWrite);

	clearBuffer();

	return performCheck ? isElementAt(container, *toWrite) : true;
}

ListElement* getElementAt(ListContainer* container, int position) {
	ListElement* helpElement = container->first;

	for (int i = 1; i < position; i++) helpElement = helpElement->next;

	return helpElement;
}

bool firstElementCreated(ListContainer* container) { return container->first != 0; }

bool isElementAt(ListContainer* container, unsigned int position) { return position <= container->elementCount && position > 0; }

bool yesNoDialog(char* message, ListElement* element, bool printInfo) {
	char input;
	do {
		system("cls");

		printf("%s? [y/n]\n", message);
		if (printInfo)
			printf(
				"Name: %s\nStadt: %s %s\nHobby: %s\n",
				element->name,
				element->postcode,
				element->city,
				element->hobby
			);

		putchar('>');
		putchar(' ');

		scanf_s("%c", &input, 1);

		clearBuffer();

		input = tolower(input);
	} while (input != 'y' && input != 'n');

	system("cls");

	return input == 'y';
}

bool hasNextElement(ListElement* element) { return element != NULL ? element->next != NULL : false; }

bool hasPreviousElement(ListElement* element) { return element != NULL ? element->previous != NULL : false; }

void clearBuffer(void) { while (getchar() != '\n'); }
