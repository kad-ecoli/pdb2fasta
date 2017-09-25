#!/usr/bin/env python
import sys,os
import re

if len(sys.argv)<2:
    sys.stdout.write('''pdb2fasta.py pdb.pdb > seq.fasta
    convert PDB file pdb.pdb to FASTA sequence file seq.fasta
''')

aa3to1={
   'ALA':'A', 'VAL':'V', 'PHE':'F', 'PRO':'P', 'MET':'M',
   'ILE':'I', 'LEU':'L', 'ASP':'D', 'GLU':'E', 'LYS':'K',
   'ARG':'R', 'SER':'S', 'THR':'T', 'TYR':'Y', 'HIS':'H',
   'CYS':'C', 'ASN':'N', 'GLN':'Q', 'TRP':'W', 'GLY':'G',
   'MSE':'M',
}

ca_pattern=re.compile("^ATOM\s{2,6}\d{1,5}\s{2}CA\s[\sA]([A-Z]{3})\s([\s\w])|^HETATM\s{0,4}\d{1,5}\s{2}CA\s[\sA](MSE)\s([\s\w])")
for pdb_file in sys.argv[1:]:
    filename=os.path.basename(pdb_file).split('.')[0]
    chain_dict=dict()
    chain_list=[]

    fp=open(pdb_file,'rU')
    for line in fp.read().splitlines():
        if line.startswith("ENDMDL"):
            break
        match_list=ca_pattern.findall(line)
        if match_list:
            resn=match_list[0][0]+match_list[0][2]
            chain=match_list[0][1]+match_list[0][3]
            if chain in chain_dict:
                chain_dict[chain]+=aa3to1[resn]
            else:
                chain_dict[chain]=aa3to1[resn]
                chain_list.append(chain)
    fp.close()

    for chain in chain_list:
        sys.stdout.write('>%s:%s\n%s\n'%(filename,chain,chain_dict[chain]))
