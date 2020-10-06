function [G_J, c_J] = Jacobi_factorization(A, b)
  N=diag(diag(A));
  P=N-A;
  inv_N=inv(N);
  G_inv=inv_N*P;
  c_j=inv_N*b;
endfunction
