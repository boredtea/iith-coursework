subroutine differences(y, delY, del2Y, del3Y)
    
    implicit none

    real, dimension(4),intent(in) :: y
    real, dimension(4),intent(out) :: delY, del2Y
    real, intent(out) :: del3Y
    integer :: i

    do i = 2,4
        delY(i) = y(i) - y(i-1)
    end do

    do i = 3,4
        del2Y(i) = delY(i) - delY(i-1)
    end do

    del3Y = del2Y(4) - del2Y(3)

end subroutine differences