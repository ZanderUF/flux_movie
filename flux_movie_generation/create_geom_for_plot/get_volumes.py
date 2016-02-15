#-- Utility for gathering volumes from KENO output file
#-- AUthor: Zander Mausolff
#-- Notes: The user enters the file name they wish to get the volumes from
#--        and this program assumes the file specified is in the current directory
#-- Returns a text file called "volumes"


import re

filename= raw_input("Enter the file name containing volumes info: ")

input_file = open(filename, 'r+')
output_file = open('volumes','w')

i=1
for line in input_file:
	if "unit     uses    region     mixture        total region volume (cm**3)" in line:
		for line in input_file:
			if "mixture       total mixture volume (cm**3)            total mixture mass (gm)" in line:
				break
			if line !=  '\n':
#				if line[28]==" ":
#					line[28] == "0"
#				if line[37]== " ":
#					line[37] == "0"
			#	if line[57] == " ":
			#		line[57] == "0"
			#	if line[69] == " ":
			#		line[69] == "0"
				print line[1]
		#		str(line)
				" ".join(str(line).split())
				output_file.write(str(i) + line)
				i+=1
