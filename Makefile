OUT=parser
SRC=main.c
CC=gcc
DB=gdb
JUDGE_O=-O2
JUDGE_FLAGS=-Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wpointer-arith -Wtype-limits -Wempty-body -Wno-logical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -Wno-unused-result -std=gnu99 -lm
MY_FLAGS=-Wextra

default: $(SRC)
	$(CC) $(SRC) -o $(OUT) $(JUDGE_O) $(JUDGE_FLAGS) $(MY_FLAGS)

run: default
	./$(OUT)

build-debug: $(SRC)
	# building for debug with judge flags except optimization level
	$(CC) $(SRC) -o $(OUT) $(JUDGE_FLAGS) $(MY_FLAGS) -g

debug: build-debug
	$(DB) ./$(OUT)
