CXXFLAGS := -g -Wall -Wextra
LDLIBS := -lboost_system -lboost_thread -lpthread

main: main.cpp

clean:
	$(RM) main