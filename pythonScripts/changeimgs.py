# with is like your try .. finally block in this case
#filename = 'scene00067.txt'

# numbertxt = filename.split('ne')
# number = numbertxt[1].split('.')
# numberint = int(number[0])

# print number[0]
# print str(numberint)

for n in range(67, 679):
	filename = 'scene' + str(n).zfill(5) + '.txt'
	print filename

	with open(filename, 'r') as file:
	    # read a list of lines into data
	    data = file.readlines()
	#print data
	#print "old" + data[0]
	#oldData = data[2] #string
	#print 'data'
	#print data

	if len(data) > 2:

		oldData = data[2]
		datalist = data[2].split(" ")

		#print 'datalist'
		#print datalist

		finaldata = '2 ' + datalist[1] + ' ' + datalist[2] +  ' '  + datalist[3] + ' ' + datalist[4] + '\n'

		print oldData
		print finaldata

		#data[2] = finaldata
		# now change the 2nd line, note that you have to add a newline
		# and write everything back
		with open(filename, 'w') as file:
		    file.writelines( data )

		finaldata = ''


