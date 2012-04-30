CC := gcc
INCDIR := -I ../include
CFLAGS := -Wall $(INCDIR)

all: $(ProcObjs)

$(ProcObjs): $(subst .o,.c,$(ProcObjs)) ../include/common.h argcheck.h
	$(CC) -c $(CFLAGS) $(subst .o,.c,$@)

clean:
	rm -rf $(ProcObjs)