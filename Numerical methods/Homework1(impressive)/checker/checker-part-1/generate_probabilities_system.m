function [A, b] = generate_probabilities_system(rows)
  numar=0;
  gauss=0;
  for i=1:rows
    numar=numar+i;
  endfor
  A=zeros(numar,numar);
  M=zeros(rows+2,rows+2);
  M(1,:)=0;
  M(:,1)=0;
  M(rows+2,:)=-2;
  M(:,rows+2)=-2;
  M(2,2)=1;
  for nivel=1:rows
    gauss=gauss+nivel;
    aux=gauss-nivel;
    crescator=2;
    for lungime=nivel:-1:1
      aux=aux+1;
      M(lungime+1,crescator)=aux;
      crescator=crescator+1;
    endfor
  endfor
  for i=3:rows+1
    for j=rows+1:-1:(rows+1-i+3)
      M(i,j)=-1;
    endfor
  endfor
  A(1,1)=4;
  A(1,2:3)=-1;
  for i=2:rows+1
    for j=2:rows+1
      if M(i,j)>1
        nr0=0;
        nr=0;
        if M(i+1,j)==-1
          nr=1;
        endif
        if M(i,j+1)==-1
          nr=1;
        endif
        if (M(i,j+1)==0 || M(i+1,j)==0 || M(i-1,j+1)==0 || M(i+1,j-1)==0 
          || M(i,j-1)==0 || M(i-1,j)==0)
          nr0=1;
        endif
        if M(i+1,j)>0
          A(M(i,j),M(i+1,j))=-1;
          nr=nr+1;
        endif
        if M(i-1,j)>0
          A(M(i,j),M(i-1,j))=-1;
          nr=nr+1;
        endif
        if M(i,j+1)>0
          A(M(i,j),M(i,j+1))=-1;
          nr=nr+1;
        endif
        if M(i,j-1)>0
          A(M(i,j),M(i,j-1))=-1;
          nr=nr+1;
        endif
        if M(i-1,j+1)>0
          A(M(i,j),M(i-1,j+1))=-1;
          nr=nr+1;
        endif
        if M(i+1,j-1)>0
          A(M(i,j),M(i+1,j-1))=-1;
          nr=nr+1;
        endif
        A(M(i,j),M(i,j))=nr+nr0;
        endif
      endfor
    endfor
    b=zeros(numar,1);
    b(numar-rows+1:numar,1)=1;
endfunction