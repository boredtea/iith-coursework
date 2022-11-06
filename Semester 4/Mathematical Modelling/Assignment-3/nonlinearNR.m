clc
%  function matrix
f_1 = @(x_1, x_2, x_3)(x_1 ^ 2 + x_2 - x_3 - 1);
f_2 = @(x_1, x_2, x_3)(x_1 + x_2 - 3);
f_3 = @(x_1, x_2, x_3)(x_1 ^ 4 + 3 * x_2 + x_3 ^ 2 - 35);

% initial guess
x = [1; 0; 3];

tol = 1e-6;
flag = 0;
for i = 1:20
    J = jacobian(x);
    f = [feval(f_1, x(1), x(2), x(3)), feval(f_2, x(1), x(2), x(3)), feval(f_3, x(1), x(2), x(3))];
    x_old = x;
    x = compute(f, J, x_old);
    error = abs(x - x_old) ./ x;
    error = error < tol;
    if(all(error))
        disp("    x_1       x_2       x_3");
        disp(transpose(x));
        flag = 1;
        return
    end
end

if flag == 0
    fprintf("Sorry, no solutions found after %d iterations.\n", i);
end

