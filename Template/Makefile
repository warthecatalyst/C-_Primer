objects = main.o

main : $(objects)
	g++ -std=c++17 -o main.exe $(objects)

$(objects) : global.h MyVec.hpp MyList.hpp

.PHONY : clean
clean : 
	-rm main.exe *.o