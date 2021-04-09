# Compiler
CC=gcc

#Names
PROJECT_NAME=producer_consumer_problem
SOURCE_PATH=./src/
# Headers
HEADERS=$(wildcard $(SOURCE_PATH)*.h)
LIBRARIES = -lpthread -lrt
# C Files
FILES=$(wildcard $(SOURCE_PATH)*.c)

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(HEADERS) $(FILES)
	$(CC) -o $(PROJECT_NAME) $(HEADERS) $(FILES) $(LIBRARIES)

debug: $(HEADERS) $(FILES)
	$(CC) -o $(PROJECT_NAME) $(HEADERS) $(FILES) $(LIBRARIES) -DDEBUG

delay: $(HEADERS) $(FILES)
	$(CC) -o $(PROJECT_NAME) $(HEADERS) $(FILES) $(LIBRARIES) -DDEBUG -DDELAY=1


clean:
	rm $(PROJECT_NAME)