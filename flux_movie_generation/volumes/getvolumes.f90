	program getvolumes
	integer :: stat,count
	character(len=100) :: line
	character(len=100) :: orgline

	orgline="                                        unit     uses    region     mixture        total volume"
	count=0
	open(25,file="_out",status="unknown")
        open(21,file="volumes",status="unknown")
	open(22,file="ncor",status="unknown")
	do
		read(25,'(a)',iostat=stat) line
		if (  stat /= 0 ) exit
		if ( line(1:95) == orgline(1:95) ) then
			do
				read(25,'(a)',iostat=stat) line
				if (line == "" ) then
					count=count+1
					if (count > 1) exit
					cycle
				end if
				if (line(72:72) == " " ) line(72:72)="0"
				write(21,'(a)') line(80:92)
				write(22,'(a)') line(70:73)
				count=0
			end do
			if (count > 2) exit
		else
			cycle
		endif
	end do

	end program
