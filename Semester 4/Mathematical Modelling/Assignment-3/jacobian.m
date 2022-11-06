function J = jacobian(x)

J = [(2 * x(1)), 1, -1; 1, 1, 0; 4 * (x(1) ^ 3), 3, (2 * x(3))];

end