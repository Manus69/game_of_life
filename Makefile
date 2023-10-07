target := a.out
cc := gcc
flags_base := -std=c2x -Wall -Wextra -fsanitize=address
flags_dbg := $(flags_base) -g
flags_release := $(flags_base) -O3 -flto
flags_link := -lSDL2
flags := $(flags_dbg)

obj_dir := obj/
src_dir := src/
src := $(wildcard $(src_dir)/*.c)
src_no_dir := $(notdir $(src))
obj_no_dir := $(src_no_dir:.c=.o)
obj := $(addprefix $(obj_dir),$(obj_no_dir))

all: build

dir:
	mkdir -p $(obj_dir)

test:
	echo $(obj)

$(target): $(obj)
	$(cc) $(flags) $(obj) -o $(target) $(flags_link)

clean:
	rm -f $(obj) $(target)

build: dir $(target)

release: flags := $(flags_release)
release: clean $(obj) build

dbg: flags := $(flags_dbg)
dbg: clean $(obj) $(target)

$(obj_dir)%.o : $(src_dir)%.c
	$(cc) -c $(flags) $< -o $@ $(flags_link)