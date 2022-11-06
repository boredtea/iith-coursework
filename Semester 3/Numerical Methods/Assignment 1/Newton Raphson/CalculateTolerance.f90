subroutine CalculateTolerance(x, xOld, tolerance, flag)
    
    implicit none
    
    real, dimension(2), intent(in) :: x, xOld
    real, intent(in) :: tolerance
    integer, intent(out) :: flag
    
    if ((abs((x(1) - xOld(1))/xOld(1))) .LE. tolerance .AND. (abs((x(2) - xOld(2))/xOld(2)) .LE. tolerance)) then
        flag = -1
    else
        flag = 1
    end if
end subroutine
        
    