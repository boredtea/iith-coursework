clc

% A = [4, 12, -16; 12, 37, -43; -16, -43, 98];
A = [1, 1, 3; 1, 5, 5; 3, 5, 19];
cholesky_algo(A)

function cholesky_algo(A)
n = size(A);
if(n(1) == n(2) && issymmetric(A))
    L = zeros(n(1), n(2));
    for i = 1:n(1)
        for j = 1:i
            sum = 0;
            if j == i % diagonals
               for k = 1:j
                   sum = sum + L(j, k) ^ 2;
               end
               L(j, j) = sqrt(A(j, j) - sum);

            else % other cells
                for k = 1:j
                    sum = sum + L(i, k) * L(j, k);
                end
                L(i, j) = (A(i, j) - sum) / L(j, j);
            end 
        end
    end
    L_t = transpose(L);
    disp("Lower: ");
    disp(L);
    disp("Lower transposed: ");
    disp(L_t);
    disp("Inbuilt MATLAB function: ");
    disp(chol(A, 'lower'));
else
    disp("The given matrix is either not square or not symmetric, or neither.");
end
end



