subroutine CalculateFunc(x, f)
    
    implicit none
    
    real, dimension(2), intent(in) :: x
    real, dimension(2), intent(out) :: f
    
    f(1) = x(1) + 2 * x(1)**2 - 5 * x(2)**3 - 3
    f(2) = 3 * x(1)**3 + x(2) + 2 * x(2)**2 - 26
    
end subroutine CalculateFunc