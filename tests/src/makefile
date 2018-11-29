SRC=../../src
BIN=../bin
OBJ=../obj
CPP=g++
CPPFLAGS=-std=c++2a -Wall -Werror -g3
CPPLIBS=-lgtest -lgtest_main -lpthread
.PHONY: dirs clean
all: dirs $(BIN)/ut_syntaxTree $(BIN)/ut_nodeIterator $(BIN)/ut_parser $(BIN)/ut_scanner $(BIN)/ut_token

$(BIN)/ut_syntaxTree: $(OBJ)/ut_syntaxTree.o $(OBJ)/syntax_tree.o $(OBJ)/node_iterator.o
	$(CPP) $(CPPFLAGS) -o $(BIN)/ut_syntaxTree $(OBJ)/ut_syntaxTree.o $(OBJ)/syntax_tree.o $(OBJ)/node_iterator.o $(CPPLIBS)
$(OBJ)/ut_syntaxTree.o: ut_syntaxTree.cpp
	$(CPP) $(CPPFLAGS) -o $(OBJ)/ut_syntaxTree.o -c ut_syntaxTree.cpp
$(OBJ)/syntax_tree.o: $(SRC)/syntax_tree.h $(SRC)/syntax_tree.cpp
	$(CPP) $(CPPFLAGS) -o $(OBJ)/syntax_tree.o -c $(SRC)/syntax_tree.cpp

$(BIN)/ut_nodeIterator: $(OBJ)/ut_nodeIterator.o $(OBJ)/syntax_tree.o $(OBJ)/node_iterator.o
	$(CPP) $(CPPFLAGS) -o $(BIN)/ut_nodeIterator $(OBJ)/syntax_tree.o $(OBJ)/ut_nodeIterator.o $(OBJ)/node_iterator.o $(CPPLIBS)
$(OBJ)/ut_nodeIterator.o: ut_nodeIterator.cpp $(OBJ)/node_iterator.o
	$(CPP) $(CPPFLAGS) -o $(OBJ)/ut_nodeIterator.o -c ut_nodeIterator.cpp
$(OBJ)/node_iterator.o: $(SRC)/node_iterator.h $(SRC)/node_iterator.cpp
	$(CPP) $(CPPFLAGS) -o $(OBJ)/node_iterator.o -c $(SRC)/node_iterator.cpp

$(BIN)/ut_token: $(OBJ)/ut_token.o $(OBJ)/token.o
	$(CPP) $(CPPFLAGS) -o $(BIN)/ut_token $(OBJ)/ut_token.o $(OBJ)/token.o $(CPPLIBS)
$(OBJ)/ut_token.o: ut_token.cpp $(OBJ)/token.o
	$(CPP) $(CPPFLAGS) -o $(OBJ)/ut_token.o -c ut_token.cpp
$(OBJ)/token.o: $(SRC)/token.h $(SRC)/token.cpp
	$(CPP) $(CPPFLAGS) -o $(OBJ)/token.o -c $(SRC)/token.cpp

$(BIN)/ut_scanner: $(OBJ)/ut_scanner.o $(OBJ)/scanner.o $(OBJ)/token.o
	$(CPP) $(CPPFLAGS) -o $(BIN)/ut_scanner $(OBJ)/ut_scanner.o $(OBJ)/scanner.o $(OBJ)/token.o $(CPPLIBS)
$(OBJ)/ut_scanner.o: ut_scanner.cpp $(OBJ)/scanner.o
	$(CPP) $(CPPFLAGS) -o $(OBJ)/ut_scanner.o -c ut_scanner.cpp
$(OBJ)/scanner.o: $(SRC)/scanner.h $(SRC)/scanner.cpp
	$(CPP) $(CPPFLAGS) -o $(OBJ)/scanner.o -c $(SRC)/scanner.cpp

$(BIN)/ut_parser: $(OBJ)/ut_parser.o $(OBJ)/parser.o
	$(CPP) $(CPPFLAGS) -o $(BIN)/ut_parser $(OBJ)/ut_parser.o $(OBJ)/parser.o $(CPPLIBS)
$(OBJ)/ut_parser.o: ut_parser.cpp $(OBJ)/parser.o
	$(CPP) $(CPPFLAGS) -o $(OBJ)/ut_parser.o -c ut_parser.cpp
$(OBJ)/parser.o: $(SRC)/parser.h $(SRC)/parser.cpp
	$(CPP) $(CPPFLAGS) -o $(OBJ)/parser.o -c $(SRC)/parser.cpp


dirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)
clean:
	rm -rf $(BIN) $(OBJ)

