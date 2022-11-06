program NIFD
    
    implicit none
    real, dimension(4) :: x, y
    
    real, dimension(3) :: xNew, yNew, a
    real :: delX
    integer :: i
    
    open(10,file = "data.txt")
    do i = 1,4
        read(10,*) x(i), y(i)
    end do
    close(10)
    
    delX = x(2) - x(1)
    xNew(1) = 1.5
    xNew(2) = 2.5
    xNew(3) = 3.5
    
    do i = 1, 3
        a(i) = (xNew(i) - x(1))/delX
        call getvalues(y, a(i), yNew(i))
        write(*,*) "y at x = ", xNew(i), " is ", yNew(i)
    end do
    
end program NIFD
