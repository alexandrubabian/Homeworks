function [G_J, c_J] = Jacobi_factorization(A, b)
   [linii,coloane]=size(A);
  G_J=zeros(linii,linii);
  c_J=zeros(linii,1);
  N=diag(diag(A));
  P=N-A;
  inv_N=inv(N);
  G_J=inv_N*P;
  c_J=inv_N*b;
endfunction
