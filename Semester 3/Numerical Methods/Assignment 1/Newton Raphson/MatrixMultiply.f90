subroutine MatrixMultiply(A, F, P)
    
    implicit none
    
    real, dimension(2, 2), intent(in) :: A
    real, dimension(2, 1), intent(in) :: F   
    real, dimension(2, 1), intent(out) :: P
    
    integer :: ARow, AColumn, FRow, FColumn
    real :: sum
    
    FRow = 1
    FColumn = 1
    sum = 0
    
    do Arow = 1, 2
        do AColumn = 1, 2
            P(ARow, FColumn) = sum + A(ARow, AColumn) * F(FRow, FColumn)
            sum = P(ARow, FColumn)
            FRow = FRow + 1
        end do
        FRow = 1
        sum = 0
    end do
end subroutine MatrixMultiply