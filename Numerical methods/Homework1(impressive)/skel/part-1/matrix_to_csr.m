function [values, colind, rowptr] = matrix_to_csr(A)
  contor=0;
  for i=1:rows(A)
    ok=0;
    for j=1:columns(A)
      if A(i,j) ~= 0
        contor=contor+1;
        values(contor)=A(i,j);
        colind(contor)=j;
        if ok==0
          rowptr(i)=contor;
          ok=1;
        endif
      endif
    endfor
  endfor   
  rowptr(rows(A)+1)=contor+1;
endfunction