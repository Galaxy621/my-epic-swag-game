COMPILER = g++
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lopengl32 -lgdi32
INCLUDE_PATH = -I lib/ -I include/
OBJECT_FILES = *.o
TARGET = game.exe

all: $(TARGET)

$(TARGET): object
	$(COMPILER) -DUNICODE -o out/$@ $(OBJECT_FILES) $(LINKER_FLAGS)

assets:
	Copy-Item -Path "assets" -Destination "out/"

object:
	$(COMPILER) -DUNICODE -c $(COMPILER_FLAGS) $(INCLUDE_PATH) src/*.cpp src/*.c src/win32/*.cpp

optimize:
	$(COMPILER) -DUNICODE -O3 -c $(COMPILER_FLAGS) $(INCLUDE_PATH) src/*.cpp src/*.c src/win32/*.cpp

clean:
	del $(OBJECT_FILES)

remove:
	del $(OBJECT_FILES)
	del out/$(TARGET)

run:
	./$(TARGET)