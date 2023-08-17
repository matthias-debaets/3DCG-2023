import java.util.List;

public class BoundingBox {
    private double minX;
    private double minY;
    private double minZ;
    private double maxX;
    private double maxY;
    private double maxZ;

    public BoundingBox(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
        this.minX = minX;
        this.minY = minY;
        this.minZ = minZ;
        this.maxX = maxX;
        this.maxY = maxY;
        this.maxZ = maxZ;
    }

    public double getMinX() {
        return minX;
    }

    public double getMinY() {
        return minY;
    }

    public double getMinZ() {
        return minZ;
    }

    public double getMaxX() {
        return maxX;
    }

    public double getMaxY() {
        return maxY;
    }

    public double getMaxZ() {
        return maxZ;
    }

    public boolean contains(Vertex vertex) {
        double x = vertex.getX();
        double y = vertex.getY();
        double z = vertex.getZ();
        return x >= minX && x <= maxX && y >= minY && y <= maxY && z >= minZ && z <= maxZ;
    }

    public boolean intersects(BoundingBox other) {
        return minX <= other.maxX && maxX >= other.minX &&
                minY <= other.maxY && maxY >= other.minY &&
                minZ <= other.maxZ && maxZ >= other.minZ;
    }

    public static BoundingBox combine(BoundingBox box1, BoundingBox box2) {
        if (box1 == null) return box2;
        if (box2 == null) return box1;

        double minX = Math.min(box1.minX, box2.minX);
        double minY = Math.min(box1.minY, box2.minY);
        double minZ = Math.min(box1.minZ, box2.minZ);
        double maxX = Math.max(box1.maxX, box2.maxX);
        double maxY = Math.max(box1.maxY, box2.maxY);
        double maxZ = Math.max(box1.maxZ, box2.maxZ);
        return new BoundingBox(minX, minY, minZ, maxX, maxY, maxZ);
    }

    public static BoundingBox createBoundingBoxNodes(List<MeshNode> nodes) {
        double minX = Double.POSITIVE_INFINITY;
        double minY = Double.POSITIVE_INFINITY;
        double minZ = Double.POSITIVE_INFINITY;
        double maxX = Double.NEGATIVE_INFINITY;
        double maxY = Double.NEGATIVE_INFINITY;
        double maxZ = Double.NEGATIVE_INFINITY;

        for (MeshNode child : nodes) {
            BoundingBox childBoundingBox = child.boundingBox;

            minX = Math.min(minX, childBoundingBox.getMinX());
            minY = Math.min(minY, childBoundingBox.getMinY());
            minZ = Math.min(minZ, childBoundingBox.getMinZ());

            maxX = Math.max(maxX, childBoundingBox.getMaxX());
            maxY = Math.max(maxY, childBoundingBox.getMaxY());
            maxZ = Math.max(maxZ, childBoundingBox.getMaxZ());
        }

        return new BoundingBox(minX, minY, minZ, maxX, maxY, maxZ);
    }

    public static BoundingBox createBoundingBoxTriangles(List<Triangle> triangles) {
        double minX = Double.POSITIVE_INFINITY;
        double minY = Double.POSITIVE_INFINITY;
        double minZ = Double.POSITIVE_INFINITY;
        double maxX = Double.NEGATIVE_INFINITY;
        double maxY = Double.NEGATIVE_INFINITY;
        double maxZ = Double.NEGATIVE_INFINITY;

        for (Triangle triangle : triangles) {
            Vertex v1 = triangle.getV1();
            Vertex v2 = triangle.getV2();
            Vertex v3 = triangle.getV3();

            minX = Math.min(minX, Math.min(v1.getX(), Math.min(v2.getX(), v3.getX())));
            minY = Math.min(minY, Math.min(v1.getY(), Math.min(v2.getY(), v3.getY())));
            minZ = Math.min(minZ, Math.min(v1.getZ(), Math.min(v2.getZ(), v3.getZ())));

            maxX = Math.max(maxX, Math.max(v1.getX(), Math.max(v2.getX(), v3.getX())));
            maxY = Math.max(maxY, Math.max(v1.getY(), Math.max(v2.getY(), v3.getY())));
            maxZ = Math.max(maxZ, Math.max(v1.getZ(), Math.max(v2.getZ(), v3.getZ())));
        }

        return new BoundingBox(minX, minY, minZ, maxX, maxY, maxZ);
    }
}