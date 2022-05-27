AddressBook:AddressBook.c gui_void.o
	gcc -o AddressBook AddressBook.c gui_void.o
gui_void.o:gui_void.c
	gcc -c gui_void.c
clean:
	rm -f *.o