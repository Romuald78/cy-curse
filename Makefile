#-----------------------------------------
# VARIABLES
#-----------------------------------------
LIB      = GameRGR2
INC_DIR  = inc
SRC_DIR  = src
LIB_DIR  = lib
TEST_EXE = test

#-----------------------------------------
# REBUILD
#-----------------------------------------
all : $(TEST_EXE) run

#-----------------------------------------
# LIB RGR
#-----------------------------------------
$(LIB_DIR)/lib$(LIB).so : $(SRC_DIR)/lib$(LIB).c $(INC_DIR)/lib$(LIB).h
	@echo "Regenerating [$@]..."
	gcc $< -o $@ -shared -fPIC -I$(INC_DIR) -lcurses
	
#-----------------------------------------
# MAIN
#-----------------------------------------
$(TEST_EXE) : $(LIB_DIR)/lib$(LIB).so test.c
	@echo "Regenerating [$@]..."
	gcc test.c -o $@ -I$(INC_DIR) -L$(LIB_DIR) -lcurses -l$(LIB)

#-----------------------------------------
# RUN
#-----------------------------------------
run : $(TEST_EXE)
	LD_LIBRARY_PATH=./$(LIB_DIR) ./$(TEST_EXE)


#-----------------------------------------
# CLEAN / REBUILD
#-----------------------------------------
clean :
	@echo "Removing library..."
	@rm -f $(LIB_DIR)/lib$(LIB).so
	@echo "Removing test executable..."
	@rm -f $(TEST_EXE)
	
rebuild : clean $(TEST_EXE)	

