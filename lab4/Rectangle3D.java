public class Rectangle3D {

	Vector p[] = new Vector[4];

	public Rectangle3D() {
	}

	public Rectangle3D(Vector p1, Vector p2, Vector p3, Vector p4) {
		p[0] = p1;
		p[1] = p2;
		p[2] = p3;
		p[3] = p4;
	}

	public Rectangle3D(Rectangle3D rectangle) {
		this(rectangle.p);
	}

	public Rectangle3D(Vector[] other_points) {
		for (int i = 0; i < 4; ++i) {
			p[i] = new Vector(other_points[i]);
		}
	}
}