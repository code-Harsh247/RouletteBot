C_FILE = botv1.cpp
EXE = ./a.out
OUTPUT_FILE = output.txt

all:
	rm -f $(OUTPUT_FILE)
	g++ $(C_FILE) 
	$(EXE) > $(OUTPUT_FILE)

clean:
	rm -f $(EXE) $(OUTPUT_FILE)