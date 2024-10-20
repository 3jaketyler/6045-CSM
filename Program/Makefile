CXX = g++ 

CXXFLAGS = -Wall -g   

EXEC = cfm 

SRCS = cfm.cpp person.cpp searchNSort.cpp 

HEADERS = person.h searchNSort.h 

OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) 

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJS) $(EXEC)
else
	rm -f $(OBJS) $(EXEC)
endif


