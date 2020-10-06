function R = Algebraic(nume, d)
	% Functia care calculeaza vectorul PageRank folosind varianta algebrica de calcul.
	% Intrari: 
	%	-> nume: numele fisierului in care se scrie;
	%	-> d: probabilitatea ca un anumit utilizator sa continue navigarea la o pagina urmatoare.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina.
  fisier = fopen(nume, 'r');
  N = fscanf(fisier, '%f', 1);
  A = zeros(N, N);
  I = eye(N,N);
  for i =1 : N
    linie = fscanf(fisier, '%f', 1);
    vecini = fscanf(fisier, '%f', 1);
    for j = 1 : vecini
      k = fscanf(fisier, '%f', 1);
      A(linie, k)=1;
    endfor
  endfor
  val1 = fscanf(fisier, '%f', 1);
  val2 = fscanf(fisier, '%f', 1);
  %elimin toate 1-urile de pe diagonala principala intrucat in graf2
  %o sa fie un element care va avea link catre el insasi
  diagonal=zeros(N,N);
  diagonal = diag(diag(A));
  A = A - diagonal;
  for i = 1 : N
   L(i)=sum(A(i,:));
  endfor
  fclose(fisier);
  K = zeros(N);
  K = diag(L);
  K = inv(K);
  M = (K * A)';
  X = I - d * M;
  %Notez matricea superior triunghiulara returnata de GS cu Z pentru ca
  % R deja este parametru returnat de functie
  [Q, Z] = GramSchmidt(X);
  inversa=zeros(N,N);
	for i = 1 : N
    xi = SST(Z, Q' * I(:, i));
    %xi precum este prezentat in enunt, va reprezenta coloana cu coloana
    % matricea inversa lui I-d*M
    inversa(:, i) = xi;
  endfor
   coloana = ones(N, 1);
  R=inversa * (1 - d) / N * coloana;
endfunction

    