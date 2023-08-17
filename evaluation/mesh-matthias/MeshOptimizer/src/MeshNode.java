import java.util.Comparator;
import java.util.List;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MeshNode {
    public BoundingBox boundingBox;
    List<Triangle> triangles;
    List<MeshNode> children;
    MeshNode parent;

    MeshNode() {
        this.triangles = new ArrayList<>();
        this.children = new ArrayList<>();
        this.boundingBox = null;
        this.parent = null;
    }

    MeshNode(List<Triangle> triangles) {
        this.triangles = triangles;
        this.children = new ArrayList<>();
        this.boundingBox = null;
        this.parent = null;
    }

   public int countTriangles() {
        int count = triangles.size();
        for (MeshNode child : children) {
            count += child.countTriangles();
        }
        return count;
   }

   public List<Vertex> getVertices() {
        List<Vertex> vertices = new ArrayList<>();
        for (Triangle triangle : triangles) {
            vertices.add(triangle.getV1());
            vertices.add(triangle.getV2());
            vertices.add(triangle.getV3());
        }
        for (MeshNode child : children) {
            vertices.addAll(child.getVertices());
        }
        return vertices;
   }
}
