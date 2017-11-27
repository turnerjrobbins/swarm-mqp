#Created by Mathew Schwartzman on 27 November 2017

import numpy as np
from scipy import misc
import matplotlib.pyplot as plt


rows = 5
cols = 5

#########-------TEST ARRAYS------#######
a = np.array([[1,0,0,0,0],
			  [0,0,0,0,0],
			  [0,0,0,1,0],
			  [0,0,1,2,1],
			  [0,0,0,1,0]])

b = np.array([[0,0,0,0,0],
			  [0,0,1,0,0],
			  [0,1,2,1,0],
			  [0,0,1,0,0],
			  [0,0,0,0,0]])

c = np.array([[0,0,0,0,0],
			  [0,0,1,0,0],
			  [0,1,2,1,0],
			  [0,0,1,0,0],
			  [0,0,0,0,0]])

def scalarDelta(matrix1, matrix2):	#simple similarity function that returns the absolute scalar differences between cell values
	deltaMatrix = matrix1 - matrix2
	deltaScalar = 0
	for el in deltaMatrix.flatten():
		deltaScalar = deltaScalar + abs(el)
	return deltaScalar

def translateUpOne(array):
	d = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	array_flat = array.flatten()	#flatten the input array
	for el in range(cols, (rows*cols)):	#start on second row
		np.put(d, el-cols, array_flat[el])	#put all the elements up in the new array d
	return d

def translateUp(distance, array):
	d = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	array_flat = array.flatten()	#flatten the input array
	for el in range(cols*distance, (rows*cols)):	#start on second row
		np.put(d, el-cols*distance, array_flat[el])	#put all the elements up in the new array d
	return d

print a
print b
print c
print scalarDelta(a,b)
print translateUp(1, c)

