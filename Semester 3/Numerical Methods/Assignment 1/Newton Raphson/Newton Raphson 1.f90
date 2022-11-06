program NewtonRaphson1

    implicit none
    
    real, dimension(2) :: x, xOld, F, P
    real, dimension(2, 2) :: A, Inv ! for Jacobian
    real :: tolerance = 1E-7
    integer :: i, flag, steps_1, steps_2
    
    x = 1
    print*, "Intitial guess: ", x
    
    xOld = x
    
    do i = 1, 1000
        call CalculateFunc(x, F)
        call Jacobian(x, A)
        call Inverse(A, Inv)
        call MatrixMultiply(Inv, F, P)
        
        write(*, *) "Step ", i, x(1), x(2), F(1), F(2)
        
        xOld = x
        x = x - P
        
        call CalculateTolerance(x, xOld, tolerance, flag)
        
        if(flag == -1) then
            steps_1 = i
            exit
        end if
        
    end do
    
    print*, "x1: ", x(1), "x2: ", x(2)
    
    print*, "----------------------------------------------------------------"
    
    x = 0.5
    print*, "Intitial guess: ", x
    
    xOld = x
    
    do i = 1, 1000
        call CalculateFunc(x, F)
        call Jacobian(x, A)
        call Inverse(A, Inv)
        call MatrixMultiply(Inv, F, P)
        
        write(*, *) "Step ", i, x(1), x(2), F(1), F(2)
        
        xOld = x
        x = x - P
        
        call CalculateTolerance(x, xOld, tolerance, flag)
        
        if(flag == -1) then
            steps_2 = i
            exit
        end if
        
    end do
    
    print*, "x1: ", x(1), "x2: ", x(2)
    
    print*, "----------------------------------------------------------------"
    
    if(steps_1 > steps_2) then
        print*, "The initial guess x = 0.5 converged faster."
    else
        print*, "The initial guess x = 1 converged faster."
    end if
    
    
    end program NewtonRaphson1