subroutine Inverse(A, Inv)
    
    implicit none
    
    real, dimension(2, 2), intent(in) :: A
    real, dimension(2, 2), intent(out) :: Inv
    real :: determinant
    
    
    Inv(1, 1) = A(2, 2)
    Inv(1, 2) = -A(1, 2)
    Inv(2, 1) = -A(2, 1)
    Inv(2, 2) = A(1, 1)

    determinant = (A(1, 1) * A(2, 2)) - (A(1, 2) * A(2, 1))

    Inv = Inv / determinant
    
end subroutine Inverse
    