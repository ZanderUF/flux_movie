#!----- Read binary flux files created by KENO


import numpy as np

file="flux.for.0"

array = np.fromfile(file,dtype=float,count=-1,sep="")
print len(array) 
print array[0]


