function [sol] = hsvHistogram(path_to_image, count_bins)
  sol=zeros(1,3*count_bins);
  poza=imread(path_to_image);
  [m,n,c]=size(poza);
  poza=double(poza);
  suma1=zeros(1,count_bins+1);
  suma2=zeros(1,count_bins+1);
  suma3=zeros(1,count_bins+1);
  for i=1:m
    for j=1:n
      R=poza(i,j,1)/255;
      G=poza(i,j,2)/255;
      B=poza(i,j,3)/255;
      aux=[R,G,B];
      maxim=max(aux);
      minim=min(aux);
      delta=maxim-minim;
      if delta==0
        H=0;
      else
        if maxim==R
          H=60*mod((G-B)/delta,6);
        endif
        if maxim==G
          H=60*((B-R)/delta+2);
        endif
        if maxim==B
          H=60*((R-G)/delta+4);
        endif
      endif
      H=H/360;
      if maxim==0
        S=0;
      else
        S=delta/maxim;
      endif
      V=maxim;
      poza(i,j,1)=H;
      poza(i,j,2)=S;
      poza(i,j,3)=V;
    endfor
     vector1=histc(poza(i,:,1),[0:1.01/count_bins:1.01]);
     suma1=suma1+vector1;
     vector2=histc(poza(i,:,2),[0:1.01/count_bins:1.01]);
     suma2=suma2+vector2;
     vector3=histc(poza(i,:,3),[0:1.01/count_bins:1.01]);
     suma3=suma3+vector3;
    endfor
    suma1(:,count_bins+1)=[];
    suma2(:,count_bins+1)=[];
    suma3(:,count_bins+1)=[];
    sol(1,0*count_bins+1:1*count_bins)=suma1;
    sol(1,1*count_bins+1:2*count_bins)=suma2;
    sol(1,2*count_bins+1:3*count_bins)=suma3;
end