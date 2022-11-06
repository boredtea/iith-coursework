function [root, num_itr, convergence] = newtonraphson(fun, dfunc, x_0)
tol = 1e-6;
num_itr = 0;
for i = 1 : 20
    dx = -feval(fun, x_0) / feval(dfunc, x_0);
    x = x_0 + dx;
    convergence(i) = (abs(dx/x)) * 100;
    if abs(dx) < tol
        root = x;
        num_itr = i;
        
        fprintf("Newton Rhapson\nRoot: %f \nIterations: %d \n\n", root, num_itr);
        return
    end
    x_0 = x;
end
root = NaN;

end