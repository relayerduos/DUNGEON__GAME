ifdef PROCESSOR_REVISION
  OS      := windows
  OBJ_EXT := obj
  EXE_EXT := .exe
  CLEAN   := *.ilk *.pdb *.suo
else
  OS      := unix
  OBJ_EXT := o
  EXE_EXT :=
  CLEAN   := core
endif

ifeq ($(OS), windows)
  CDEFS += -nologo -EHsc -Zi
  LDEFS += -nologo -debug
else
  CDEFS += -g
  LDEFS += -g
endif

CFLAGS += $(CDEFS)
LFLAGS += $(LDEFS)

OBJS := \
  term.$(OBJ_EXT)     \
  monsters.$(OBJ_EXT) \
  items.$(OBJ_EXT)    \
  player.$(OBJ_EXT)   \
  main.$(OBJ_EXT)

TARGET := DUNGEON$(EXE_EXT)

all : $(TARGET)

$(TARGET) : $(OBJS)
ifeq ($(OS), windows)
	link $(LFLAGS) -out:$@ $^
else
	g++  $(LFLAGS) -o $@ $^
endif

clean :
	rm -f $(TARGET) *.$(OBJ_EXT) $(CLEAN)

%.$(OBJ_EXT) : %.cpp
ifeq ($(OS), windows)
	cl  -c $(CFLAGS) $?
else
	g++ -c $(CFLAGS) $?
endif
