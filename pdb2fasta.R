#!/usr/bin/env Rscript
args=commandArgs(TRUE)
if (length(args)<1){
    cat("pdb2fasta.py pdb.pdb > seq.fasta\n")
    cat("    convert PDB file pdb.pdb to FASTA sequence file seq.fasta\n")
}

aa3to1=c("A","V","F","P","M","I","L","D","E","K",
     "R","S","T","Y","H","C","N","Q","W","G","M")
names(aa3to1)=c("ALA","VAL","PHE","PRO","MET","ILE","LEU","ASP","GLU","LYS",
          "ARG","SER","THR","TYR","HIS","CYS","ASN","GLN","TRP","GLY","MSE")

for (pdb_file in args){
    chain_prev="" # chain ID of previous chain
    filename=tools::file_path_sans_ext(basename(pdb_file))
    fp=file(pdb_file,'r')
    while(1){
        line=readLines(fp,1)
        if (length(line)<1||substr(line,1,6)=="ENDMDL"){break}
        chainID=substr(line,22,22)
        resn=substr(line,18,20)
        atom=substr(line,13,16)
	altid=substr(line,17,17)
        if ((substr(line,1,6)!="ATOM  " && substr(line,1,6)!="HETATM")
           ||atom!=" CA "||is.element(resn,names(aa3to1))==FALSE
	   ||(altid!=" " && altid!="A")){next} # continue
        if (chainID !=chain_prev){
            if (chain_prev==""){
                cat(paste(">",filename,":",chainID,"\n",sep=""))
            }else{
                cat(paste("\n>",filename,":",chainID,"\n",sep=""))
            }
            chain_prev=chainID
        }
        cat(aa3to1[resn])
    }
    close(fp)
    cat("\n")
}
