function [x] = SST (A,b)
  [n,n]=size(A);
  x=zeros(n,1);
  if A(n,n)~=0
    x(n)=b(n)/A(n,n);
  endif
  for i=(n-1):-1:1
    suma=A(i,(i+1):n)*x((i+1):n,1);
    x(i)=(b(i)-suma)/A(i,i);
  endfor
endfunction
