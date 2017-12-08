#-----------------------#
#			#
#	gridMerge	#
#			#
#-----------------------#

Transformation class stores an array x and a scalar delta of the transformed array from the compared array

createTransList takes in an array still and a compared array shake and creates a list of Transformation objects around a distance radius from the center of the target arrays

createRotList takes in an array still and a compared array shimmy and tilts shimmy an angle tilt (multiples of 10 degrees) to create rotations Transformation objects

simpleDelta subtracts matrix2 from matrix 1 and counts the scalar differences in each element, returning that count

translateUpOne is the original translation function, simply translating the given array up by one grid cell

translateUp is a generalized translation function for translating a target_array in the positive y-direction a distance (gridcells)

translateDown is a generalized translation function for translating target_array down a distance (gridcells)


