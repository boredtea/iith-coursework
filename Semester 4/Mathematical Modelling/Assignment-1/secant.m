function [root, num_itr, convergence] = secant(func, x_1, x_0)
tol = 1e-6;
num_itr = 0;
% convergence = zeroes(10, 1);
for i = 1 : 20
    dx = -feval(func, x_1) / ((feval(func, x_1) - feval(func, x_0)) / (x_1 - x_0));
    x = x_1 + dx;
    convergence(i) = (abs((dx)/x)) * 100;
    if abs(dx) < tol
        root = x;
        num_itr = i;
        fprintf("Secant\nRoot: %f \nIterations: %d \n\n", root, num_itr);
        return
    end
    x_0 = x_1;
    x_1 = x;
end
root = NaN;

end