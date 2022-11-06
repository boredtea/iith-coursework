subroutine BackwardSweep(A, b, x)
    
    implicit none
    
    real, dimension(3, 3), intent(in) :: A
    real, dimension(3), intent(in) :: b
    real, dimension(3), intent(out) :: x
    
    x(3) = b(3) / A(3, 3)
    x(2) = (b(2) - (x(3) * A(2, 3))) / A(2, 2)
    x(1) = (b(1) - ((x(3) * A(1, 3)) + (x(2) * A(1, 2)))) / A(1 ,1)
    
end subroutine BackwardSweep
    