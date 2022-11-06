subroutine getValues(y,a,f)
    
    implicit none
    
    real, dimension(4), intent(in) :: y
    real, intent(in) :: a
    real, intent(out) :: f
    real, dimension(3) :: delY
    real, dimension(2) :: del2Y
    real :: del3Y
    
    call differences(y, delY, del2Y, del3Y)
    
    f = y(1) + delY(1)*a + del2Y(1)*(a**2- a)/2 + del3Y*((a**2 - a)*(a - 2))/6
    
end subroutine getValues