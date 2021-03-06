MODULE scf_tools

INTERFACE CHECKNUMCONV
  MODULE PROCEDURE CHECKNUMCONV_relativistic,CHECKNUMCONV_AOCOSDHF,CHECKNUMCONV_RHF,CHECKNUMCONV_UHF
END INTERFACE

CONTAINS

SUBROUTINE CHECKORB(EIG,N,LOON)
! Subroutine that determines the number of the lowest and highest occupied electronic orbitals and checks if they are both in the spectral gap (in the relavistic case).
  USE case_parameters ; USE data_parameters
  IMPLICIT NONE
  DOUBLE PRECISION,DIMENSION(N),INTENT(IN) :: EIG
  INTEGER,INTENT(IN) :: N
  INTEGER,INTENT(OUT) :: LOON

  INTEGER :: HGEN

! determination of the number of the lowest occupied orbital (i.e., the one relative to the first eigenvalue associated to an electronic state in the gap)
  LOON=MINLOC(EIG,DIM=1,MASK=EIG>-C*C)
  IF (LOON.EQ.0) THEN
     STOP'Subroutine CHECKORB: no eigenvalue associated to an electronic state.'
  ELSE
     WRITE(*,'(a,i3,a,i3,a)')' Number of the lowest occupied electronic orbital = ',LOON,'(/',N,')'
     IF (N-LOON.LT.NBE) THEN
        WRITE(*,'(a)')' Subroutine CHECKORB: there are not enough eigenvalues associated to electronic states (',N-LOON,').'
        STOP
     END IF
! determination of the number of the highest orbital relative to an eigenvalue associated to an electronic state in the gap
     HGEN=MAXLOC(EIG,DIM=1,MASK=EIG<0.D0)
     WRITE(*,'(a,i3)')' Number of eigenvalues associated to electronic states in the gap = ',HGEN-LOON+1
     IF (HGEN-LOON+1.LT.NBE) THEN
        WRITE(*,'(a,i2,a)')' Warning: there are less than ',NBE,' eigenvalues associated to electronic states in the gap.'
     END IF
  END IF
END SUBROUTINE CHECKORB

SUBROUTINE CHECKNUMCONV_relativistic(PDMN,PDMO,PFM,N,ETOTN,ETOTO,TRSHLD,NUMCONV,VERBOSE)
! Subroutine that checks several numerical convergence criteria for the SCF solutions of Hartree-Fock equations (restricted closed-shell Hartree-Fock and closed-shell Dirac-Hartree-Fock formalisms).
  USE matrix_tools ; USE metric_relativistic
  IMPLICIT NONE
  DOUBLE COMPLEX,DIMENSION(N*(N+1)/2),INTENT(IN) :: PDMN,PDMO,PFM
  INTEGER,INTENT(IN) :: N
  DOUBLE PRECISION,INTENT(IN) :: ETOTN,ETOTO,TRSHLD
  LOGICAL,INTENT(OUT) :: NUMCONV
  LOGICAL,INTENT(IN) :: VERBOSE

  DOUBLE COMPLEX,DIMENSION(N*(N+1)/2) :: PDIFF
  DOUBLE COMPLEX,DIMENSION(N,N) :: CMT,ISRS
  DOUBLE PRECISION :: FNDFDN,FNCMT
  DOUBLE PRECISION,DIMENSION(N) :: WORK
  LOGICAL :: CONVD,CONVC

  CONVD=.FALSE. ; CONVC=.FALSE.

  PDIFF=ABA(PSRS,PDMN-PDMO,N)
  FNDFDN=NORM(PDIFF,N,'F')
  WRITE(*,*)'Frobenius norm of the difference D_n-D_{n-1} =',FNDFDN
  WRITE(17,'(e22.14)')FNDFDN
  IF (FNDFDN<=TRSHLD) CONVD=.TRUE.

  ISRS=UNPACK(PISRS,N)
  CMT=MATMUL(ISRS,MATMUL(COMMUTATOR(PFM,PDMN,PS,N),ISRS))
  FNCMT=NORM(CMT,N,'F')
  WRITE(*,*)'Frobenius norm of the commutator [F(D_n),D_n] =',FNCMT
  WRITE(18,'(e22.14)')FNCMT
  IF (FNCMT<=TRSHLD) CONVC=.TRUE.
! Note: this criterion is not used to assert convergence
  WRITE(*,*)'Difference of the energies E_n-E_{n-1} =',ETOTN-ETOTO,'Ha'
  WRITE(16,'(e22.14)')ETOTN

  IF (CONVD.AND.CONVC) THEN
     NUMCONV=.TRUE.
  ELSE
     NUMCONV=.FALSE.
  END IF
END SUBROUTINE CHECKNUMCONV_relativistic

SUBROUTINE CHECKNUMCONV_RHF(PDMN,PDMO,PFM,N,ETOTN,ETOTO,TRSHLD,NUMCONV,VERBOSE)
! Subroutine that checks several numerical convergence criteria for the SCF solutions of Hartree-Fock equations (restricted closed-shell Hartree-Fock formalism).
  USE matrix_tools ; USE metric_nonrelativistic
  IMPLICIT NONE
  DOUBLE PRECISION,DIMENSION(N*(N+1)/2),INTENT(IN) :: PDMN,PDMO,PFM
  INTEGER,INTENT(IN) :: N
  DOUBLE PRECISION,INTENT(IN) :: ETOTN,ETOTO,TRSHLD
  LOGICAL,INTENT(OUT) :: NUMCONV
  LOGICAL,INTENT(IN) :: VERBOSE

  DOUBLE PRECISION,DIMENSION(N*(N+1)/2) :: PDIFF
  DOUBLE PRECISION,DIMENSION(N,N) :: CMT,ISRS
  DOUBLE PRECISION :: FNDFDN,FNCMT
  DOUBLE PRECISION,DIMENSION(N) :: WORK
  LOGICAL :: CONVD,CONVC

  CONVD=.FALSE. ; CONVC=.FALSE.

  PDIFF=ABA(PSRS,PDMN-PDMO,N)
  FNDFDN=NORM(PDIFF,N,'F')
  IF (VERBOSE) WRITE(*,*)'Frobenius norm of the difference D_n-D_{n-1} =',FNDFDN
  WRITE(17,'(e22.14)')FNDFDN
  IF (FNDFDN<=TRSHLD) CONVD=.TRUE.

  ISRS=UNPACK(PISRS,N)
  CMT=MATMUL(ISRS,MATMUL(COMMUTATOR(PFM,PDMN,PS,N),ISRS))
  FNCMT=NORM(CMT,N,'F')
  IF (VERBOSE) WRITE(*,*)'Frobenius norm of the commutator [F(D_n),D_n] =',FNCMT
  WRITE(18,'(e22.14)')FNCMT
  IF (FNCMT<=TRSHLD) CONVC=.TRUE.
! Note: this criterion is not used to assert convergence
  IF (VERBOSE) WRITE(*,*)'Difference of the energies E_n-E_{n-1} =',ETOTN-ETOTO,'Ha'
  WRITE(16,'(e22.14)')ETOTN

  IF (CONVD.AND.CONVC) THEN
     NUMCONV=.TRUE.
  ELSE
     NUMCONV=.FALSE.
  END IF
END SUBROUTINE CHECKNUMCONV_RHF

SUBROUTINE CHECKNUMCONV_UHF(PDMA,PDMB,PTDMO,PFMA,PFMB,N,ETOTN,ETOTO,TRSHLD,NUMCONV,VERBOSE)
! Subroutine that checks several numerical convergence criteria for the SCF solutions of Hartree-Fock type equations (unrestricted open-shell Hartree-Fock formalism).
  USE matrix_tools ; USE metric_nonrelativistic
  IMPLICIT NONE
  DOUBLE PRECISION,DIMENSION(N*(N+1)/2),INTENT(IN) :: PDMA,PDMB,PTDMO,PFMA,PFMB
  INTEGER,INTENT(IN) :: N
  DOUBLE PRECISION,INTENT(IN) :: ETOTN,ETOTO,TRSHLD
  LOGICAL,INTENT(OUT) :: NUMCONV
  LOGICAL,INTENT(IN) :: VERBOSE

  DOUBLE PRECISION,DIMENSION(N*(N+1)/2) :: PDIFF
  DOUBLE PRECISION,DIMENSION(N,N) :: CMT,ISRS
  DOUBLE PRECISION :: FNDFDN,FNCMTA,FNCMTB
  LOGICAL :: CONVD,CONVC

  CONVD=.FALSE. ; CONVC=.FALSE.

  PDIFF=ABA(PSRS,PDMA+PDMB-PTDMO,N)
  FNDFDN=NORM(PDIFF,N,'F')
  WRITE(*,*)'Frobenius norm of the difference D_n-D_{n-1} =',FNDFDN
  IF (FNDFDN<=TRSHLD) CONVD=.TRUE.

  ISRS=UNPACK(PISRS,N)
  CMT=MATMUL(ISRS,MATMUL(COMMUTATOR(PFMA,PDMA,PS,N),ISRS))
  FNCMTA=NORM(CMT,N,'F')
  WRITE(*,*)'Frobenius norm of the commutator [F(D_n^a),D_n^a] =',FNCMTA
  CMT=MATMUL(ISRS,MATMUL(COMMUTATOR(PFMB,PDMB,PS,N),ISRS))
  FNCMTB=NORM(CMT,N,'F')
  WRITE(*,*)'Frobenius norm of the commutator [F(D_n^b),D_n^b] =',FNCMTB
  IF ((FNCMTA<=TRSHLD).AND.(FNCMTB<=TRSHLD)) CONVC=.TRUE.
! Note: this criterion is not used to assert convergence
  WRITE(*,*)'Difference of the energies E_n-E_{n-1} =',ETOTN-ETOTO,'Ha'

  IF (CONVD.AND.CONVC) THEN
     NUMCONV=.TRUE.
  ELSE
     NUMCONV=.FALSE.
  END IF
END SUBROUTINE CHECKNUMCONV_UHF

SUBROUTINE CHECKNUMCONV_AOCOSDHF(PDMCN,PDMON,PDMCO,PDMOO,PFMC,PFMO,N,ETOTN,ETOTO,TRSHLD,NUMCONV,VERBOSE)
! Subroutine that checks several numerical convergence criteria for the SCF solutions of Hartree-Fock type equations (average-of-configuration open-shell Dirac-Hartree-Fock formalism).
  USE matrix_tools ; USE metric_relativistic
  IMPLICIT NONE
  DOUBLE COMPLEX,DIMENSION(N*(N+1)/2),INTENT(IN) :: PDMCN,PDMON,PDMCO,PDMOO,PFMC,PFMO
  INTEGER,INTENT(IN) :: N
  DOUBLE PRECISION,INTENT(IN) :: ETOTN,ETOTO,TRSHLD
  LOGICAL,INTENT(OUT) :: NUMCONV
  LOGICAL,INTENT(IN) :: VERBOSE

  DOUBLE COMPLEX,DIMENSION(N*(N+1)/2) :: PDIFF
  DOUBLE COMPLEX,DIMENSION(N,N) :: CMT,ISRS
  DOUBLE PRECISION :: FNDFDNC,FNDFDNO,FNCMTC,FNCMTO
  LOGICAL :: CONVD,CONVC

  CONVD=.FALSE. ; CONVC=.FALSE.

  PDIFF=PDMCN-PDMCO
  FNDFDNC=NORM(PDIFF,N,'F')
  WRITE(*,*)'Frobenius norm of the difference D_n^c-DC_{n-1}^c =',FNDFDNC
  PDIFF=PDMON-PDMOO
  FNDFDNO=NORM(PDIFF,N,'F')
  WRITE(*,*)'Frobenius norm of the difference D_n^o-DC_{n-1}^o =',FNDFDNO
  IF ((FNDFDNC<=TRSHLD).AND.(FNDFDNO<=TRSHLD)) CONVD=.TRUE.

  ISRS=UNPACK(PISRS,N)
  CMT=MATMUL(ISRS,MATMUL(COMMUTATOR(PFMC,PDMCN,PS,N),ISRS))
  FNCMTC=NORM(CMT,N,'F')
  WRITE(*,*)'Frobenius norm of the commutator [F(D_n^c),D_n^c] =',FNCMTC
  CMT=MATMUL(ISRS,MATMUL(COMMUTATOR(PFMO,PDMON,PS,N),ISRS))
  FNCMTO=NORM(CMT,N,'F')
  WRITE(*,*)'Frobenius norm of the commutator [F(D_n^o),D_n^o] =',FNCMTO
  IF ((FNCMTC<=TRSHLD).AND.(FNCMTO<=TRSHLD)) CONVC=.TRUE.
! Note: this criterion is not used to assert convergence
  WRITE(*,*)'Difference of the energies E_n-E_{n-1} =',ETOTN-ETOTO,'Ha'

  IF (CONVD.AND.CONVC) THEN
     NUMCONV=.TRUE.
  ELSE
     NUMCONV=.FALSE.
  END IF
END SUBROUTINE CHECKNUMCONV_AOCOSDHF
END MODULE

MODULE graphics_tools

INTERFACE DENSITY_POINTWISE_VALUE
  MODULE PROCEDURE DENSITY_POINTWISE_VALUE_relativistic,DENSITY_POINTWISE_VALUE_nonrelativistic
END INTERFACE

INTERFACE EXPORT_DENSITY
  MODULE PROCEDURE EXPORT_DENSITY_relativistic,EXPORT_DENSITY_nonrelativistic
END INTERFACE

CONTAINS

FUNCTION DENSITY_POINTWISE_VALUE_relativistic(DM,PHI,NBAST,POINT) RESULT(VALUE)
! Function that computes the value of the electronic density associated to a given density matrix (only the upper triangular part of this matrix is stored in packed format) at a given point of space.
  USE basis_parameters ; USE matrix_tools
  IMPLICIT NONE
  DOUBLE COMPLEX,DIMENSION(NBAST,NBAST),INTENT(IN) :: DM
  TYPE(twospinor),DIMENSION(NBAST),INTENT(IN) :: PHI
  INTEGER,INTENT(IN) :: NBAST
  DOUBLE PRECISION,DIMENSION(3),INTENT(IN) :: POINT
  DOUBLE PRECISION :: VALUE

  INTEGER :: I
  DOUBLE COMPLEX,DIMENSION(NBAST,2) :: POINTWISE_VALUES
  DOUBLE COMPLEX,DIMENSION(2,2) :: MATRIX

  DO I=1,NBAST
     POINTWISE_VALUES(I,:)=TWOSPINOR_POINTWISE_VALUE(PHI(I),POINT)
  END DO
  MATRIX=MATMUL(TRANSPOSE(CONJG(POINTWISE_VALUES)),MATMUL(DM,POINTWISE_VALUES))
  VALUE=REAL(MATRIX(1,1)+MATRIX(2,2))
END FUNCTION DENSITY_POINTWISE_VALUE_relativistic

FUNCTION DENSITY_POINTWISE_VALUE_nonrelativistic(DM,PHI,NBAST,POINT) RESULT(VALUE)
! Function that computes the value of the electronic density associated to a given density matrix (only the upper triangular part of this matrix is stored in packed format) at a given point of space.
  USE basis_parameters ; USE matrix_tools
  IMPLICIT NONE
  DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(IN) :: DM
  TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI
  INTEGER,INTENT(IN) :: NBAST
  DOUBLE PRECISION,DIMENSION(3),INTENT(IN) :: POINT
  DOUBLE PRECISION :: VALUE

  INTEGER :: I
  REAL(KIND=C_DOUBLE),DIMENSION(NBAST) :: POINTWISE_VALUES

  DO I=1,NBAST
     POINTWISE_VALUES(I)=GBF_POINTWISE_VALUE(PHI(I),POINT)
  END DO
  VALUE=DOT_PRODUCT(POINTWISE_VALUES,MATMUL(DM,POINTWISE_VALUES))
END FUNCTION DENSITY_POINTWISE_VALUE_nonrelativistic

SUBROUTINE EXPORT_DENSITY_relativistic(DM,PHI,NBAST,RMIN,RMAX,NPOINTS,FILENAME,FILEFORMAT)
  USE basis_parameters ; USE data_parameters ; USE matrices
  IMPLICIT NONE
  DOUBLE COMPLEX,DIMENSION(NBAST,NBAST),INTENT(IN) :: DM
  TYPE(twospinor),DIMENSION(NBAST),INTENT(IN) :: PHI
  INTEGER,INTENT(IN) :: NBAST,NPOINTS
  DOUBLE PRECISION,INTENT(IN) :: RMIN,RMAX
  CHARACTER(*),INTENT(IN) :: FILENAME
  CHARACTER(*),INTENT(IN) :: FILEFORMAT

  INTEGER :: I,J,K
  DOUBLE PRECISION :: GRID_STEPSIZE
  DOUBLE PRECISION,DIMENSION(3) :: X

  IF (NPOINTS/=1) THEN
     GRID_STEPSIZE=(RMAX-RMIN)/(NPOINTS-1)
  ELSE
     STOP
  END IF
  IF ((FILEFORMAT=='matlab').OR.(FILEFORMAT=='MATLAB')) THEN
     OPEN(UNIT=42,FILE='plots/'//FILENAME)
     DO I=0,NPOINTS-1
        DO J=0,NPOINTS-1
           DO K=0,NPOINTS-1
              X(1)=RMIN+REAL(I)*GRID_STEPSIZE
              X(2)=RMIN+REAL(J)*GRID_STEPSIZE
              X(3)=RMIN+REAL(K)*GRID_STEPSIZE
              WRITE(42,*)X(:),DENSITY_POINTWISE_VALUE(DM,PHI,NBAST,X)
           END DO
        END DO
     END DO
     CLOSE(42)
  ELSE IF ((FILEFORMAT=='cube').OR.(FILEFORMAT=='CUBE')) THEN
     OPEN(UNIT=42,FILE='plots/'//FILENAME//'.cube')
     WRITE(42,*)'CUBE FILE.'
     WRITE(42,*)'OUTER LOOP: X, MIDDLE LOOP: Y, INNER LOOP: Z'
     WRITE(42,*)NBN,RMIN,RMIN,RMIN
     WRITE(42,*)NPOINTS,(RMAX-RMIN)/NPOINTS,0.D0,0.D0
     WRITE(42,*)NPOINTS,0.D0,(RMAX-RMIN)/NPOINTS,0.D0
     WRITE(42,*)NPOINTS,0.D0,0.D0,(RMAX-RMIN)/NPOINTS
     DO I=1,NBN
        WRITE(42,*)Z(I),0.D0,CENTER(:,I)
     END DO
     DO I=0,NPOINTS-1
        DO J=0,NPOINTS-1
           DO K=0,NPOINTS-1
              X(1)=RMIN+REAL(I)*GRID_STEPSIZE
              X(2)=RMIN+REAL(J)*GRID_STEPSIZE
              X(3)=RMIN+REAL(K)*GRID_STEPSIZE
              WRITE(42,*)DENSITY_POINTWISE_VALUE(DM,PHI,NBAST,X)
           END DO
        END DO
     END DO
     CLOSE(42)
  END IF
END SUBROUTINE EXPORT_DENSITY_relativistic

SUBROUTINE EXPORT_DENSITY_nonrelativistic(DM,PHI,NBAST,RMIN,RMAX,NPOINTS,FILENAME,FILEFORMAT)
  USE basis_parameters ; USE data_parameters ; USE matrices
  IMPLICIT NONE
  DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(IN) :: DM
  TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI
  INTEGER,INTENT(IN) :: NBAST,NPOINTS
  DOUBLE PRECISION,INTENT(IN) :: RMIN,RMAX
  CHARACTER(*),INTENT(IN) :: FILENAME
  CHARACTER(*),INTENT(IN) :: FILEFORMAT

  INTEGER :: I,J,K
  DOUBLE PRECISION :: GRID_STEPSIZE
  DOUBLE PRECISION,DIMENSION(3) :: X

  IF (NPOINTS/=1) THEN
     GRID_STEPSIZE=(RMAX-RMIN)/(NPOINTS-1)
  ELSE
     STOP
  END IF
  IF ((FILEFORMAT=='matlab').OR.(FILEFORMAT=='MATLAB')) THEN
     OPEN(UNIT=42,FILE='plots/'//FILENAME)
     DO I=0,NPOINTS-1
        DO J=0,NPOINTS-1
           DO K=0,NPOINTS-1
              X(1)=RMIN+REAL(I)*GRID_STEPSIZE
              X(2)=RMIN+REAL(J)*GRID_STEPSIZE
              X(3)=RMIN+REAL(K)*GRID_STEPSIZE
              WRITE(42,*)X(:),DENSITY_POINTWISE_VALUE(DM,PHI,NBAST,X)
           END DO
        END DO
     END DO
     CLOSE(42)
  ELSE IF ((FILEFORMAT=='cube').OR.(FILEFORMAT=='CUBE')) THEN
     OPEN(UNIT=42,FILE='plots/'//FILENAME//'.cube')
     WRITE(42,*)'CUBE FILE.'
     WRITE(42,*)'OUTER LOOP: X, MIDDLE LOOP: Y, INNER LOOP: Z'
     WRITE(42,*)NBN,RMIN,RMIN,RMIN
     WRITE(42,*)NPOINTS,(RMAX-RMIN)/NPOINTS,0.D0,0.D0
     WRITE(42,*)NPOINTS,0.D0,(RMAX-RMIN)/NPOINTS,0.D0
     WRITE(42,*)NPOINTS,0.D0,0.D0,(RMAX-RMIN)/NPOINTS
     DO I=1,NBN
        WRITE(42,*)Z(I),0.D0,CENTER(:,I)
     END DO
     DO I=0,NPOINTS-1
        DO J=0,NPOINTS-1
           DO K=0,NPOINTS-1
              X(1)=RMIN+REAL(I)*GRID_STEPSIZE
              X(2)=RMIN+REAL(J)*GRID_STEPSIZE
              X(3)=RMIN+REAL(K)*GRID_STEPSIZE
              WRITE(42,*)DENSITY_POINTWISE_VALUE(DM,PHI,NBAST,X)
           END DO
        END DO
     END DO
     CLOSE(42)
  END IF
END SUBROUTINE EXPORT_DENSITY_nonrelativistic
END MODULE

MODULE output
  DOUBLE PRECISION,DIMENSION(:,:),ALLOCATABLE :: ALL_EIG

INTERFACE OUTPUT_ITER
  MODULE PROCEDURE OUTPUT_ITER_nonrelativistic,OUTPUT_ITER_relativistic
END INTERFACE OUTPUT_ITER

INTERFACE OUTPUT_FINALIZE
  MODULE PROCEDURE OUTPUT_FINALIZE_nonrelativistic,OUTPUT_FINALIZE_relativistic
END INTERFACE OUTPUT_FINALIZE

CONTAINS

SUBROUTINE OUTPUT_ITER_relativistic(ITER,PDM,PHI,NBAST,EIG,EIGVEC,ETOT)
  USE basis_parameters ; USE scf_parameters
  IMPLICIT NONE
  INTEGER,INTENT(IN) :: ITER,NBAST
  DOUBLE PRECISION,INTENT(IN) :: ETOT
  DOUBLE PRECISION,DIMENSION(NBAST),INTENT(IN) :: EIG
  DOUBLE COMPLEX,DIMENSION(NBAST,NBAST),INTENT(IN) :: EIGVEC
  DOUBLE COMPLEX,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: PDM
  TYPE(twospinor),DIMENSION(NBAST),INTENT(IN) :: PHI

  IF (ITER==1) ALLOCATE(ALL_EIG(NBAST,MAXITR))
  ALL_EIG(:,ITER)=EIG
END SUBROUTINE OUTPUT_ITER_relativistic

SUBROUTINE OUTPUT_ITER_nonrelativistic(ITER,PDM,PHI,NBAST,EIG,EIGVEC,ETOT)
  USE basis_parameters ; USE scf_parameters
  IMPLICIT NONE
  INTEGER,INTENT(IN) :: ITER,NBAST
  DOUBLE PRECISION,INTENT(IN) :: ETOT
  DOUBLE PRECISION,DIMENSION(NBAST),INTENT(IN) :: EIG
  DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(IN) :: EIGVEC
  DOUBLE PRECISION,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: PDM
  TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI

  IF (ITER==1) ALLOCATE(ALL_EIG(NBAST,MAXITR))
  ALL_EIG(:,ITER)=EIG
END SUBROUTINE OUTPUT_ITER_nonrelativistic

SUBROUTINE OUTPUT_FINALIZE_relativistic(ITER,PDM,PHI,NBAST,EIG,EIGVEC,ETOT)
  USE basis_parameters ; USE graphics_tools ; USE matrix_tools
  IMPLICIT NONE
  INTEGER,INTENT(IN) :: ITER,NBAST
  DOUBLE PRECISION,INTENT(IN) :: ETOT
  DOUBLE PRECISION,DIMENSION(NBAST),INTENT(IN) :: EIG
  DOUBLE COMPLEX,DIMENSION(NBAST,NBAST),INTENT(IN) :: EIGVEC
  DOUBLE COMPLEX,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: PDM
  TYPE(twospinor),DIMENSION(NBAST),INTENT(IN) :: PHI

  INTEGER :: I

  OPEN(42,FILE='eigenvalues.txt',STATUS='UNKNOWN',ACTION='WRITE')
  DO I=1,ITER
     WRITE(42,*)ALL_EIG(:,I)
  END DO
  CLOSE(42)
  DEALLOCATE(ALL_EIG)
  CALL EXPORT_DENSITY(UNPACK(PDM,NBAST),PHI,NBAST,-12.D0,12.D0,20,'density','matlab')
END SUBROUTINE OUTPUT_FINALIZE_relativistic

SUBROUTINE OUTPUT_FINALIZE_nonrelativistic(ITER,PDM,PHI,NBAST,EIG,EIGVEC,ETOT)
  USE basis_parameters ; USE graphics_tools ; USE matrix_tools
  IMPLICIT NONE
  INTEGER,INTENT(IN) :: ITER,NBAST
  DOUBLE PRECISION,INTENT(IN) :: ETOT
  DOUBLE PRECISION,DIMENSION(NBAST),INTENT(IN) :: EIG
  DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(IN) :: EIGVEC
  DOUBLE PRECISION,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: PDM
  TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI

  INTEGER :: I

  OPEN(42,FILE='eigenvalues.txt',STATUS='UNKNOWN',ACTION='WRITE')
  DO I=1,ITER
     WRITE(42,*)ALL_EIG(:,I)
  END DO
  CLOSE(42)
  DEALLOCATE(ALL_EIG)
  CALL EXPORT_DENSITY(UNPACK(PDM,NBAST),PHI,NBAST,-12.D0,12.D0,20,'density','matlab')
END SUBROUTINE OUTPUT_FINALIZE_nonrelativistic
END MODULE output
