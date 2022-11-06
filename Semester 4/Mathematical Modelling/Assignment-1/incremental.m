function [x1, x2, num_itr, convergence] = incremental(func, a, b, dx)
x1 = a;
f1 = feval(func, x1);
x2 = a + dx;
f2 = feval(func, x2);
num_itr = 0;
while (f1 * f2) > 0
    num_itr = num_itr + 1;
    convergence(num_itr) = (abs((dx)/x2)) * 100;
    if x1 >= b
        x1 = NaN;
        x2 = NaN;
        return
    end
    x1 = x2;
    f1 = f2;
    x2 = x1 + dx;
    f2 = feval(func, x2);
    
end
fprintf("Incremental Search\nRoot: %f \nIterations: %d \n\n", x2, num_itr);
end