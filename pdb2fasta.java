import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.*;
import java.io.*;

public class pdb2fasta 
{
    public static void main(String[] args)
    {
        if (args.length==0)
        {
            System.out.println("java pdb2fasta pdb.pdb > seq.fasta\n" + 
            "    convert PDB file pdb.pdb to FASTA sequence seq.fasta\n");
            return;
        }
        String[] aa3 = {"ALA", "VAL", "PHE", "PRO", "MET", "ILE", "LEU",
                        "ASP", "GLU", "LYS", "ARG", "SER", "THR", "TYR",
                        "HIS", "CYS", "ASN", "GLN", "TRP", "GLY", "MSE"};
        String[] aa1 = {"A", "V", "F", "P", "M", "I", "L", "D", "E",
                        "K", "R", "S", "T", "Y", "H", "C", "N", "Q",
                        "W", "G", "M"};
        Map<String, String> aa3to1=new HashMap();
        for(int i = 0; i < aa3.length; i++) aa3to1.put(aa3[i], aa1[i]);
        Pattern ca_pattern=Pattern.compile(
            "^ATOM\\s{2,6}\\d{1,5}\\s{2}CA\\s[\\sA]([A-Z]{3})\\s([\\s\\w])"+ 
            "|^HETATM\\s{0,4}\\d{1,5}\\s{2}CA\\s[\\sA](MSE)\\s([\\s\\w])");

        for (int arg=0;arg<args.length;arg++)
        {
            File pdb_file = new File(args[arg]);
            String filename=pdb_file.getName();
            if (filename.indexOf(".")>-1)
                filename=filename.substring(0,filename.indexOf("."));
            Map chain_dict = new HashMap();
            List chain_list = new ArrayList();
            String line;
            String resn;
            String chain;
            try
            {
                BufferedReader fp = new BufferedReader(new FileReader(pdb_file));
                while( (line = fp.readLine()) != null &&
                    !line.startsWith("ENDMDL")) 
                {
                    Matcher match_list = ca_pattern.matcher(line);
                    if(match_list.find())
                    {
                        resn = match_list.group(1);
                        chain = match_list.group(2);
                        if (chain_dict.containsKey(chain))
                        {
                            chain_dict.put(chain, chain_dict.get(chain)+
                                                  aa3to1.get(resn));
                        }
                        else
                        {
                            chain_dict.put(chain, aa3to1.get(resn));
                            chain_list.add(chain);
                        }
                    }
                }
                fp.close();
           }
           catch(FileNotFoundException ex) {ex.printStackTrace();}
           catch(IOException ex) {ex.printStackTrace();}
           for (int c = 0; c < chain_list.size(); c++)
               System.out.println(">"+filename+":"+chain_list.get(c)+"\n"+
                   chain_dict.get(chain_list.get(c)));
        }
    }
}
