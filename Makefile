EXEC=lab_02
EXEC_T=t_$(EXEC)
OBJ=main.o lab_02.o 
OBJ_T=lab_02.o test.o 
LIBS  = -lgsl -lm 
CPPFLAGS = -Wall -g

main: $(OBJ)
	@echo "Сборка бинарника"
	c++ $(CPPFLAGS) $(OBJ) $(LIBS) -o $(EXEC) 
lab_02.o: lab_02.c++ lab_02.h
	@echo "Компиляция модуля lab_02"
	c++ $(CPPFLAGS) -c lab_02.c++
main.o: main.c++
	@echo "Компиляция main.o"
	c++ $(CPPFLAGS) -c main.c++
clean:
	rm -f ./*.o $(EXEC) $(EXEC_T)
test.o: test.c++
	@echo "Компиляция UNIT теста"
	c++ $(CPPFLAGS) -c test.c++
test: $(OBJ_T) 
	c++ $(CPPFLAGS) $(OBJ_T) $(LIBS) -o $(EXEC_T)
run:$(EXEC)
	./$(EXEC)

