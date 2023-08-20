import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    private List<Vertex> vertices;
    public static void main(String[] args) throws IOException {
        String inputFilePath = "src/meshes/buddha.mesh";
        String outputFilePath = "src/meshes/buddha_optimized.mesh";

        // Read the vertices and triangles from the file and put them in seperate lists
        System.out.println("Loading mesh from file...");
        List<Vertex> vertices = readVertices(inputFilePath);
        List<Triangle> triangles = readTriangles(inputFilePath, vertices);
        System.out.println("Mesh loaded successfully!");
        // optimize the mesh
        System.out.println("Optimizing mesh...");
        // firstly, write the amount of vertices and amound of normals to the first line of the file
        // secondly, loop through the list of vertices and write the coordinates of each vertex to the file
        // thirdly, write the hierarchy of the triangles to the file
        try {
            FileWriter writer = new FileWriter(outputFilePath);
            writer.write(vertices.size() + " 0\n");
            for (int i = 0; i < vertices.size(); i++) {
                Vertex vertex = vertices.get(i);
                writer.write(vertex.getX() + " " + vertex.getY() + " " + vertex.getZ() + "\n");
            }
            writeHierarchy(triangles, writer);
            writer.write("end");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Optimized mesh written to file successfully!");
    }

    // Function to read vertices from the file
    private static List<Vertex> readVertices(String filePath) throws IOException {
        List<Vertex> vertices = new ArrayList<>();
        // regex to match a line containing 3 doubles, which are the coordinates of a vertex
        Pattern pattern = Pattern.compile("^\\s*([-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)" +
                "\\s+([-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)" +
                "\\s+([-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)\\s*$");
        // loop through the file and match each line with the regex
        Scanner scanner = new Scanner(new File(filePath));
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            Matcher matcher = pattern.matcher(line);
            // if the line matches the regex, create a new vertex and add it to the list of vertices
            if (matcher.matches()) {
                double x = Double.parseDouble(matcher.group(1));
                double y = Double.parseDouble(matcher.group(3));
                double z = Double.parseDouble(matcher.group(5));
                vertices.add(new Vertex(x, y, z));
            }
        }
        return vertices;
    }

    // Function to read triangles from the file
    private static List<Triangle> readTriangles(String inputPath, List<Vertex> vertices) throws IOException {
        Scanner scanner = new Scanner(new File(inputPath));
        List<Triangle> triangles = new ArrayList<>();
        // loop through the file and search for lines that contain the character 't', which indicates a triangle
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.contains("t")) {
                String[] indices = line.substring(2).trim().split(" ");
                // v1, v2 and v3 are the indices of the vertices that make up the triangle
                int v1 = Integer.parseInt(indices[0]);
                int v2 = Integer.parseInt(indices[1]);
                int v3 = Integer.parseInt(indices[2]);
                // to create a triangle, we need the coordinates of the vertices that make up the triangle, which we can get from the list of vertices
                Triangle t = new Triangle(vertices.get(v1), vertices.get(v2), vertices.get(v3));
                // we need to save the indices of the vertices that make up the triangle, so we can write them to the file later. Next, we add the triangle to the list of triangles
                t.setIv1(v1);
                t.setIv2(v2);
                t.setIv3(v3);
                triangles.add(t);
            }
        }
        return triangles;
    }

    // Function to calculate the lengths of the bounding box along the x, y and z axis. Returns the axis with the longest length.
    private static String longestDistance(List<Triangle> triangles) {
        // initialize the min and max values of the x, y and z axis with the coordinates of the first triangle
        double xMin = triangles.get(0).getCenter().getX();
        double xMax = triangles.get(0).getCenter().getX();
        double yMin = triangles.get(0).getCenter().getY();
        double yMax = triangles.get(0).getCenter().getY();
        double zMin = triangles.get(0).getCenter().getZ();
        double zMax = triangles.get(0).getCenter().getZ();

        // loop through the list of triangles and update the min and max values of the x, y and z axis if necessary
        for (Triangle triangle : triangles) {
            if (triangle.getCenter().getX() < xMin) {
                xMin = triangle.getCenter().getX();
            }
            if (triangle.getCenter().getX() > xMax) {
                xMax = triangle.getCenter().getX();
            }
            if (triangle.getCenter().getY() < yMin) {
                yMin = triangle.getCenter().getY();
            }
            if (triangle.getCenter().getY() > yMax) {
                yMax = triangle.getCenter().getY();
            }
            if (triangle.getCenter().getZ() < zMin) {
                zMin = triangle.getCenter().getZ();
            }
            if (triangle.getCenter().getZ() > zMax) {
                zMax = triangle.getCenter().getZ();
            }
        }
        // calculate the length of the bounding box along the x, y and z axis
        double xAxis = Math.abs(xMax - xMin);
        double yAxis = Math.abs(yMax - yMin);
        double zAxis = Math.abs(zMax - zMin);
        // return the axis with the longest length
        if (xAxis >= yAxis && xAxis >= zAxis) {
            return "x";
        } else if (yAxis >= xAxis && yAxis >= zAxis) {
            return "y";
        } else {
            return "z";
        }
    }

    // Function to write the hierarchy to the file
    private static void writeHierarchy(List<Triangle> triangles, FileWriter writer) throws IOException {
        // As long as the size of the list of triangles is greater than 2, we calculate the longest axis of the bounding box and sort the list of triangles along that axis.
        if (triangles.size() > 2) {
            // calculate the longest axis of the bounding box
            String axis = longestDistance(triangles);
            // sort the list of triangles along the longest axis of the bounding box
            if (axis.equals("x")) {
                triangles.sort(Comparator.comparingDouble(t -> t.getCenter().getX()));
            } else if (axis.equals("y")) {
                triangles.sort(Comparator.comparingDouble(t -> t.getCenter().getY()));
            } else {
                triangles.sort(Comparator.comparingDouble(t -> t.getCenter().getZ()));
            }
            // split the list of triangles in two halves and recursively call the function for each half
            int size = triangles.size();
            int half = size / 2;
            List<Triangle> left = triangles.subList(0, half);
            List<Triangle> right = triangles.subList(half, size);
            writeHierarchy(left, writer);
            writeHierarchy(right, writer);
            // write the bounding box to the file, this bounding box always contains 2 other bounding boxes, which can each contain 2 other bounding boxes, etc.
            writer.write("b " + 2 + "\n");
        } else {
            // if the size of the list of triangles is less than or equal to 2, we write the triangles to the file
            for (Triangle triangle : triangles) {
                writer.write("t " + triangle.getIv1() + " " + triangle.getIv2() + " " + triangle.getIv3() + "\n");
            }
            // After writing the triangles to the file, we write the bounding box to the file. This bounding box contains the number of triangles in the list of triangles, which represents the triangles in the bounding box
            writer.write("b " + triangles.size() + "\n");
        }
    }
}