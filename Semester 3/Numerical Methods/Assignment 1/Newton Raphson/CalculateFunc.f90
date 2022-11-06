subroutine CalculateFunc(x, F)
    
    implicit none
    
    real, dimension(2), intent(in) :: x
    real, dimension(2), intent(out) :: F
    
    F(1) = 2 * x(1)**2 - 5 * x(2)**3 - 3
    F(2) = 3 * x(1)**3 + 2 * x(2)**2 - 26
    
end subroutine CalculateFunc