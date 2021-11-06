import java.awt.*;

public class Simple3DCanvas extends Canvas {

    private static final long serialVersionUID = 1L;
    private Rectangle3D rectangle;

    private Matrix model = new Matrix();
    private Matrix view = new Matrix();
    private Matrix project = new Matrix();
    private Color color = Color.BLACK;

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public Simple3DCanvas() {
        rectangle = new Rectangle3D(new Vector(100.0, 100.0, 0.0),
                new Vector(-100.0, 100.0, 0.0),
                new Vector(-100.0, -100.0, 0.0),
                new Vector(100.0, -100.0, 0.0));
    }

    public void paint(Graphics g) {
        int polygonX[] = new int[4];
        int polygonY[] = new int[4];

        Vector v;

        for (int i = 0; i < 4; ++i) {
            v = rectangle.p[i];
            v = model.mult(v);
            v = view.mult(v);
            v = project.mult(v);
            polygonX[i] = (int) (getSize().width / 2.0 + v.elements[0]);
            polygonY[i] = (int) (getSize().height / 2.0 + v.elements[1]);
        }
        g.setColor(color);
        g.fillPolygon(polygonX, polygonY, 4);
    }

    public void multiplyMatrix(Matrix matrix) {
        model = matrix.mult(model);
        System.out.println(model.toString());
    }

    public void setMatrix(Matrix matrix) {
        model = matrix;
        System.out.println(model.toString());
    }
}