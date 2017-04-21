const char* docstring=""
"pdb2fasta pdb.pdb > seq.fasta\n"
"    convert PDB file pdb.pdb to sequence FASTA file seq.fasta\n"
;

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

/* convert three letter code of AA to 1 letter char */
inline char aa3to1(string resn){
    if (resn=="ALA") return 'A';
    if (resn=="VAL") return 'V'; 
    if (resn=="PHE") return 'F';
    if (resn=="PRO") return 'P';
    if (resn=="MET") return 'M';
    if (resn=="ILE") return 'I';
    if (resn=="LEU") return 'L';
    if (resn=="ASP") return 'D';
    if (resn=="GLU") return 'E';
    if (resn=="LYS") return 'K';
    if (resn=="ARG") return 'R';
    if (resn=="SER") return 'S';
    if (resn=="THR") return 'T';
    if (resn=="TYR") return 'Y';
    if (resn=="HIS") return 'H';
    if (resn=="CYS") return 'C';
    if (resn=="ASN") return 'N';
    if (resn=="GLN") return 'Q';
    if (resn=="TRP") return 'W';
    if (resn=="GLY") return 'G';
    if (resn=="MSE") return 'M';
    return 'X';
}

/* extract the basename from a file path */
string basename_no_ext(const char *pdb_file,bool suppress_ext=true)
{
    string filename;
    int startindex=0;
    int endindex=strlen(pdb_file);
    for (int i=0;i<strlen(pdb_file);i++){
        if (pdb_file[i]=='/'||pdb_file[i]=='\\'){
            startindex=i+1;
            endindex=strlen(pdb_file);
        }
        if (pdb_file[i]=='.' && endindex==strlen(pdb_file) && suppress_ext){
            endindex=i;
        }
    }
    for (int i=startindex;i<endindex;i++) filename+=pdb_file[i];
    return filename;
}

/* convert PDB file to fasta text */
string pdb2fasta(const char *pdb_file)
{
    stringstream seqtxt;
    string line,atom_name,resn;
    char altloc,chain,prev_chain=0;

    string filename=basename_no_ext(pdb_file);
    ifstream fp(pdb_file, ios::in);
    while (fp.good())
    {
        getline(fp,line);
        if (line.substr(0,3)=="END") break;
        if (line.length()<54) continue;

        altloc=line[16];
        atom_name=line.substr(12,4);
        resn=line.substr(17,3);
        chain=line[21];
        if ((altloc!=' ' && altloc!='A') || atom_name!=" CA " ||
           !(line.substr(0,6)=="ATOM  " || (line.substr(0,6)=="HETATM" && 
            resn=="MSE"))) continue;

        if (prev_chain!=chain)
        {
            if (prev_chain!=0) seqtxt<<endl;
            seqtxt<<'>'<<filename<<':'<<chain<<endl;
            prev_chain=chain;
        }
        seqtxt<<aa3to1(resn);
    }
    fp.close();
    seqtxt<<endl;
    return seqtxt.str();
}

int main(int argc, char** argv){
    if (argc<2){
        cout<<docstring;
        return 0;
    }

    for (int i=1;i<argc;i++)
    {
        char *pdb_file=argv[i];
        cout<<pdb2fasta(pdb_file);
    }
    return 0;
}
