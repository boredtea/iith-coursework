subroutine GE(A, b)
    
    implicit none
    
    real, dimension(3, 3), intent(inout) :: A
    real, dimension(3), intent(inout) :: b
    
    real:: pivot, factor
    
    integer :: i, j, k, N
    N = 3
    
    do k = 2, N
        pivot = A(k - 1, k - 1)
        do i = k, N
            factor = A(i, k - 1)/pivot
            b(i) = b(i) - factor * b(k - 1)
            do j = 1, N
                A(i, j) = A(i, j) - factor * A(k - 1, j)
            end do
        end do
    end do
    
end subroutine GE