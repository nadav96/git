#define MENU_OPTS_SINGLETON		01
#define MENU_OPTS_IMMEDIATE		02
#define MENU_OPTS_LIST_ONLY		04

#define ERROR_BAD_MENU		-1

struct menu_opts {
	const char *header;
	const char *prompt;
	int flags;
};

#define MENU_RETURN_NO_LOOP		10

struct menu_item {
	char hotkey;
	const char *title;
	int selected;
	int (*fn)(void);
};

enum menu_stuff_type {
	MENU_STUFF_TYPE_STRING_LIST = 1,
	MENU_STUFF_TYPE_MENU_ITEM
};

struct menu_stuff {
	enum menu_stuff_type type;
	int nr;
	void *stuff;
};

int find_unique(const char *choice, struct menu_stuff *menu_stuff);

int run(void);