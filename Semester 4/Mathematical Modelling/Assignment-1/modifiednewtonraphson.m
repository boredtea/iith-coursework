function [root, num_itr, convergence] = modifiednewtonraphson(func, dfunc, ddfunc, x_0)
tol = 1e-6;
num_itr = 0;
for i = 1 : 20
    du = -(feval(func, x_0) * feval(dfunc, x_0)) / (feval(dfunc, x_0)^2 - feval(func, x_0) * feval(ddfunc, x_0));
    x = x_0 + du;
    convergence(i) = (abs(du/x)) * 100;
    if abs(du) < tol
        root = x;
        num_itr = i;
        
        fprintf("Modified Newton Rhapson\nRoot: %f \nIterations: %d \n\n", root, num_itr);
        return
    end
    x_0 = x;
end
root = NaN;

end