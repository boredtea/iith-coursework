subroutine yValues(theta, r, y)
    
    implicit none
    
    real, intent(in) :: theta, r
    real, intent(out) :: y
    
    y = 4 * theta * (1 - r**2) * r
    
end subroutine yValues