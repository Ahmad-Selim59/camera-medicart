# Makefile for Camera Control Test Application
# Requires MinGW-w64 or TDM-GCC

CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
LDFLAGS = CameraCtrl.lib -lstrmiids -lws2_32 -lole32 -loleaut32 -ladvapi32

TARGET = CameraControlTest.exe
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Windows commands
RM = del /Q /F
COPY = copy /Y
MKDIR = mkdir

all: $(TARGET)
	@echo.
	@echo Build successful!
	@echo Make sure CameraCtrl.dll is in the same directory as $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@if exist CameraCtrl.dll ($(COPY) CameraCtrl.dll . >nul 2>&1)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJECTS) 2>nul
	-$(RM) $(TARGET) 2>nul
	@echo Clean complete

.PHONY: all clean

