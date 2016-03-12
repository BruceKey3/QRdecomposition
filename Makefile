.PHONY: clean
SRC_DIR = "src/"
DEPS = $(SRC_DIR)CompTechCoursework.cpp $(SRC_DIR)MatrixUtils.cpp
FLAGS = -std=c++11

coursework:
	g++ $(DEPS) $(FLAGS) -o coursework	

clean:
	rm -rf *.o coursework
  
