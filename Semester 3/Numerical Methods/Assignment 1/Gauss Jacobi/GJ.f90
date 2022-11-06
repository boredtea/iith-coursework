subroutine GJ(A, b, x)
    
    implicit none
    
    real, dimension(3, 3), intent(in) :: A
    real, dimension(3), intent(in) :: b
    real, dimension(3), intent(inout) :: x
    
    real, dimension(3) :: xOld
    
    xOld = x
    
    x(1) = (b(1) - a(1, 2)*xOld(2) - a(1, 3)*xOld(3)) / a(1, 1)
    x(2) = (b(2) - a(2, 1)*xOld(1) - a(2, 3)*xOld(3)) / a(2, 2)
    x(3) = (b(3) - a(3, 1)*xOld(1) - a(3, 2)*xOld(2)) / a(3, 3)
    
end subroutine GJ
    
    
    