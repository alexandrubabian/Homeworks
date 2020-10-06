function [centroids] = clustering_pc(points, NC)
  [N,D]=size(points);
  centroids=zeros(NC,D);
  auxcentroids=zeros(NC,D);
  cluster=zeros(NC,N);
  impartire=idivide(N,NC,"floor");
  for i=1:NC
    suma=zeros(D,1);
    for j=0:impartire-1
      cluster(i,j+1)=i+j*NC;
    endfor
    for j=1:D
      for k=1:impartire
        suma(j,1)=suma(j,1)+points(cluster(i,k),j);
      endfor
        centroids(i,j)=suma(j,1)/impartire;
    endfor
  endfor
    suma=0;
 %centroids=zeros(NC,D);
 while norm(auxcentroids-centroids)>1e-6
   numarator=zeros(NC,1);
   auxcentroids=centroids;
   centroids=zeros(NC,D);
   cluster=zeros(NC,N);
   for i=1:N
     mini=100;
     indice=1;
     for j=1:NC
      % V=points(i,:)-auxcentroids(j,:);
       %nor=sqrt(V*V');
       nor=norm(points(i,:)-auxcentroids(j,:));
       if mini > nor
         mini=nor;
         indice=j;
       endif
     endfor
     numarator(indice,1)=numarator(indice,1)+1;
     cluster(indice,numarator(indice,1))=i;
    % numarator(indice,1)=numarator(indice,1)+1;
   endfor
   for i=1:NC
     suma=zeros(D,1);
     for j=1:D
      for k=1:numarator(i,1)
        suma(j,1)=suma(j,1)+points(cluster(i,k),j);
      endfor
      if numarator(i,1)~=0
        centroids(i,j)=suma(j,1)/numarator(i,1);
        endif
    endfor
  endfor
 endwhile
endfunction
