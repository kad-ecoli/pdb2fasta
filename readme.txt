This is a collection of implemention of the "pdb2fasta" program for
converting PDB format protein structure to FASTA format amino acid sequence.
On Mac or Linux, you can run the programs with:

    pdb2fasta pdb.pdb > seq.fasta

, where "pdb.pdb" is the input PDB file pdb.pdb to FASTA sequence file seq.fasta.

The following implements are available: Python2 (.py), Perl5 (.pl), 
Matlab (.m), R (.R), C (.c), C++ (.cpp), BASH (.sh), Java (.java).

These programs have consistent behavior over the following scenarios: 
[1] If atoms have alternative locations (e.g. 3b2c), only those atom with 
    alternative location identifier ' ' (space) or 'A' will be considered.
[2] If a protein contain non-standard amino acids (e.g. 1a62), "MSE" residues
    will be converted to "MET", while other non-standard amino acids are
    ignored.
[3] If a residue have insetion code (e.g. 2p83), it will still be considered.
[4] If a PDB contains multi-models (e.g. 2m9l), only the first model will be
    considered.
