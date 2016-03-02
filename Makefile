.PHONY: clean
SRC_DIR = "src/"
DEPS = $(SRC_DIR)CompTechCoursework.cpp $(SRC_DIR)MatrixUtils.cpp
coursework:
	g++ $(DEPS) -o coursework	

clean:
	rm -rf *.o coursework
  