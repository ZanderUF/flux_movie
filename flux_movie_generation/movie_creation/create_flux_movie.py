#!----- Read binary flux files created by KENO


import numpy as np

filename="flux.for.0"

input_file = open(filename, 'r')


array = np.fromfile(filename,dtype=float,count=-1,sep="")

with open(filename,'r') as f:
	header = np.fromfile(f, dtype=np.int, count=-1)
	data = np.fromfile(f, dtype=np.float32)
	print data
#with open(filename, 'rb') as f:
#	    data = f.read(16)
#	    text = data.decode('utf-8') 
#	    print text
i=0
#for i in array:
#	print array[i]
##	i+=1
