subroutine LU(A, L, U)
    
    implicit none
    
    real, dimension(3, 3), intent(in) :: A
    real, dimension(3, 3), intent(inout) :: L
    real, dimension(3, 3), intent(inout) :: U
    
    integer :: i, j, k, N
    real :: sum
    N = 3
    
    do i = 1, N    !for U and L
        
        !U Matrix
        do k = i, N
            sum = 0    !sigma L(i, j) * U(j, k)
            do j = 1, i
                sum = sum + (L(i, j) * U(j, k))
            end do
            U(i, k) = A(i, k) - sum
        end do
        
        !L matrix
        do k = i, N
            if(i == k) then
                L(i, i) = 1
            else
                sum = 0    !sigma L(k, j) * U(j, i)
                do j = 1, i
                    sum = sum + (L(k, j) * U(j, i))
                end do
                L(k, i) = (A(k, i) - sum) / U(i, i)
            end if
        end do
    end do
                
            
        
    
    
    
end subroutine LU
    