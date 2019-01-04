export TOP		:= $(shell pwd)
export CC 		:= gcc
export STRIP 	:= strip
export DEFS	:=
export LDFLAG 	:= -luini
export CFLAGS 	:=-Os -Wall -Werror $(DEFS)
export INCLUDE := -I $(TOP)/common

