        !COMPILER-GENERATED INTERFACE MODULE: Tue Nov 10 15:39:17 2020
        ! This source file is for reference only and may not completely
        ! represent the generated interface used by the compiler.
        MODULE DIFFERENCES__genmod
          INTERFACE 
            SUBROUTINE DIFFERENCES(Y,DELY,DEL2Y,DEL3Y)
              REAL(KIND=4), INTENT(IN) :: Y(4)
              REAL(KIND=4), INTENT(OUT) :: DELY(3)
              REAL(KIND=4), INTENT(OUT) :: DEL2Y(2)
              REAL(KIND=4), INTENT(OUT) :: DEL3Y
            END SUBROUTINE DIFFERENCES
          END INTERFACE 
        END MODULE DIFFERENCES__genmod
