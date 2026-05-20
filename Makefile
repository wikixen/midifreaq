CFLAGS = -lm -lportsf
FILE = main


default:
	gcc $(CFLAGS) -o build/$(FILE) src/$(FILE).c