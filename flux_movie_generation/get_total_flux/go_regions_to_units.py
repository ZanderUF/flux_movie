#-- Utility for gathering volumes from KENO output file
#-- AUthor: Zander Mausolff
#-- Notes: The user enters the file name they wish to get the volumes from
#--        and this program assumes the file specified is in the current directory
#-- Returns a text file called "volumes"


import re
import numpy as np

filename= raw_input("Enter the file name containing the array: ")

input_file = open(filename, 'r+')
output_file = open('volumes','w')

i=1
for line in input_file:
	if "unit  region   density     deviation      fissions" in line:
		for line in input_file:
			if "  writing fluxes to file flux.for....." in line:
				break
#			if line !=  '\n':
			output_file.write( line)
			np.array(line)			
			i+=1

