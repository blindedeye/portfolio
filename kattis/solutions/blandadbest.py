n=int(input())
i=0
slist = []
while i<n:
    slist.append(input())
    i+=1
if n>1:
    if slist[0] == "nautakjot" and slist[1] == "kjuklingur":
        print("blandad best")
    elif slist[0] == "kjuklingur" and slist[1] == "nautakjot":
        print("blandad best")
else:
    print(slist[0])