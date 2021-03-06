#	makefile created by Artem Suttar
#	Based on the file "A.Zimmermann, Allzweck-Makefile" from lectures Operating systems

#BEFORE-ALL CREATE obj-FOLDER,
$(shell if not exist .\obj mkdir obj)


# Linker, create pa.exe file
pa.exe : obj/main.o obj/thread.o obj/lib.o obj/inifini.o obj/datalistlib.o
	@echo Linking ...
	gcc -o pa.exe obj/main.o obj/thread.o obj/lib.o obj/inifini.o obj/datalistlib.o

# Compiler, create objects files
obj/main.o: main.c interface.h
	@echo Compiling main.o...
	gcc -c -o obj/main.o main.c

obj/thread.o: thread.c interface.h
	@echo Compiling thread.o...
	gcc -c -o obj/thread.o thread.c

obj/lib.o: lib.c interface.h
	@echo Compiling lib.o...
	gcc -c -o obj/lib.o lib.c

obj/inifini.o: inifini.c interface.h
	@echo Compiling lib.o...
	gcc -c -o obj/inifini.o inifini.c

obj/datalistlib.o: datalistlib.c interface.h
	@echo Compiling lib.o...
	gcc -c -o obj/datalistlib.o datalistlib.c


run:
	cls
	pa.exe

clean:
	@echo Deleting obj- A- B-folder, obj- and exe-files and all Test-files...
	if exist .\obj rmdir /s /q obj
	if exist .\A rmdir /s /q A
	if exist .\B rmdir /s /q B
	if exist *.exe del *.exe
	if exist *.txt del *.txt
	if exist *.o del *.o

FILES_TO_ZIP := main.c,thread.c,lib.c,interface.h,makefile,.gitignore, inifini.c, datalistlib.c

zip:
	@powershell Compress-Archive $(FILES_TO_ZIP) -Force ./Suttar.zip
#  =============  EOF  =============
