program Simpson
    
    implicit none
    
    real :: z, delr, theta_b
    real, dimension(5) :: r, theta, y
    integer :: i

    z = 0.5
    r(1) = 0

    do i = 2,5
        r(i) = r(i-1) + 0.25
    end do

    do i = 1,5
        call getValues(z, r(i), theta(i))
    end do

    delr = r(2) - r(1)

    do i = 1,5
        call yValues(theta(i), r(i), y(i))
    end do

    theta_b = (delr/3.0) * (y(1) + 4*y(2) + 2*y(3) + 4*y(4) + y(5))
    print *, "The numerical solution is ", theta_b
    
end program Simpson
