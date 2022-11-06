
    program GaussElimination

    implicit none

    real, dimension(3, 3) :: A, Inv
    real, dimension(3) :: b, x
    
    real:: pivot, factor
    
    integer :: i, j, k, N
    N = 3
    
    Inv = 0
    Inv(1, 1) = 1
    Inv(2, 2) = 1
    Inv(3, 3) = 1
    
    
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
    
    call GJ(A, b, Inv)
    x = b
   
    
    print*, "New A:"
    call PrintArray(A)
    print*, "Inverse:"
    call PrintArray(Inv)
    print*, "X:"
    print*, x

    end program GaussElimination

