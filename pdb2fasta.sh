#!/bin/bash
if [ -z "$1" ];then
    echo "$(basename $0) pdb.pdb > seq.fasta"
    echo "    convert PDB file pdb.pdb to FASTA sequence file seq.fasta"
    exit
fi

declare -A aa3to1=(
    ['ALA']='A' ['VAL']='V' ['PHE']='F' ['PRO']='P' ['MET']='M'
    ['ILE']='I' ['LEU']='L' ['ASP']='D' ['GLU']='E' ['LYS']='K'
    ['ARG']='R' ['SER']='S' ['THR']='T' ['TYR']='Y' ['HIS']='H'
    ['CYS']='C' ['ASN']='N' ['GLN']='Q' ['TRP']='W' ['GLY']='G'
    ['MSE']='M'
)

IFS=$'\n'       # make newlines the only separator

for pdb_file in $@;do
    filename=`basename $pdb_file`;filename=${filename%%.*}
    chainID_list=""

    pdb_txt=`grep -ohP "(^ATOM\s{2,6}\d{1,5}\s{2}CA\s[\sA]([A-Z]{3})\s[\s\w])|(^HETATM\s{0,4}\d{1,5}\s{2}CA\s[\sA]MSE\s[\s\w])|^ENDMDL" $pdb_file`
    for line in $pdb_txt;do
	if [ "$line" = "ENDMDL" ];then
	    break
	fi
        resn=${line:17:3}
	chainID=${line:21:1}

	if [[ ! "$chainID_list" =~ $chainID ]];then
	    if [ ! -z "$chainID_list" ];then 
	        printf "\n"
	    fi
	    printf ">$filename:$chainID\n"
	    chainID_list="$chainID_list$chainID"
	fi

	printf ${aa3to1[$resn]}

    done
    printf "\n"
done
