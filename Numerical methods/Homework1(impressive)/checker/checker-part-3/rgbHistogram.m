function [sol] = rgbHistogram(path_to_image, count_bins)
  sol=zeros(1,3*count_bins);
  poza=imread(path_to_image);
  [m,n,c]=size(poza);
  for i=1:3
    suma=zeros(1,count_bins+1);
    for j=1:m
      vector=histc(poza(j,:,i),[0:256/count_bins:256]);
      suma=suma+vector;
    endfor
    suma(:,count_bins+1)=[];
    sol(1,(i-1)*count_bins+1:i*count_bins)=suma;
end