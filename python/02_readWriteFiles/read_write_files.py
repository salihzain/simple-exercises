# read existing file
ds = open('ds.txt')

# create new file
ds_new = open('ds_new.txt', 'w')

while True:
    line = ds.readline().replace("\n","")
    # EOF
    if len(line) == 0:
        break
    items = line.split(",")
    x = float(items[0])
    y = float(items[1])
    z = float(items[2])
    print("x:{} y:{} z:{}".format(x, y, z))
    ds_new.write("x:{} y:{} z:{}\n".format(x, y, z))


ds.close()
ds_new.close()

