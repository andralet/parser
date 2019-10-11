OUT=parser
SRC=main.cpp
CC=g++
DB=gdb
JUDGE_O=-O2
JUDGE_FLAGS=-Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wpointer-arith -Wtype-limits -Wempty-body -Wno-logical-op -Wmissing-field-initializers -Wno-unused-result -std=c++11 -lm
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
