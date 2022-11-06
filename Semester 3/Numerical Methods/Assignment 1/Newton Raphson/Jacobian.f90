subroutine Jacobian(x, A)
    
    implicit none
    
    real, dimension(2), intent(in) :: x
    real, dimension(2, 2), intent(out) :: A
    
    A(1, 1) = 4 * x(1)
    A(1, 2) = -15 * x(2)**2
    A(2, 1) = 9 * x(1)**2
    A(2, 2) = 4 * x(2)
    
end subroutine Jacobian