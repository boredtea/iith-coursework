subroutine ForwardSweep(L, b, y)
    
    implicit none
    
    real, dimension(3, 3), intent(in) :: L
    real, dimension(3), intent(in) :: b
    real, dimension(3), intent(out) :: y
    
    y(1) = b(1) / L(1, 1)
    y(2) = (b(2) - (y(1) * L(2, 1))) / L(2, 2)
    y(3) = (b(3) - ((y(1) * L(3, 1)) + (y(2) * L(3, 2)))) / L(3 ,3)
    
    
end subroutine ForwardSweep
    