#define USE_THE_INDEX_COMPATIBILITY_MACROS

#include <stdio.h>
#include "stashh.h"
#include "builtin.h"
#include "cache.h"
#include "config.h"
#include "dir.h"
#include "parse-options.h"
#include "string-list.h"
#include "quote.h"
#include "column.h"
#include "color.h"
#include "pathspec.h"
#include "help.h"
#include "prompt.h"
#include "add-menu.h"

static int sample_run(void) {
	printf("other \n");
	return 1;
}

static int a1(void) {
	printf("a11! \n");
	return 1;
}

static int a2(void) {
	printf("a22! \n");
	return 1;
}

static int a3(void) {
	printf("a33! \n");
	return 1;
}

static void prompt_help_cmd(int singleton)
{
	clean_print_color(CLEAN_COLOR_HELP);
	printf(singleton ?
		  _("Prompt help:\n"
		    "1          - select a numbered item\n"
		    "foo        - select item based on unique prefix\n"
		    "           - (empty) select nothing\n") :
		  _("Prompt help:\n"
		    "1          - select a single item\n"
		    "3-5        - select a range of items\n"
		    "2-3,6-9    - select multiple ranges\n"
		    "foo        - select item based on unique prefix\n"
		    "-...       - unselect specified items\n"
		    "*          - choose all items\n"
		    "           - (empty) finish selecting\n"));
	clean_print_color(CLEAN_COLOR_RESET);
}

int cmd_stashh(int argc, const char **argv, const char *prefix) {
int i = 0;
	int* result;


	struct menu_opts menu_opts;
	struct menu_stuff menu_stuff;
	struct menu_item menus[] = {
		{'c', "clean",			0, a1},
		{'f', "filter by pattern",	0, a2},
		{'s', "select by numbers",	0, a3},
		{'a', "ask each",		0, sample_run},
		{'q', "quit",			0, sample_run},
		{'h', "help",			0, sample_run},
	};
	int *chosen;

	menu_opts.header = N_("*** Commands ***");
	menu_opts.prompt = N_("What now");
	menu_opts.flags = MENU_OPTS_SINGLETON;

	menu_stuff.type = MENU_STUFF_TYPE_MENU_ITEM;
	menu_stuff.stuff = menus;
	menu_stuff.nr = sizeof(menus) / sizeof(struct menu_item);

	clean_print_color(CLEAN_COLOR_HEADER);

	ALLOC_ARRAY(chosen, menu_stuff.nr);
	/* set chosen as uninitialized */
	for (i = 0; i < menu_stuff.nr; i++)
		chosen[i] = -1;

	result = list_and_choose(&menu_opts, &menu_stuff, prompt_help_cmd);

	if (*result != EOF) {
		int ret;
		ret = menus[*result].fn();
		printf("the result is %d\n", ret);
	}

	return 0;
}