subroutine GJ(A, b, Inv)
    
    implicit none
    
    real, dimension(3, 3), intent(inout) :: A, Inv
    real, dimension(3), intent(inout) :: b
    
    real:: pivot, factor
    
    integer :: i, j, k, N
    N = 3
    
    
    do i = 1, N
        pivot = A(i, i)
        b(i) = b(i) / pivot
        
        ! dividing the rows of A and Inv with the pivot 
        do j = i, N
            A(i, j) = A(i, j) / pivot
        end do
        do j = 1, N
            Inv(i, j) = Inv(i, j) / pivot
        end do
        
        do j = i + 1, N
            factor = A(j, i)
            
            b(j) = b(j) - factor * b(i)
            do k = i, N
                A(j, k) = A(j, k) - factor * A(i, k)
            end do
            do k = 1, N
                Inv(j, k) = Inv(j, k) - factor * Inv(i, k)
            end do
        end do
    end do
    
    do i = N, 2, -1
        do j = i - 1, 1, -1
            factor = A(j, i)
            A(j, i) = 0
            b(j) = b(j) - factor * b(i)
            
            do k = 1, N
                Inv(j, k) = Inv(j, k) - factor * Inv(i, k)
            end do
        end do
    end do

            
      
                
    
    
end subroutine GJ