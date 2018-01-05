SHELL := /bin/bash
PATH := $(HOME)/bin:$(PATH)
HOW=clangxx5_0_pkg
#HOW=gcc6_20151018
MAIN=main
DIR.root := $(shell dirup_dir_file.pl $(PWD) root.imk)
include $(DIR.root)/root.imk
main.exe.deps:=start
main.exe.deps:=$(main.exe.deps:%=%.o)
main.exe.deps:=$(main.exe.deps:%=$(BUILD_HOW_WHAT.dir)/%)
$(BUILD_HOW_WHAT.dir)/main.exe : $(main.exe.deps)

USE_FORK.which?=1
USE_FORK.0=
USE_FORK.1=-I$(boost.spirit.fork)
VAL_XFORM_IN_RULE?=1
VAL_NO_XFORM_NEEDED?=1
INCS= \
  $(USE_FORK.$(USE_FORK.which)) \
  -I$(boost.root) \
  -I$(nonvartmpl.root) \
  -DBOOST_SPIRIT_X3_EXPERIMENTAL_GET_RHS_NS=0 \
  -DBOOST_SPIRIT_X3_EXPERIMENTAL_GET_RHS_CRTP=0 \
  -DBOOST_SPIRIT_X3_EXPERIMENTAL_ATTR_XFORM_IN_RULE=$(VAL_XFORM_IN_RULE) \
  -DSHOW_PARSE_NO_XFORM_NEEDED=$(VAL_NO_XFORM_NEEDED) \
###

.PHONY: compile show

compare:
	make VAL_NO_XFORM_NEEDED=0 --always-make run
	make VAL_NO_XFORM_NEEDED=1 --always-make run

show:
	@echo "USE_FORk.which=$(USE_FORK.$(USE_FORK.which))"



