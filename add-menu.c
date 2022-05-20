#include <stdio.h>
#include "add-menu.h"
#include "string-list.h"
//#include "builtin.h"
#include <string.h>

int find_unique(const char *choice, struct menu_stuff *menu_stuff)
{
	struct menu_item *menu_item;
	struct string_list_item *string_list_item;
	int i, len, found = 0;

	len = strlen(choice);
	switch (menu_stuff->type) {
	default:
		// Bad type of menu_stuff when parse choice
		return ERROR_BAD_MENU;
	case MENU_STUFF_TYPE_MENU_ITEM:

		menu_item = (struct menu_item *)menu_stuff->stuff;
		for (i = 0; i < menu_stuff->nr; i++, menu_item++) {
			if (len == 1 && *choice == menu_item->hotkey) {
				found = i + 1;
				break;
			}
			if (!strncasecmp(choice, menu_item->title, len)) {
				if (found) {
					if (len == 1) {
						/* continue for hotkey matching */
						found = -1;
					} else {
						found = 0;
						break;
					}
				} else {
					found = i + 1;
				}
			}
		}
		break;
	case MENU_STUFF_TYPE_STRING_LIST:
		string_list_item = ((struct string_list *)menu_stuff->stuff)->items;
		for (i = 0; i < menu_stuff->nr; i++, string_list_item++) {
			if (!strncasecmp(choice, string_list_item->string, len)) {
				if (found) {
					found = 0;
					break;
				}
				found = i + 1;
			}
		}
		break;
	}
	return found;
}