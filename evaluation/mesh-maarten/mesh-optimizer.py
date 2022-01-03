import sys

class Vertex:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

class Triangle:
    def __init__(self, v1, v2, v3, iv1, iv2, iv3):
        #v = vertices
        self.v1 = v1
        self.v2 = v2
        self.v3 = v3
        #iv = index of vertices in the list of vertices
        self.iv1 = iv1
        self.iv2 = iv2
        self.iv3 = iv3
        #c = center of triangle
        self.c = self.center()

    def center(self):
        return Vertex((self.v1.x + self.v2.x + self.v3.x)/3, (self.v1.y + self.v2.y + self.v3.y)/3, (self.v1.z + self.v2.z + self.v3.z)/3)

def longest_axis(list):
    x_min = list[0].c.x
    x_max = list[0].c.x
    y_min = list[0].c.y
    y_max = list[0].c.y
    z_min = list[0].c.z
    z_max = list[0].c.z
    for i in range(len(list)):
        if list[i].c.x < x_min:
            x_min = list[i].c.x
        elif list[i].c.x > x_max:
            x_max = list[i].c.x
        if list[i].c.y < y_min:
            y_min = list[i].c.y
        elif list[i].c.y > y_max:
            y_max = list[i].c.y        
        if list[i].c.z < z_min:
            z_min = list[i].c.z
        elif list[i].c.z > z_max:
            z_max = list[i].c.z
    x_axis = x_max - x_min
    y_axis = y_max - y_min
    z_axis = z_max - z_min
    axis = [x_axis, y_axis, z_axis]
    if max(axis) == x_axis:
        return "x" 
    elif max(axis) == y_axis:
        return "y"
    else:
        return "z"

def write_hierarchy(list):
    #if size of list > 2: split list in 2 and repeat write_hierarchy
    if len(list) > 2:
        axis = longest_axis(list)
        if axis == "x":
            list.sort(key= lambda x: x.c.x)
        elif axis == "y":
            list.sort(key= lambda x: x.c.y)
        else:
            list.sort(key= lambda x: x.c.z)
        length = len(list)
        middle = length // 2
        l = list[:middle]
        r = list[middle:]
        write_hierarchy(l)
        write_hierarchy(r)
        optimized.write(f'b 2\n')
    #else write the triangles and size of the box
    else:
        for x in range(len(list)):
            optimized.write(f't {list[x].iv1} {list[x].iv2} {list[x].iv3}\n')
        optimized.write(f'b {len(list)}\n')

with open(sys.argv[1], 'r') as mesh:
    print("file opened")
    name = sys.argv[1].split(".")
    output = name[0] + "-optimized.mesh"
    with open(output, "w") as optimized:
        firstline = mesh.readline()
        optimized.write(firstline)
        count_vertices = int(firstline.strip().split(" ")[0])
        vertices = []
        triangles= []

        #writes all vertices and puts them in a list
        for x in range(count_vertices):
            line = mesh.readline()
            coords = line.split()

            vertices.append(Vertex(float(coords[0]), float(coords[1]), float(coords[2])))
            optimized.write(line)

        print("vertices writen")
        #puts all triangles in a list
        for line in mesh:
            l = line.split()
            if l[0] == "t":
                triangles.append(Triangle(vertices[int(l[1])], vertices[int(l[2])], vertices[int(l[3])], int(l[1]), int(l[2]), int(l[3])))
        
        print("triangles read")
        print("writing hierarchy...")
        #writes hierarchy of bounding boxes
        write_hierarchy(triangles)
        
        optimized.write("end")
        print("hierarchy writen")