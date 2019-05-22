CC := g++ -std=c++11
INCLUDE_DIR = Include
SRC_DIR = Source
BUILD_DIR = Build
EXECUTABLE_FILE = out

OBJECTS = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/Client.o \
	$(BUILD_DIR)/Publisher.o \
	$(BUILD_DIR)/Film.o \
	$(BUILD_DIR)/UserInterface.o \
	$(BUILD_DIR)/UTflix.o \
	$(BUILD_DIR)/Exception.o \

ClientSensitivityList = \
	$(INCLUDE_DIR)/Client.h \
	$(INCLUDE_DIR)/Exception.h \
	$(INCLUDE_DIR)/Film.h \
	$(SRC_DIR)/Client.cpp \

PublisherSensitivityList = \
	$(INCLUDE_DIR)/Publisher.h \
	$(INCLUDE_DIR)/Client.h \
	$(INCLUDE_DIR)/Exception.h \
	$(SRC_DIR)/Publisher.cpp \

FilmSensitivityList = \
	$(INCLUDE_DIR)/Film.h \
	$(INCLUDE_DIR)/Exception.h \
	$(SRC_DIR)/Film.cpp \

ExceptionSensitivityList = \
	$(INCLUDE_DIR)/Exception.h \
	$(SRC_DIR)/Exception.cpp \

UserInterfaceSensitivityList = \
	$(INCLUDE_DIR)/UserInterface.h \
	$(INCLUDE_DIR)/UTflix.h \
	$(INCLUDE_DIR)/Exception.h \
	$(SRC_DIR)/UserInterface.cpp \

UTflixSensitivityList = \
	$(INCLUDE_DIR)/UTflix.h \
	$(INCLUDE_DIR)/Client.h \
	$(INCLUDE_DIR)/Publisher.h \
	$(INCLUDE_DIR)/Film.h \
	$(INCLUDE_DIR)/Exception.h \
	$(SRC_DIR)/UserInterface.cpp \

MainSensitivityList = \
	$(INCLUDE_DIR)/UserInterface.h \
	$(INCLUDE_DIR)/UTflix.h \
	$(INCLUDE_DIR)/Exception.h \
	$(SRC_DIR)/main.cpp \

all : $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXECUTABLE_FILE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/main.o : $(MainSensitivityList)
	$(CC) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Client.o : $(ClientSensitivityList)
	$(CC) -c $(SRC_DIR)/Client.cpp -o $(BUILD_DIR)/Client.o

$(BUILD_DIR)/Publisher.o : $(PublisherSensitivityList)
	$(CC) -c $(SRC_DIR)/Publisher.cpp -o $(BUILD_DIR)/Publisher.o

$(BUILD_DIR)/Film.o : $(FilmSensitivityList)
	$(CC) -c $(SRC_DIR)/Film.cpp -o $(BUILD_DIR)/Film.o

$(BUILD_DIR)/UserInterface.o : $(UserInterfaceSensitivityList)
	$(CC) -c $(SRC_DIR)/UserInterface.cpp -o $(BUILD_DIR)/UserInterface.o

$(BUILD_DIR)/UTflix.o : $(UTflixSensitivityList)
	$(CC) -c $(SRC_DIR)/UTflix.cpp -o $(BUILD_DIR)/UTflix.o

$(BUILD_DIR)/Exception.o : $(ExceptionSensitivityList)
	$(CC) -c $(SRC_DIR)/Exception.cpp -o $(BUILD_DIR)/Exception.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
