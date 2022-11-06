subroutine PrintMatrix(A)
    
    implicit none
    
    real, dimension(3, 3), intent(in) :: A
    
    
    integer :: i
    
    do i = 1, 3
        
        print*, A(i, :)
        
    end do
    
end subroutine PrintMatrix