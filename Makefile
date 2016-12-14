EXEC=LO41

SOURCES=main.c Factory.c Conveyor.c Supervisor.c \
		Retrait.c Supplier.c Type.c Product.c \
		Table.c Machine.c Display.c

REPORT=Report.tex

EXEC_DIR=bin
OBJ_DIR=obj

OBJECTS=${SOURCES:%.c=$(OBJ_DIR)/%.o}

IDIR=-I /usr/include/

LDIR=-L /usr/lib -L /usr/local/lib -L /usr/lib64 -L /usr/lib/x86_64-linux-gnu

CFLAGS=-Wall -Wextra -O3 -g3 -Wno-unused-variable -Wno-unused-parameter
LFLAGS=-lpthread

CC=gcc

all: clean init $(EXEC_DIR)/$(EXEC)

$(EXEC_DIR)/$(EXEC): $(OBJECTS)
	@echo "\n=======LINKING=======\n"
	$(CC) -o $@ $^ $(LDIR) $(LFLAGS)

$(OBJ_DIR)/%.o: %.c
	@echo "\n=======COMPILING $@======="
	$(CC) -o $@ -c $< $(IDIR) $(CFLAGS)

init:
	@mkdir -p "$(EXEC_DIR)"
	@mkdir -p "$(OBJ_DIR)"

clean:
	@rm -rf "$(OBJ_DIR)"

report:
	pdflatex $(REPORT);
	evince $(REPORT:%.tex=%.pdf)
