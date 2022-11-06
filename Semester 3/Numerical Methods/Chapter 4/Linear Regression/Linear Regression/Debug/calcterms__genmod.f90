        !COMPILER-GENERATED INTERFACE MODULE: Sun Nov  8 22:03:45 2020
        ! This source file is for reference only and may not completely
        ! represent the generated interface used by the compiler.
        MODULE CALCTERMS__genmod
          INTERFACE 
            SUBROUTINE CALCTERMS(X,Y,N,SUMX,SUMY,SUMXY,SUMXX)
              INTEGER(KIND=4), INTENT(IN) :: N
              REAL(KIND=4), INTENT(IN) :: X(N)
              REAL(KIND=4), INTENT(IN) :: Y(N)
              REAL(KIND=4), INTENT(OUT) :: SUMX
              REAL(KIND=4), INTENT(OUT) :: SUMY
              REAL(KIND=4), INTENT(OUT) :: SUMXY
              REAL(KIND=4), INTENT(OUT) :: SUMXX
            END SUBROUTINE CALCTERMS
          END INTERFACE 
        END MODULE CALCTERMS__genmod
