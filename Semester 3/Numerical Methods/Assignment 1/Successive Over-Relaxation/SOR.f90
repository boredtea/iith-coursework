subroutine SOR(A, b, x, w)
    
    implicit none
    
    real, dimension(3, 3), intent(in) :: A
    real, dimension(3), intent(in) :: b
    real, dimension(3), intent(inout) :: x
    real, intent(in) :: w
    
    x(1) = w * ((b(1) - a(1, 2)*x(2) - a(1, 3)*x(3)) / a(1, 1)) + (1 - w) * x(1)
    x(2) = w * ((b(2) - a(2, 1)*x(1) - a(2, 3)*x(3)) / a(2, 2)) + (1 - w) * x(2)
    x(3) = w * ((b(3) - a(3, 1)*x(1) - a(3, 2)*x(2)) / a(3, 3)) + (1 - w) * x(3)
    
end subroutine SOR
    
    
    