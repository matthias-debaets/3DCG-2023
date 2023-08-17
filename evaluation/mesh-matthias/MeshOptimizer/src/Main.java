import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    private List<Vertex> vertices;
    public static void main(String[] args) throws IOException {
        // Replace "input_file.txt" with the actual file path of your input mesh file
        String inputFilePath = "src/meshes/lucy.mesh";
        String outputFilePath = "src/meshes/lucy_optimized.mesh";

        // Read the mesh from file and get the root of the hierarchy
        System.out.println("Loading mesh from file...");
        List<Vertex> vertices = readVertices(inputFilePath);
        List<Triangle> triangles = readTriangles(inputFilePath, vertices);
        System.out.println("Mesh loaded successfully!");
        // optimize the mesh
        System.out.println("Optimizing mesh...");
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
        Pattern pattern = Pattern.compile("^\\s*([-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)" +
                "\\s+([-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)" +
                "\\s+([-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)\\s*$");

        Scanner scanner = new Scanner(new File(filePath));
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            Matcher matcher = pattern.matcher(line);
            if (matcher.matches()) {
                double x = Double.parseDouble(matcher.group(1));
                double y = Double.parseDouble(matcher.group(3));
                double z = Double.parseDouble(matcher.group(5));
                vertices.add(new Vertex(x, y, z));
            }
        }
        return vertices;
    }

    private static List<Triangle> readTriangles(String inputPath, List<Vertex> vertices) throws IOException {
        Scanner scanner = new Scanner(new File(inputPath));
        List<Triangle> triangles = new ArrayList<>();

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.contains("t")) {
                String[] indices = line.substring(2).trim().split(" ");
                int v1 = Integer.parseInt(indices[0]);
                int v2 = Integer.parseInt(indices[1]);
                int v3 = Integer.parseInt(indices[2]);
                Triangle t = new Triangle(vertices.get(v1), vertices.get(v2), vertices.get(v3));
                t.setIv1(v1);
                t.setIv2(v2);
                t.setIv3(v3);
                triangles.add(t);
            }
        }
        return triangles;
    }

    private static String longestDistance(List<Triangle> triangles) {
        double xMin = triangles.get(0).getCenter().getX();
        double xMax = triangles.get(0).getCenter().getX();
        double yMin = triangles.get(0).getCenter().getY();
        double yMax = triangles.get(0).getCenter().getY();
        double zMin = triangles.get(0).getCenter().getZ();
        double zMax = triangles.get(0).getCenter().getZ();

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

        double xAxis = Math.abs(xMax - xMin);
        double yAxis = Math.abs(yMax - yMin);
        double zAxis = Math.abs(zMax - zMin);

        if (xAxis >= yAxis && xAxis >= zAxis) {
            return "x";
        } else if (yAxis >= xAxis && yAxis >= zAxis) {
            return "y";
        } else {
            return "z";
        }
    }

    private static void writeHierarchy(List<Triangle> triangles, FileWriter writer) throws IOException {
        if (triangles.size() > 2) {
            String axis = longestDistance(triangles);
            if (axis.equals("x")) {
                triangles.sort(Comparator.comparingDouble(t -> t.getCenter().getX()));
            } else if (axis.equals("y")) {
                triangles.sort(Comparator.comparingDouble(t -> t.getCenter().getY()));
            } else {
                triangles.sort(Comparator.comparingDouble(t -> t.getCenter().getZ()));
            }

            int size = triangles.size();
            int half = size / 2;
            List<Triangle> left = triangles.subList(0, half);
            List<Triangle> right = triangles.subList(half, size);
            writeHierarchy(left, writer);
            writeHierarchy(right, writer);
            writer.write("b " + 2 + "\n");
        } else {
            for (Triangle triangle : triangles) {
                writer.write("t " + triangle.getIv1() + " " + triangle.getIv2() + " " + triangle.getIv3() + "\n");
            }
            writer.write("b " + triangles.size() + "\n");
        }
    }
}