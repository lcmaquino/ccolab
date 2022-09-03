# Variable Definitions
CC = g++
FLAGS = -lm --std=c++17
SRC = ../src
EXTENSION = cc
EXEC_CCO = cco
EXEC_FOREST_INVASION = forest-invasion
EXEC_COAT = coat
BASE_FILES = $(SRC)/progress/*.$(EXTENSION) $(SRC)/geometry/*.$(EXTENSION) $(SRC)/domain/*.$(EXTENSION) $(SRC)/tree/*.$(EXTENSION) $(SRC)/cco/*.$(EXTENSION) $(SRC)/morphometry/*.$(EXTENSION)
FILES_CCO = $(EXEC_CCO).$(EXTENSION) $(BASE_FILES)
FILES_FOREST_INVASION = $(EXEC_FOREST_INVASION).$(EXTENSION) $(BASE_FILES) $(SRC)/forest/*.$(EXTENSION)
FILES_COAT = $(EXEC_COAT).$(EXTENSION) $(BASE_FILES) $(SRC)/forest/*.$(EXTENSION)
INCLUDES = -I $(SRC) -I $(SRC)/progress -I $(SRC)/forest -I $(SRC)/cco -I $(SRC)/cco/interface -I $(SRC)/tree -I $(SRC)/domain -I $(SRC)/morphometry -I $(SRC)/voronoi

# Compiling rules.
all: cco forest-invasion coat

# Compiling cco rule.
cco:
	@echo "Compiling $(EXEC_CCO)..."
	$(CC) -o $(EXEC_CCO) $(FILES_CCO) $(INCLUDES) $(FLAGS)
	@echo ""

# Compiling forest-invasion rule.
forest-invasion:
	@echo "Compiling $(EXEC_FOREST_INVASION)..."
	$(CC) -o $(EXEC_FOREST_INVASION) $(FILES_FOREST_INVASION) $(INCLUDES) $(FLAGS)
	@echo ""

# Compiling coat rule.
coat:
	@echo "Compiling $(EXEC_COAT)..."
	$(CC) -o $(EXEC_COAT) $(FILES_COAT) $(INCLUDES) $(FLAGS)
	@echo ""

# Clean binaries
clean:
	@rm -f $(EXEC_CCO)
	@rm -f $(EXEC_FOREST_INVASION)
	@rm -f $(EXEC_COAT)
	@echo "All binaries cleaned up!"