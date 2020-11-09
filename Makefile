COMPILER  = clang++
CFLAGS    = -std=c++14 -g -O3 -Wall -Wno-missing-field-initializers -isysroot/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS = -O3
else
  LDFLAGS = -O3
endif
LIBS      = /usr/local/Cellar/ftgl/2.1.3-rc5/lib/libftgl.dylib /usr/local/lib/libfreetype.dylib  /usr/local/lib/libSDL2.dylib /usr/local/lib/libSDL2_mixer.dylib /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib
INCLUDE   = -I/usr/local/include/freetype2/ -I/usr/local/include/
TARGET    = ./a.out
SRCDIR    = ./src
ifeq "$(strip $(SRCDIR))" ""
  SRCDIR  = .
endif
SOURCES   = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR    = ./obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR  = .
endif
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
