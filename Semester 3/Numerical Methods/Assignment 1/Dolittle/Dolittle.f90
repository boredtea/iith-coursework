
program Dolittle

    implicit none
    
    real, dimension(3, 3) :: A, L, U
    real, dimension(3) :: b, x, y
    
    L = 0
    U = 0
    
    A(1, 1) = 5
    A(1, 2) = -2
    A(1, 3) = 3
    
    A(2, 1) = 3
    A(2, 2) = 9
    A(2, 3) = -5
    
    A(3, 1) = 3
    A(3, 2) = -2
    A(3, 3) = 7
    
    b(1) = 27
    b(2) = -11
    b(3) = 51
    
    call LU(A, L, U)
    print*, "L: "
    call PrintMatrix(L)
    
    print*, "U: "
    call PrintMatrix(U)
    
    call ForwardSweep(L, b, y)
    call BackwardSweep(U, y, x)
    
    print*, "y: "
    print*, y
    
    print*, "x: "
    print*, x
    


    end program Dolittle

