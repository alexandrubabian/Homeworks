function [Q,R] = GramSchmidt (A)
  %GramSchmidt varianta optimizata
  n = size(A);
  Q = zeros(n ,n);
  R = zeros(n, n);
  for j = 1:n
    R(j, j) = norm(A(:, j));
    Q(:, j) = A(:, j) / R(j, j);
    R(j, j + 1 : n) = Q(:, j)' * A(:, j + 1 : n);
    A(:, j + 1 : n) = A(:, j + 1 : n) - Q(:, j) * R(j, j + 1 :n);
  endfor
endfunction
