function [root, num_itr, convergence] = bisect(func, x1, x2)
tol = 1e-12;
f1 = feval (func, x1);
if f1 == 0
    root = x1;
    return
end

f2 = feval(func, x2);
if  f2 == 0
    root = x2;
    return
end

if (f1 * f2) > 0
    error('root is not bracketed in (x1, x2)')
    return
end

num_itr = ceil(log(abs(x2 - x1)/tol)/log(2));
for i = 1 : num_itr
    x3 = 0.5 * (x1 + x2);
    f3 = feval(func, x3);
    if f3 == 0
        root =  x3;
        return
    end
    if (f2 * f3) < 0
        convergence(i) = (abs((x3 - x1)/x3)) * 100;
        x1 = x3;
        f1 = f3;
        
    else
        convergence(i) = (abs((x3 - x2)/x3)) * 100;
        x2 = x3; 
        f2 = f3;
    end
    root = 0.5 * (x1 + x2);
    
end

fprintf("Bisect\nRoot: %f \nIterations: %d \n\n", root, num_itr);

end
