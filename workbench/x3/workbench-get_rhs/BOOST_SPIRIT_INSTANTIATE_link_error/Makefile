SHELL := /bin/bash
PATH := $(HOME)/bin:$(PATH)
HOW=clangxx5_0_pkg
#HOW=gcc6_20151018
MAIN=main
DIR.root := $(shell dirup_dir_file.pl $(PWD) root.imk)
main.exe.deps=start
include $(DIR.root)/root.imk

USE_SPIRIT.which?=0
USE_SPIRIT.0=
USE_SPIRIT.1=-I$(boost.spirit.devel)
USE_SPIRIT.2=-I$(boost.spirit.fork)
VAL_XFORM_IN_RULE?=1
VAL_NO_XFORM_NEEDED?=0
INCS= \
  $(USE_SPIRIT.$(USE_SPIRIT.which)) \
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
	@echo "USE_FORk.which=$(USE_SPIRIT.$(USE_SPIRIT.which))"
	@echo "main.exe.deps=$($(MAIN).exe.deps)"
	@echo "SRC.deps=$(SRC.deps)"



