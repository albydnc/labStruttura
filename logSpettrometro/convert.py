import csv
picchi = []
for i in range(3649):
    picchi.append([i,0])
for j in range(375,1000,25):
    j=375
    temp = list(csv.reader(open('picco'+str(j)+'.txt', 'r'), delimiter='\t'))
    for i in range(3649):

        if(picchi[i][1] < float(temp[i][1])):
            print(temp[i][1])
            picchi[i][1] = float(temp[i][1])
with open("output.txt", "w") as f:
    writer = csv.writer(f,delimiter ='\t')
    writer.writerows(picchi)
