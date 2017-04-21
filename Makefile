CC=g++
CFLAGS=-O3
LDFLAGS=-static

pdb2fasta: pdb2fasta.cpp
	${CC} ${CFLAGS} pdb2fasta.cpp -o pdb2fasta ${LDFLAGS}

clean:
	rm pdb2fasta
