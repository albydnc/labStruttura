import csv
picchi = []
for i in range(3648):
    picchi.append([i,0])
for j in range(375,1000,25):
    temp = list(csv.reader(open('picco'+str(j)+'.txt', 'r'), delimiter='\t'))
    mi=int((j-375)/0.216)
    print(mi)
    for i in range(mi,mi+500):
        if(picchi[i][1] < float(temp[i][1])):
            picchi[i][1] = float(temp[i][1])
with open("output.txt", "w") as f:
    writer = csv.writer(f,delimiter ='\t')
    writer.writerows(picchi)
