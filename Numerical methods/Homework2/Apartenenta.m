function y = Apartenenta(x, val1, val2)
	% Functia care primeste ca parametrii x, val1, val2 si care calculeaza valoarea functiei membru in punctul x.
	% Stim ca 0 <= x <= 1 
	%a*val2+b=1
  %a*val1+b=0
  %Pentru a fi continua functia trebuie ca in capetele intervalelor
  %valorile functiei sa fie egala cu ramura invecinata
  a = 1 / (val2 - val1);
  b=(-1) * val1 / (val2 - val1);
  if x < val1
    y = 0;
  elseif x >= val1 && x <= val2
      y = a * x + b;
  elseif x > val2
      y =1;
    endif
endfunction
  
      