CC := gcc
MAKE := make
INCDIR := -I ./include -I ./stdproc
CFLAGS := -Wall $(INCDIR)

StdprocDir := stdproc
export ProcObjs := argcheck.o boolean_proc.o char_proc.o equal_proc.o list_proc.o \
                   number_proc.o pair_proc.o string_proc.o symbol_proc.o \
                   vector_proc.o output_proc.o control_proc.o
StdprocObjs := $(addprefix $(StdprocDir)/, $(ProcObjs))
StdprocFiles :=  $(subst .o,.c,$(StdprocObjs))

Objects := main.o memory.o atom.o control.o boolean.o character.o number.o symbol.o \
          mstring.o vector.o list.o equal_predicate.o output.o read_parse.o stack.o \
          procedure.o environment.o eval.o driver_loop.o garbage_collection.o

#####################################################
##rules
#####################################################

CSchemer: $(Objects) $(StdprocObjs)
	$(CC) $(CFLAGS) -o CSchemer $(Objects) $(StdprocObjs)

IncCommonObjs := $(filter-out main.o environment.o, $(Objects))
$(IncCommonObjs):$(subst .o,.c,$(IncCommonObjs)) include/common.h
	$(CC) -c $(CFLAGS) $(subst .o,.c,$@)

main.o: main.c include/driver_loop.h
	$(CC) -c $(CFLAGS) main.c

environment.o: environment.c include/common.h stdproc/stdproc.h
	$(CC) -c $(CFLAGS) environment.c

$(StdprocObjs): $(StdprocFiles)
	$(MAKE) -C $(StdprocDir)

clean:
	-rm -rf CSchemer $(Objects) 
	cd $(StdprocDir) ; make clean