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

int cmd_stashh(int argc, const char **argv, const char *prefix) {
	struct strbuf choice = STRBUF_INIT;
	int eof = 0;

	//if (git_read_line_interactively(&choice) == EOF) {
	//	eof = 1;
	//	return 1;
	//}

	printf("hello world %d %s\n", eof, choice.buf);
	
	run();

	return 0;
}