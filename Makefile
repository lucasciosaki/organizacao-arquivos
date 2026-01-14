all:
	gcc -g -o programaTrab *.c funcionalidades/*.c arquivo_de_dados/*.c arquivo_de_indice/*.c

run:
	./programaTrab

clean:
	rm -f programaTrab *.o funcionalidades/*.o arquivo_de_dados/*.o arquivo_de_indice/*.o
