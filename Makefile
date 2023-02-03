SYSTEMC_ARCH=linux64
LIB_DIRS=$(SYSTEMC_HOME)/lib-$(SYSTEMC_ARCH)

# Include directories
INCLUDE_DIRS = -I. -I$(SYSTEMC_HOME)/include 

# header files used. for dependency checking
HEADERS = fir.h tb.h

# source files used. for dependency checking
SOURCES = main.cc fir.cc tb.cc

DEPENDENCIES = \
	Makefile \
	$(HEADERS) \
	$(SOURCES)

LIBS= -lsystemc -lstdc++ -lm

BIN= main

all: $(BIN)
	./$(BIN)
	# @make cmp_result

$(BIN): $(DEPENDENCIES)
	gcc -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L. -L$(LIB_DIRS) $(LIBS) -Wl,-rpath=$(LIB_DIRS)

clean:
	rm -f $(BIN) *.dat

# The cmp_result target compares the simulation results with the golden result
GOLD_DIR = ./golden
GOLD_FILE = $(GOLD_DIR)/ref_output.dat

cmp_result:
	@echo "************************************"
	@if diff -w ./golden/ref_output.dat ./output.dat ; then \
		ehco "SIMULATION PASSED"; \
	else \
		ehco "SIMULATION FAILED"; \
	fi
	@echo "************************************"


.PHONY: clean

# run:
# 	g++ -L. -L$(SYSTEMC_HOME)/lib-linux64 -Wl,-rpath=$(SYSTEMC_HOME)/lib-linux64 -o main main.cc fir.cc tb.cc -lsystemc -lm
#  ./main
