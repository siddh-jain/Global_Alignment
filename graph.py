import matplotlib.pyplot as plt


# Using readlines()
file1 = open('input.txt', 'r')
Lines = file1.readlines()
 
x=[]
y=[]
count = 0
# Strips the newline character
for line in Lines:
    line.strip()
    t = line.split()
    y.append(float(t[0]))
    x.append(float(t[1]))


plt.xlabel('Tile Length')
plt.ylabel('Compute Time')

plt.plot(x,y)
plt.show()