program LinearRegression

    implicit none

    integer :: i, n = 7
    
    real, dimension(7) :: x, y
    
    real :: sumX, sumY, sumXY, sumXX, a0, a1
    
    real, dimension(7, 2) :: xMat
    real, dimension(2, 7) :: xTrans
    real, dimension(2, 2) :: xTransX
    real, dimension(7, 1) :: yMat
    real, dimension(2, 1) :: a, xTransy
    
    open(2, file = "data.txt")
    
    do i = 1, n
        read (2, *) x(i), y(i)
        xMat(i, 2) = x(i)
        yMat(i, 1) = y(i)
    end do
    close(2)
    
    call CalcTerms(x, y, n, sumX, sumY, sumXY, sumXX)
    
    a1 = (n * sumXY - sumX * sumY)/(n * sumXX - sumX * sumX)
    a0 = -(a1 * sumX - sumY)/n
    
    print *,"Analytical Method"
    print *,"The best straight line fit is y = ", a0, "+", a1, "x"
    
    xTrans = Transpose(xMat)
    xTransX = matmul(xTrans, xMat)
    xTransy = matmul(xTrans, yMat)

    call GE(xTransX, xTransy)
    call BackwardSweep(xTransX, xTransy, a)
    
    print *,"Matrix Method"
    print *,"The best straight line fit is y = ", a(1, 1), "+", a(2, 1), "x"
    
    
    
    

end program LinearRegression

