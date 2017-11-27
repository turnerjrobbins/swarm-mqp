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

def translateUp(distance, target_array):	#distance is given in cells
	d = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	array_flat = target_array.flatten()	#flatten the input array
	for el in range(cols*distance, (rows*cols)):	#start on second row
		np.put(d, el-cols*distance, array_flat[el])	#put all the elements up in the new array d
	return d

def translateDown(distance, target_array):
	d = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	array_flat = target_array.flatten()	#flatten the input array
	for el in range((rows*cols - cols), -1, -1):
		np.put(d, (el+cols*distance)-1, array_flat[el-1])
		#print el
	return d

def translateRight(distance, target_array):
	d = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	target_array = np.rot90(target_array)
	array_flat = target_array.flatten()	#flatten the input array
	for el in range(cols*distance, (rows*cols)):	#start on second row
		np.put(d, el-cols*distance, array_flat[el])	#put all the elements up in the new array d
		#print el
	d = np.rot90(d)
	d = np.rot90(d)
	d = np.rot90(d)
	return d

def translateLeft(distance, target_array):
	d = np.zeros(rows*cols).reshape(rows, cols)	#create an array of zeros
	target_array = np.rot90(target_array)
	target_array = np.rot90(target_array)
	target_array = np.rot90(target_array)

	array_flat = target_array.flatten()	#flatten the input array
	for el in range(cols*distance, (rows*cols)):	#start on second row
		np.put(d, el-cols*distance, array_flat[el])	#put all the elements up in the new array d
		#print el
	d = np.rot90(d)
	# d = np.rot90(d)
	# d = np.rot90(d)
	return d




print a
print b
print c
print scalarDelta(a,b)
print translateUp(1, c)
print translateDown(1, c)
print translateRight(1, c)
print translateLeft(2, c)