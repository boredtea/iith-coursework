program GaussSiedel

    implicit none

    real, dimension(3, 3) :: A
    real, dimension(3) :: b, x, xOld, tolerance
    real :: w
    integer :: k, i
    
    w = 1.5
    
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
    
    x(1) = 1
    x(2) = 2
    x(3) = 1
    
    do k = 1, 100
        write (*, *) "Step: ", k, " ", x
        
        xOld = x
        call SOR(A, b, x, w)
        
        do i = 1, 3
            tolerance(i) = abs((x(i) - xOld(i))/xOld(i))
        end do
        
        
        if(tolerance(1) < 1E-5 .AND. tolerance(2) < 1E-5 .AND. tolerance(3) < 1E-5) then
            exit
        end if
    end do
    
end program GaussSiedel

