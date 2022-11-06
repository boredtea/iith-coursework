subroutine differences(y, delY, del2Y, del3Y)
    
    implicit none

    real, dimension(4),intent(in) :: y
    real, dimension(3), intent(out) :: delY
    real, dimension(2), intent(out) :: del2Y
    real, intent(out) :: del3Y
    integer :: i

    do i = 1, 3
        delY(i) = y(i+1) - y(i)
    end do

    do i = 1, 2
        del2Y(i) = delY(i+1) - delY(i)
    end do

    del3Y = del2Y(2) - del2Y(1)

end subroutine differences