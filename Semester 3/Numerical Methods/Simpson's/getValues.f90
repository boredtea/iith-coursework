subroutine getValues(z, r, theta)
    
    implicit none
    
    real,intent(in) :: z, r
    real,intent(out) :: theta
    
    theta = - 4 * z - r ** 2 + (r ** 4)/4.0 + 7.0/24.0
    
end subroutine getValues