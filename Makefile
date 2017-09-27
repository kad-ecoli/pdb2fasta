CC=g++
JC=javac
CFLAGS=-O3
LDFLAGS=-static

all: pdb2fasta pdb2fasta.class

pdb2fasta: pdb2fasta.cpp
	${CC} ${CFLAGS} pdb2fasta.cpp -o pdb2fasta ${LDFLAGS}

pdb2fasta.class: pdb2fasta.java
	${JC} pdb2fasta.java

clean:
	rm pdb2fasta
