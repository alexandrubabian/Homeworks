function [R1 R2] = PageRank(nume, d, eps)
	% Calculeaza indicii PageRank pentru cele 3 cerinte
	% Scrie fisierul de iesire nume.out 
  fisier = fopen(nume,'r');
  N = fscanf(fisier, '%f', 1);
  for i = 1 : N
   x = fscanf(fisier, '%f', 1);
   x = fscanf(fisier, '%f', 1);
   for j = 1 : x
     y = fscanf(fisier, '%f', 1);
   endfor
 endfor
  val1 = fscanf(fisier, '%f', 1);
  val2 = fscanf(fisier, '%f', 1);
  fclose(fisier);
  out = strcat(nume, '.out');
  fisierout = fopen(out, 'w');
  fprintf(fisierout, '%.f \n\n', N);
  R1 = Iterative(nume, d, eps)
  fprintf(fisierout, '%.6f\n',R1);
  fprintf(fisierout,'\n');
  R2 = Algebraic(nume,d)
  fprintf(fisierout, '%.6f\n',R2);
  fprintf(fisierout,'\n');
  %al doilea parametru returnat de functia sort, vector, reprezinta
  %indicele de linie al elementelor care au fost sortate
  [PR, vector] = sort(R2, 'descend');
 for i = 1 : N
   y = Apartenenta(PR(i), val1, val2);
   fprintf(fisierout, '%.f %.f %.6f\n', i, vector(i), y);
 endfor
 fclose(fisierout);
endfunction