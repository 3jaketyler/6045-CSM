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
	rm -f $(OBJS) $(EXEC)

