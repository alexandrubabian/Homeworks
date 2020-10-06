function [cost] = compute_cost_pc(points, centroids)
  [N,D]=size(points);
  [NC,d]=size(centroids);
  cost=0;
  norma=0
  for i=1:N
    minim=1000;
    for j=1:NC
      nor=norm(points(i,:)-centroids(j,:));
      if minim>nor
        minim=nor;
      endif
      
    endfor
    cost=cost+minim;
  endfor
endfunction

