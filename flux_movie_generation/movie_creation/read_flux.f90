program create_movie
!--- Author: Zander Mausolff ---!
!--- Purpose:  Generate flux movie by reading flux.for.x files
!--- 

!---dummy


implicit none
!------------Variables---------------!
integer ::  ig,engp,incr,stgp,stat,k,kmax,ngp,iflux
real :: time,klgkeff
character(10) :: datafilename
real  :: flux_array(44,238), tot_flux_ar(44)
character(len=100) :: line

iflux = 10
datafilename = "flux.for.0"

        open(iflux,file=datafilename,status='unknown',form='unformatted')
        read(iflux) kmax,ngp
        read(iflux) time,klgkeff
        print *, kmax,ngp
        print *,time,klgkeff
        tot_flux_ar(k) = 0.0
        flux_array(k,ig) = 0.0
        ngp = 238
        kmax = 44
        
        do k=1,kmax
            read(iflux) flux_array(k,1:ngp)
            do ig=1,ngp
                tot_flux_ar(k) = flux_array(k,ig) + tot_flux_ar(k)
            end do
        end do
        
        do k=1,kmax
                print *, tot_flux_ar(k)
        end do
!---loop over  and add all flux valus for a given region-!
        

end program
