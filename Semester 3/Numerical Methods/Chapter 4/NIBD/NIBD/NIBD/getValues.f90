subroutine getValues(y, a, f)

    implicit none

    real, dimension(4), intent(in) :: y
    real, intent(in) :: a
    real, intent(out) :: f
    real, dimension(4) :: delY, del2Y
    real :: del3Y

    call differences(y,delY,del2Y,del3Y)
    f = y(4) + delY(4)*a + del2Y(4)*(a**2+ a)/2 + del3Y*((a**2 + a)*(a + 2))/6

end subroutine getValues