public class Vector {
	
	double[] elements = new double[] {0.0, 0.0, 0.0, 1.0};

	public Vector() {
	}

	public Vector(double x, double y, double z) {
		elements[0] = x;
		elements[1] = y;
		elements[2] = z;
	}
	
	public Vector(double[] vector) {
		if (vector.length == 3) {
			elements = new double[3];
		}	
		for (int i = 0; i < elements.length; ++i) {
			elements[i] = vector[i];
		}
	}

	public Vector(Vector vector) {
		this(vector.elements);
	}

	public double getX() {
		return elements[0];
	}

	public double getY() {
		return elements[1];
	}

	public double getZ() {
		return elements[2];
	}

	public Vector mult(Matrix matrix) {
		Vector result = new Vector(elements);
		if (elements.length == 4) {
			for (int i = 0; i < 4; ++i) {
				result.elements[i] = 0.0;
				for (int j = 0; j < 4; ++j) {
					result.elements[i] += elements[j] * matrix.elements[i][j];
				}
			}
		} else {
			for (int i = 0; i < 3; ++i) {
				result.elements[i] = 0.0;
				for (int j = 0; j < 3; ++j) {
					result.elements[i] += elements[j] * matrix.elements[i][j];
				}
				result.elements[i] += matrix.elements[i][3];
			}
			double w = 0.0;
			for (int j = 0; j < 3; ++j) {
				w += elements[j] * matrix.elements[3][j];
			}
			w += matrix.elements[3][3];
			if (w == 0.0) {
				return null;
			}
		}	
		double divW = 1.0 / result.elements[3];
		for (int i = 0; i < 3; ++i) {
			result.elements[i] *= divW;
		}
		return result;
	}


	public double dot (Vector vector) {
		return elements[0] * vector.elements[0] +
			   elements[1] * vector.elements[1] +
			   elements[2] * vector.elements[2];
	}

	public Vector cross (Vector vector) {
		Vector result = new Vector();
		result.elements[0] = vector.elements[2] * elements[1] -	vector.elements[1] * elements[2];
		result.elements[1] = vector.elements[0] * elements[2] -	vector.elements[2] * elements[0];
		result.elements[2] = vector.elements[1] * elements[0] - vector.elements[0] * elements[1];	
		return result;
	}

	public double length () {
		return Math.sqrt(elements[0] * elements[0] +
						 elements[1] * elements[1] +
						 elements[2] * elements[2]);
	}

	public String toString() {	
		StringBuffer result = new StringBuffer("Vector: {");
		for (int i = 0; i < 4; ++i) {
			result.append(elements[i]);
			if (i < 3) {
				result.append(", ");
			}
		}
		result.append("}\n");
		return result.toString();
	}

	public void printVector() {
		System.out.print(toString());
	}
}
