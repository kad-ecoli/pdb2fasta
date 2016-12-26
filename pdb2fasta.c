#include<stdio.h>
#include<string.h>

char *aa3to1(char* resn){
    // convert three letter code of AA to 1 letter char
    if (strcmp(resn,"ALA")==0) return "A";
    if (strcmp(resn,"VAL")==0) return "V"; 
    if (strcmp(resn,"PHE")==0) return "F";
    if (strcmp(resn,"PRO")==0) return "P";
    if (strcmp(resn,"MET")==0) return "M";
    if (strcmp(resn,"ILE")==0) return "I";
    if (strcmp(resn,"LEU")==0) return "L";
    if (strcmp(resn,"ASP")==0) return "D";
    if (strcmp(resn,"GLU")==0) return "E";
    if (strcmp(resn,"LYS")==0) return "K";
    if (strcmp(resn,"ARG")==0) return "R";
    if (strcmp(resn,"SER")==0) return "S";
    if (strcmp(resn,"THR")==0) return "T";
    if (strcmp(resn,"TYR")==0) return "Y";
    if (strcmp(resn,"HIS")==0) return "H";
    if (strcmp(resn,"CYS")==0) return "C";
    if (strcmp(resn,"ASN")==0) return "N";
    if (strcmp(resn,"GLN")==0) return "Q";
    if (strcmp(resn,"TRP")==0) return "W";
    if (strcmp(resn,"GLY")==0) return "G";
    if (strcmp(resn,"MSE")==0) return "M";
    return "X";
}

char *pdb2fasta(char *pdb_file){
    FILE *fp;
    int j;       // index of character
    char line[80]; // one line in PDB
    char resn[4];  // residue type
    char atom[5];  // atom type
    char altid=' ';  // alternative location identifier
    resn[3]=0;atom[4]=0;
    char chainID=0;   // chain ID of previous chain
    char chainID_new=0; // chain ID of current chain

    char *seqtxt; // maximum PDB sequence is around 3000
    seqtxt=(char *)malloc(1);

    char seqtmp[60]; // current string
    //char seqtxt[300000]; // maximum PDB sequence is around 3000
    //seqtxt[0]=0;     // free

    fp=fopen(pdb_file,"r");
    if (fp==NULL){
        fprintf(stderr,"ERROR! no such file %s\n",pdb_file);
        return "";
    }

    int startindex=0;
    int endindex=strlen(pdb_file);
    for (j=0;j<strlen(pdb_file);j++){
        if (pdb_file[j]=='/'||pdb_file[j]=='\\'){
            startindex=j+1;
            endindex=strlen(pdb_file);
        }
        if (pdb_file[j]=='.' && endindex==strlen(pdb_file)){
            endindex=j;
        }
    }
    char filename[endindex-startindex+1];
    for (j=startindex;j<endindex;j++) filename[j-startindex]=pdb_file[j];
    filename[endindex-startindex]=0;
    // only take first 50 characters of filename
    if (strlen(filename)>=50) filename[50]=0;

    while(fgets(line,80,fp)!=NULL){
        if (strncmp("ENDMDL",line,6)==0) break;
        if (strlen(line)<22 || (strncmp("ATOM  ",line,6) && \
            strncmp("HETATM",line,6))) continue;

        for (j=0;j<4;j++) atom[j]=line[12+j];
        for (j=0;j<3;j++) resn[j]=line[17+j];
        altid=line[16];
        if (strcmp(atom," CA ") || (altid!=' ' && altid!='A') || \
           (strncmp("HETATM",line,6)==0 && strcmp(resn,"MSE"))) continue;
        chainID_new=line[21];
        if (chainID!=chainID_new){ // new chain
            if (chainID){
                sprintf(seqtmp,"\n>%s:%c\n",filename,chainID_new);
            }
            else{
                sprintf(seqtmp,">%s:%c\n",filename,chainID_new);
            }
            seqtxt=(char *)realloc(seqtxt,strlen(seqtxt)+strlen(seqtmp)+1);
            strcat(seqtxt,seqtmp);
            chainID=chainID_new;
        }
        seqtxt=(char *)realloc(seqtxt,strlen(seqtxt)+2);
        strcat(seqtxt,aa3to1(resn));
    }
    fclose(fp);
    strcat(seqtxt,"\n");
    return seqtxt;
}

int main(int argc, char** argv){
    if (argc<2){
        printf("pdb2fasta pdb.pdb > seq.fasta\n");
        printf("    convert PDB file pdb.pdb to FASTA sequence file seq.fasta\n");
        return argc;
    }
    
    int i;
    for (i=1;i<argc;i++){
        char *pdb_file=argv[i];
        printf("%s",pdb2fasta(pdb_file));
    }
}
