BSTINCL = /home/lerd/boost_1_57_0/install-dir/include
BSTLIB = /home/lerd/boost_1_57_0/install-dir/lib

all:
	g++ main.cpp head.h head.cpp sha1.h sha1.cpp -lboost_filesystem -lboost_property_tree -I$(BSTINCL) -L$(BSTLIB) -std=c++11 -o search_engine_lerd