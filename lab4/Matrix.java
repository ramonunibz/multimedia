public class Matrix {

    double[][] elements = new double[][]{
            {1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}
    };

    public Matrix() {
    }

    public Matrix(double[][] matrix) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                elements[i][j] = matrix[i][j];
            }
        }
    }

    public Matrix(Matrix matrix) {
        this(matrix.elements);
    }

    public Matrix mult(Matrix matrix) {
        Matrix result = new Matrix();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.elements[i][j] = 0.0;
                for (int k = 0; k < 4; ++k) {
                    result.elements[i][j] += elements[i][k] * matrix.elements[k][j];
                }
            }
        }
        return result;
    }

    public Vector mult(Vector vector) {
        Vector result = new Vector(vector.elements);
        if (vector.elements.length == 4) {
            for (int i = 0; i < 4; ++i) {
                result.elements[i] = 0.0;
                for (int j = 0; j < 4; ++j) {
                    result.elements[i] += vector.elements[j] * elements[i][j];
                }
            }
        } else {
            for (int i = 0; i < 3; ++i) {
                result.elements[i] = 0.0;
                for (int j = 0; j < 3; ++j) {
                    result.elements[i] += vector.elements[j] * elements[i][j];
                }
                result.elements[i] += elements[i][3];
            }
            double w = 0.0;
            for (int j = 0; j < 3; ++j) {
                w += vector.elements[j] * elements[3][j];
            }
            w += elements[3][3];
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

    public String toString() {
        StringBuffer result = new StringBuffer("Matrix: {\n");
        for (int i = 0; i < 4; ++i) {
            result.append("  {");
            for (int j = 0; j < 4; ++j) {
                result.append(elements[i][j]);
                if (j < 3) {
                    result.append(", ");
                }
            }
            result.append('}');
            if (i < 3) {
                result.append(',');
            }
            result.append('\n');
        }
        result.append("}\n");
        return result.toString();
    }

    public void printMatrix() {
        System.out.print(toString());
    }

    public void setIdentity() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    elements[i][j] = 1;
                } else {
                    elements[i][j] = 0;
                }
            }
        }
    }

    public void setTranslation(int x, int y, int z) {
        setIdentity();
        elements[0][3] = x;
        elements[1][3] = y;
        elements[2][3] = z;
    }

    public void setScale(double scale) {
        setIdentity();
        elements[0][0] = scale;
        elements[1][1] = scale;
    }

    public void setRotationXAxis(double angle){
        setIdentity();
        elements[1][1] = Math.cos(angle);
        elements[1][2] = -Math.sin(angle);
        elements[2][1] = Math.sin(angle);
        elements[2][2] = Math.cos(angle);
    }

    public void setRotationYAxis(double angle){
        setIdentity();
        elements[0][0] = Math.cos(angle);
        elements[2][0] = -Math.sin(angle);
        elements[0][2] = Math.sin(angle);
        elements[2][2] = Math.cos(angle);
    }

    public void setRotationZAxis(double angle){
        setIdentity();
        elements[0][0] = Math.cos(angle);
        elements[0][1] = -Math.sin(angle);
        elements[1][0] = Math.sin(angle);
        elements[1][1] = Math.cos(angle);
    }

    public void setOrtho() {
        setIdentity();
        elements[2][2] = 0;
        printMatrix();
    }

    public void setFrustum(int d) {
        setIdentity();
        elements[2][2] = 0;
        elements[3][2] = (double) 1/d;
    }
}
