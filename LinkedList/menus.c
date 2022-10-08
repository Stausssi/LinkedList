#include "linkedList.h"


/* -----[Main Menu]----- */

void mainMenu(ListContainer* container) {
	struct MenuItem menu[] = {
		{"Datensatz anzeigen",			'1',	(void*)&submenu_show,		container},
		{"Element hinzuf"ü"gen",		'2',	(void*)&submenu_add,		container},
		{"Element entfernen",			'3',	(void*)&submenu_remove,		container},
		{"Element suchen",				'4',	(void*)&searchElement,		container},
		{"Elemente sortieren",			'5',	(void*)&submenu_sort,		container},
		{"BLANK",						NULL,	(void*)NULL},
		{"Datensatz speichern",			'a',	(void*)&submenu_save,		container},
		{"Datensatz wiederherstellen",	'b',	(void*)&submenu_get,		container},
		{"BLANK",						NULL,	(void*)NULL},
		{"Einstellungen",				'e',	(void*)&submenu_settings,	container},
		{"BLANK",						NULL,	(void*)NULL},
		{"Beenden",						'q',	(void*)&exit}
	};

	struct MenuPage pages[] = {
		{menu, sizeof(menu) / sizeof(struct MenuItem), "Verkettete Liste", true, true, &SOLID}
	};
	show_menu(pages, sizeof(pages) / sizeof(struct MenuPage), true);
}


/* -----[Show]----- */

void submenu_show(ListContainer* container) {
	if (firstElementCreated(container)) {
		struct MenuItem show[] = {
			{"Liste anzeigen",				'1',	(void*)&showList,		container},
			{"Seiten"ü"bersicht anzeigen",	'2',	(void*)&showPage,		container},
			{"BLANK",						NULL,	(void*)NULL},
			{"Zur"ü"ck",					'b',	(void*)&mainMenu,		container}
		};
		struct MenuPage page[] = {
				{show, sizeof(show) / sizeof(struct MenuItem), "Datensatz anzeigen", false, false, &NO_BORDER}
		};
		show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
	}
	else
		printf("Die Liste ist aktuell leer!");
}


/* -----[Add]----- */

void submenu_add(ListContainer* container) {
	struct MenuItem add[] = {
		{"Einzelnes Element hinzuf"ü"gen",					'1',	(void*)&addElement,				container},
		{"An einer bestimmten Stelle einf"ü"gen",			'2',	(void*)&addElementAt,			container},
		{"Bestimmte Anzahl an Elementen hinzuf"ü"gen",		'3',	(void*)&addMultipleElements,	container},
		{"Existierenden Datensatz kopieren und bearbeiten",	'4',	(void*)&cloneElement,			container},
		{"BLANK",											NULL,	(void*)NULL},
		{"Zur"ü"ck",										'b',	(void*)&mainMenu,				container}
	};
	struct MenuPage page[] = {
			{add, sizeof(add) / sizeof(struct MenuItem), "Element hinzuf" ü "gen", false, false, &NO_BORDER}
	};
	show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
};


/* -----[Remove]----- */

void submenu_remove(ListContainer* container) {
	if (firstElementCreated(container)) {
		struct MenuItem remove[] = {
		{"Element an beliebiger Stelle entfernen",	'1',	(void*)&removeElementAt,			container},
		{"Bestimmten Bereich entfernen",			'2',	(void*)&removeElementsInRange,		container},
		{"Gesamte Liste l"ö"schen",					'3',	(void*)&removeAllElements,			container},
		{"Doppelte Datens"ä"tze entfernen",			'4',	(void*)&removeIdenticalElements,	container},
		{"BLANK",									NULL,	(void*)NULL},
		{"Zur"ü"ck",								'b',	(void*)&mainMenu,					container}
		};
		struct MenuPage page[] = {
			{remove, sizeof(remove) / sizeof(struct MenuItem), "Element entfernen", false, false, &NO_BORDER}
		};
		show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
	}
	else
		printf("Es gibt keine Elemente zum Entfernen!");
}


/* -----[Sort]----- */

void submenu_sort(ListContainer* container) {
	if (firstElementCreated(container)) {
		struct MenuItem sort[] = {
			{"Nach Namen sortieren",			'1',	(void*)&sortName,	container},
			{"Nach Hobby sortieren",			'2',	(void*)&sortHobby,	container},
			{"Nach Postleitzahl sortieren",		'3',	(void*)&sortPLZ,	container},
			{"Nach Stadt sortieren",			'4',	(void*)&sortCity,	container},
			{"BLANK",							NULL,	(void*)NULL},
			{"Zur"ü"ck",						'b',	(void*)&mainMenu,	container}
		};
		struct MenuPage page[] = {
			{sort, sizeof(sort) / sizeof(struct MenuItem), "Datensatz sortieren", false, false, &NO_BORDER}
		};
		show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
	}
	else
		printf("Es gibt keine Elemente zum Sortieren!");
}


/* -----[File Handling]----- */

void submenu_save(ListContainer* container) {
	if (firstElementCreated(container)) {
		struct MenuItem save[] = {
			{"Standarddatei verwenden",				'1',	(void*)&saveContent,	container},
			{"Benutzerdefinierte Datei verwenden",	'2',	(void*)&saveContentTo,	container},
			{"BLANK",								NULL,	(void*)NULL},
			{"Zur"ü"ck",							'b',	(void*)&mainMenu,		container}
		};
		struct MenuPage page[] = {
			{save, sizeof(save) / sizeof(struct MenuItem), "Datensatz speichern", false, false, &NO_BORDER}
		};
		show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
	}
	else
		printf("Es exisiteren keine Elemente zum Speichern!");
}

void submenu_get(ListContainer* container) {
	struct MenuItem get[] = {
		{"Standarddatei verwenden",				'1',	(void*)&getContent,			container},
		{"Autosave wiederherstellen",			'2',	(void*)&restoreAutosave,	container},
		{"Benutzerdefinierte Datei verwenden",	'3',	(void*)&getContentFrom,		container},
		{"BLANK",								NULL,	(void*)NULL},
		{"Zur"ü"ck",							'b',	(void*)&mainMenu,			container}
	};
	struct MenuPage page[] = {
		{get, sizeof(get) / sizeof(struct MenuItem), "Datensatz wiedererstellen", false, false, &NO_BORDER}
	};
	show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
}


/* -----[Settings]----- */

void submenu_settings(ListContainer* container) {
	struct MenuItem settings[] = {
		{"Zeigerdarstellung umstellen",				'1',	(void*)&switchPointersShown,		container},
		{"Automatisches Speichern umstellen",		'2',	(void*)&switchAutosave,				container},
		{"Gro"ß"- und Kleinschreibung beachten",	'3',	(void*)&switchCaseSensitive,		container},
		{"Sortierrichtung "ä"ndern",				'4',	(void*)&switchSortOrder,			container},
		{"Maximale Elemente pro Seite "ä"ndern",	'5',	(void*)&changeMaxElementsPerPage,	container},
		{"BLANK",									NULL,	(void*)NULL},
		{"Zur"ü"ck",								'b',	(void*)&mainMenu,					container}
	};
	struct MenuPage page[] = {
		{settings, sizeof(settings) / sizeof(struct MenuItem), "Einstellungen", false, false, &NO_BORDER}
	};
	show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
}
