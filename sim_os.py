import os
import numpy as np
import random

s1 = 15
s2 = 10

wt = np.ones(s1*s2+s2) * 0.1

wfile = open("weight.txt","w")
for i in range(s1*s2+s2):
	wfile.write(str(wt[i]))
	wfile.write(" ")
wfile.close()

selected = []
cost = []

for i in range(1500):

	print("current runs: %d" % i)

	cmd = "./CBSH2 -m instances/lak503d.map -a instances/lak503dmap-100agents-5.agents -o test.csv -t 60 -s 1 -h WDG -r 1"

	os.system(cmd)

	rfile = open("record.txt","r")
	temp = int(rfile.read())
	print(temp)
	selected.append(temp)
	rfile.close()

	rfile2 = open("cost.txt","r")
	temp = int(rfile2.read())
	cost.append(temp)
	rfile2.close()


wfile = open("final_result.txt", "w")
for i in range(len(selected)):
	wfile.write("%d " % cost[i])
	wfile.write("%d\n" % selected[i])
wfile.close()



# 19 213 2
# 27 353 5
# 31 125 7