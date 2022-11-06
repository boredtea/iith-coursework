
    program GaussElimination

    implicit none

    real, dimension(3, 3) :: A
    real, dimension(3) :: b, x
    
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
    
    call GE(A, b)
    call BackwardSweep(A, b, x)
    
    print*, "New A:"
    call PrintArray(A)
    print*, "New B:"
    print*, b
    print*, "X:"
    print*, x

    end program GaussElimination

