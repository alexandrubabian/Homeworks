function R = Iterative(nume, d, eps)
	% Functia care calculeaza matricea R folosind algoritmul iterativ.
	% Intrari:
	%	-> nume: numele fisierului din care se citeste;
	%	-> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
	%	-> eps: eruarea care apare in algoritm.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina. 
  fisier = fopen(nume,'r');
  N = fscanf(fisier, '%f', 1);
  A = zeros(N,N);
  L = zeros(1, N);
  for i =1 : N
    linie = fscanf(fisier, '%f', 1);
    vecini = fscanf(fisier, '%f', 1);
    for j = 1 : vecini
      k = fscanf(fisier, '%f', 1);
      A(linie, k)=1;
    endfor
  endfor
  diagonal=zeros(N,N);
  diagonal = diag(diag(A));
  A = A - diagonal;
  for i = 1 : N
   L(i)=sum(A(i,:));
  endfor
  val1 = fscanf(fisier, '%f', 1);
  val2 = fscanf(fisier, '%f', 1);
  fclose(fisier);
  K = zeros(N);
  K = diag(L);
  K = inv(K);
  M = (K * A)';
  aux = zeros(N, 1);
  R = zeros(N, 1);
  coloana = ones(N, 1);
  aux(1:N, 1) = 1 / N;
  %aplic formula din wikipedia pana cand eroarea o sa fie mai mica
  %decat toleranta acceptata,eps
  R = d * M * aux +((1 - d) / N) * coloana;
  while (norm(R - aux) >= eps)
    aux = R;
    R = d * M * aux +((1 - d) / N) * coloana;
    %urmatoarea conditie nu este necesara intrucat acelasi pas il fact
    %si dupa terminarea whileului, dar in octave-ul meu imi apare
    %ca function se incheie cu endwhile in loc de endfunctionn
    %asa ca las in ambele moduri sa fiu sigur
    if norm(R-aux)<eps
      R=aux;
    endif
  endwhile
  R=aux;
  endfunction