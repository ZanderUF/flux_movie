#-- Utility for gathering volumes from KENO output file
#-- AUthor: Zander Mausolff
#-- Notes: The user enters the file name they wish to get the volumes from
#--        and this program assumes the file specified is in the current directory
#-- Returns a text file called "volumes"


import re

filename= raw_input("Enter the file name containing the array: ")

input_file = open(filename, 'r+')
output_file = open('volumes','w')

i=1
for line in input_file:
	if "unit     uses    region     mixture        total region volume (cm**3)" in line:
		for line in input_file:
			if "mixture       total mixture volume (cm**3)            total mixture mass (gm)" in line:
				break
			if line !=  '\n':
				output_file.write(str(i) + line)
				i+=1
