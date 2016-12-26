CC=gcc
CFLAGS=-O2 
LDFLAGS=-static

pdb2fasta: pdb2fasta.c
	${CC} ${CFLAGS} pdb2fasta.c -o pdb2fasta ${LDFLAGS}

clean:
	rm pdb2fasta
