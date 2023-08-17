public class Triangle {
    private Vertex v1, v2, v3, center;
    int iv1, iv2, iv3;

    Triangle(Vertex v1, Vertex v2, Vertex v3) {
        this.v1 = v1;
        this.v2 = v2;
        this.v3 = v3;

        this.center = this.calculateCenter();
    }

    public Vertex calculateCenter(){
        double xCenter = (this.v1.getX() + this.v2.getX() + this.v3.getX()) / 3;
        double yCenter = (this.v1.getY() + this.v2.getY() + this.v3.getY()) / 3;
        double zCenter =( this.v1.getZ() + this.v2.getZ() + this.v3.getZ()) / 3;

        return new Vertex(xCenter, yCenter, zCenter);
    }

    public Vertex[] getVertices() {
        return new Vertex[]{this.v1, this.v2, this.v3};
    }

    public Vertex getCenter() {
        return this.center;
    }

    public Vertex getV1() {
        return this.v1;
    }

    public Vertex getV2() {
        return this.v2;
    }

    public Vertex getV3() {
        return this.v3;
    }

    public void setIv1(int iv1) {
        this.iv1 = iv1;
    }

    public void setIv2(int iv2) {
        this.iv2 = iv2;
    }

    public void setIv3(int iv3) {
        this.iv3 = iv3;
    }

    public int getIv1() {
        return iv1;
    }

    public int getIv2() {
        return iv2;
    }

    public int getIv3() {
        return iv3;
    }
}
