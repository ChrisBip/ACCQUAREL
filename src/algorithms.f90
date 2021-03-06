MODULE scf_algorithms

INTERFACE DIIS
  SUBROUTINE DIIS_relativistic(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(INOUT) :: EIG
    DOUBLE COMPLEX,DIMENSION(NBAST,NBAST),INTENT(INOUT) :: EIGVEC
    DOUBLE COMPLEX,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(twospinor),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE

  SUBROUTINE DIIS_RHF(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(INOUT) :: EIG
    DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(INOUT) :: EIGVEC
    DOUBLE PRECISION,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE
END INTERFACE

INTERFACE LEVELSHIFTING
  SUBROUTINE LEVELSHIFTING_relativistic(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(OUT) :: EIG
    DOUBLE COMPLEX,DIMENSION(NBAST,NBAST),INTENT(OUT) :: EIGVEC
    DOUBLE COMPLEX,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(twospinor),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE

  SUBROUTINE LEVELSHIFTING_RHF(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(OUT) :: EIG
    DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(OUT) :: EIGVEC
    DOUBLE PRECISION,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE
END INTERFACE

INTERFACE ODA
  SUBROUTINE ODA_RHF(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(OUT) :: EIG
    DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(OUT) :: EIGVEC
    DOUBLE PRECISION,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE
END INTERFACE

INTERFACE ROOTHAAN
  SUBROUTINE ROOTHAAN_relativistic(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(OUT) :: EIG
    DOUBLE COMPLEX,DIMENSION(NBAST,NBAST),INTENT(OUT) :: EIGVEC
    DOUBLE COMPLEX,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(twospinor),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE

  SUBROUTINE ROOTHAAN_RHF(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(OUT) :: EIG
    DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(OUT) :: EIGVEC
    DOUBLE PRECISION,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE
END INTERFACE

INTERFACE GRADIENT
  SUBROUTINE GRADIENT_relativistic(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(OUT) :: EIG
    DOUBLE COMPLEX,DIMENSION(NBAST,NBAST),INTENT(OUT) :: EIGVEC
    DOUBLE COMPLEX,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(twospinor),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE
  SUBROUTINE GRADIENT_RHF(EIG,EIGVEC,NBAST,POEFM,PHI,TRSHLD,MAXITR,RESUME)
    USE basis_parameters
    INTEGER,INTENT(IN) :: NBAST
    DOUBLE PRECISION,DIMENSION(NBAST),INTENT(OUT) :: EIG
    DOUBLE PRECISION,DIMENSION(NBAST,NBAST),INTENT(OUT) :: EIGVEC
    DOUBLE PRECISION,DIMENSION(NBAST*(NBAST+1)/2),INTENT(IN) :: POEFM
    TYPE(gaussianbasisfunction),DIMENSION(NBAST),INTENT(IN) :: PHI
    DOUBLE PRECISION,INTENT(IN) :: TRSHLD
    INTEGER,INTENT(IN) :: MAXITR
    LOGICAL,INTENT(IN) :: RESUME
  END SUBROUTINE
END INTERFACE
END MODULE scf_algorithms
