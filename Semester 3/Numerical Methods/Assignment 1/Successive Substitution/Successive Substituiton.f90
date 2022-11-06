program SuccessiveSubstituiton

    implicit none

    real, dimension(2) :: x, f
    real :: tolerance = 1E-7
    integer :: i
    
    x = 1
    
    do i = 1, 100
        call CalculateFunc(x, f)
        print *, "Step ", i, "X: ", x
        
        if((abs((f(1) - x(1))/x(1)) <= tolerance) .AND. (abs((f(2) - x(2))/x(2)) <= tolerance)) then
            exit
        end if
        x(1) = f(1)
        x(2) = f(2)
    end do
    
    print*, "x1: ", x(1), "x2: ", x(2)
    print*, "Clearly, the solution does not converge."
    


end program SuccessiveSubstituiton

