function [x] = Jacobi_sparse(G_values, G_colind, G_rowptr, c, tol)
  prev_x=zeros(length(c));
  x=zeros(length(c));
  while 1
    y=csr_multiplication(G_values,G_colind,G_rowptr,prev_x);
    x=y+c;
    err=norm(x-prev_x);
    if (err<tol)
      return;
    endif
    prev_x=x;
  endwhile
endfunction