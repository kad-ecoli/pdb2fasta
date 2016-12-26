function txt=pdb2fasta(infile)
% pdb2fasta pdb.pdb
%    convert PDB file pdb.pdb to FASTA sequence file seq.fasta
aa1='AVFPMILDEKRSTYHCNQWGM';
aa3={'ALA','VAL','PHE','PRO','MET','ILE','LEU','ASP','GLU','LYS','ARG','SER','THR','TYR','HIS','CYS','ASN','GLN','TRP','GLY','MSE'};
txt='';

[directory,filename,extension]=fileparts(infile);

fp=fopen(infile);
line='';
chain_list='';
while ischar(line)
    line = fgetl(fp);
    if strcmp(line(1:min(length(line),6)),'ENDMDL')
        break
    end
    if length(line)<22
        continue
    end
    resn=line(18:20);
    chainID=line(22);
    atom=line(13:16);
    altid=line(17:17);
    if (~strcmp(line(1:6),'ATOM  ') && ~strcmp(line(1:6),'HETATM')) || ...
       (~strcmp(atom,' CA ')) || (~strcmp(altid,' ') && ~strcmp(altid,'A'))
        continue
    end
    for ii=1:length(aa3)
        if resn==aa3{ii}
            if isempty(chain_list)
                chain_list=chainID;
                txt=horzcat(txt,'>',filename,':',chainID,'\n',aa1(ii));
            elseif ~strcmp(chain_list(end),chainID)
                chain_list=horzcat(chain_list,chainID);
                txt=horzcat(txt,'\n>',filename,':',chainID,'\n',aa1(ii));
            else
                txt=horzcat(txt,aa1(ii));
            end
        end
    end%ii
    %display(line)
end % while
fclose(fp);
txt=horzcat(txt,'\n');
fprintf(txt);
end
