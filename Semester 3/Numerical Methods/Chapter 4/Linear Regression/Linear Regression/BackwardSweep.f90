subroutine BackwardSweep(A, b, x)
    
    implicit none
    
    real, dimension(2, 2), intent(inout) :: A
    real, dimension(2), intent(inout) :: b
    real, dimension(2), intent(out) :: x
    
    x(2) = b(2)/A(2,2)
    x(1) = (b(1) - (A(1,2) * x(2)))/A(1,1)
    
end subroutine BackwardSweep
    