program create_movie
!--- Author: Zander Mausolff ---!
!--- Purpose:  Generate flux movie by reading flux.for.x files
!--- 

!---dummy


implicit none
!------------Variables---------------!
integer ::  engp,incr,stgp,stat,k,kmax,ngp,iflux
real :: time,klgkeff
character(10) :: datafilename
real  :: flux_array(44,238)
character(len=100) :: line

iflux = 10
datafilename = "flux.for.0"

        open(iflux,file=datafilename,status='unknown',form='unformatted')
        read(iflux) kmax,ngp
        read(iflux) time,klgkeff
        print *, kmax,ngp
        print *,time,klgkeff

        do k=1,kmax
            read(iflux) flux_array(k,1),ngp,engp,incr  
            print *, flux_array(k,1),ngp,engp,incr 
        end do

end program
