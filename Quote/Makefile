objects = main.o Quote.o Bk_Quote.o Basket.o

main : $(objects)
	g++ -o main.exe $(objects)

$(objects) : global.h

.PHONY : clean
clean : 
	-rm main.exe *.o