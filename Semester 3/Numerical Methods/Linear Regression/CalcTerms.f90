subroutine CalcTerms(x, y, n, sumX, sumY, sumXY, sumXX)
    
    implicit none
    
    integer, intent(in) :: n
    real, dimension(n), intent(in) :: x, y
    real, intent(out) :: sumX, sumY, sumXY, sumXX
    
    integer :: i
    
    sumX = 0
    sumY = 0
    sumXY = 0
    sumXX = 0
    
    do i = 1, n
        sumX = sumX + x(i)
        sumY = sumY + y(i)
        sumXY = sumXY + ((x(i)) * (y(i)))
        sumXX = sumXX + (x(i))**2
    end do
    
end subroutine CalcTerms