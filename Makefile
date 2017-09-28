CFLAGS=-Wall -Werror -Wextra -Wno-unused-function -mwindows -march=native
#  Order matters.  Shlwapi must appear before shell32 or else we get a runtime
#  error for StrCpyNW.
LFLAGS=-nostartfiles -lkernel32 -luser32 -lShlwapi -lshell32 -lwininet -lole32 -lwindowscodecs

DEBUG_CFLAGS=-g -D_DEBUG

gcc:
	mkdir -p debug/gcc
	cp --update TwitchNotify.txt debug/gcc/TwitchNotify.txt
	windres TwitchNotify.rc debug/gcc/TwitchNotify.res.o
	gcc TwitchNotify.c debug/gcc/TwitchNotify.res.o -o debug/gcc/TwitchNotify.exe $(CFLAGS) $(DEBUG_CFLAGS) $(LFLAGS)

.PHONY: clean
clean:
	rm -f -r debug/