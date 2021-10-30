import java.awt.Graphics;
import java.awt.Point;
import java.util.LinkedList;

import javax.swing.JComponent;

public class BresenhamCanvas extends JComponent {
    private static final long serialVersionUID = 1L;

    private int columns;
    private int rows;

    private static int griDotRadius = 5;
    private static int dotRadius = 20;

    private LinkedList<Point> points = new LinkedList<Point>();

    public BresenhamCanvas(int columns, int rows) {
        this.columns = columns;
        this.rows = rows;
    }

    // Repaints the canvas
    public void paint(Graphics g) {
        int width = getWidth();
        int length = getHeight();
        g.clearRect(0, 0, width, length);
        drawGrid(g);
        drawLine(g, 12, 15, 0, 4);
        drawLine(g, 0, 4, 12, 11);
        drawLine(g, 12, 11, 15, 0);
        drawLine(g, 15, 0, 18, 11);
        drawLine(g, 18, 11, 29, 4);
        drawLine(g, 29, 4, 18, 15);
        drawLine(g, 18, 15, 25, 29);
        drawLine(g, 25, 29, 15, 17);
        drawLine(g, 15, 17, 5, 29);
        drawLine(g, 5, 29, 12, 15);
        drawCircle(g, 15,15,14);
        // 1. Clears background
        // 2. Draws grid
        // 3. Draws all stored points, calls drawDot(...)
    }

    // Adds a point to internal point list
    public void addPoint(int gridX, int gridY) {

    }

    // Draws the grid. Calls drawGridDot for each grid point
    private void drawGrid(Graphics g) {
        for (int i = 1; i <= columns; i++) {
            for (int j = 1; j <= rows; j++) {
                drawGridDot(g, i, j);
            }
        }
    }

    // Draws a single grid point
    // Encapsulates the conversion of grid coordinates (e.g. 2/2) into pixel coordinates (e.g. 125/125)
    private void drawGridDot(Graphics g, int gridX, int gridY) {
        int xPos = (int) getWidth() / (columns + 1) * gridX - griDotRadius / 2;
        int yPos = (int) getHeight() / (rows + 1) * gridY - griDotRadius / 2;
        g.fillOval(xPos, yPos, griDotRadius, griDotRadius);
    }

    // Draws a single point (heavy dot) onto the canvas
    // Encapsulates the conversion of grid coordinates (e.g. 2/2) into pixel coordinates (e.g. 125/125)
    private void drawDot(Graphics g, int gridX, int gridY) {
        int xPos = (int) getWidth() / (columns + 1) * gridX - dotRadius / 2;
        int yPos = (int) getHeight() / (rows + 1) * gridY - dotRadius / 2;
        g.fillOval(xPos, yPos, dotRadius, dotRadius);
    }

    public void drawLine(Graphics g, int x1, int y1, int x2, int y2) {
        int dx = x2 - x1;
        int dy = y2 - y1;
        if (dx >= dy && dx >= 0 && dy >= 0) {
            drawLine1(g, x1, y1, x2, dx, dy);
        } else if (dx >= 0 && dy >= 0) {
            drawLine2(g, x1, y1, y2, dx, dy);
        } else if (dy >= 0 && (dx * (-1) >= dy)) {
            drawLine3(g, x1, y1, x2, dx, dy);
        } else if (dy >= 0 && (dx * (-1) <= dy)) {
            drawLine4(g, x1, y1, y2, dx, dy);
        } else if (dy < 0 && dx > 0 && dx >= (-dy)) {
            drawLine5(g, x1, y1, x2, dx, dy);
        } else if (dy < 0 && dx > 0 && dx <= (-dy)) {
            drawLine6(g, x1, y1, y2, dx, dy);
        } else if (dx < dy && dx * (-1) >= 0 && dy < 0) {
            drawLine7(g, x1, y1, x2, dx, dy);
        } else if (dx <= 0 && dy <= 0) {
            drawLine8(g, x1, y1, y2, dx, dy);
        }
    }

    public void drawLine1(Graphics g, int x1, int y1, int x2, int dx, int dy) {     //1&7
        int d = 2 * dy - dx;
        int incrE = 2 * dy;
        int incrNE = 2 * (dy - dx);
        drawDot(g, x1 + 1, y1 + 1);
        int y = y1;
        for (int x = x1 + 1; x <= x2; x++) {
            if (d <= 0) {
                d = d + incrE;
            } else {
                d = d + incrNE;
                y++;
            }
            drawDot(g, x + 1, y + 1);
        }
    }

    public void drawLine2(Graphics g, int x1, int y1, int y2, int dx, int dy) {     //2&8
        int d = 2 * dx - dy;
        int incrN = 2 * dx;
        int incrNE = 2 * (dx - dy);
        drawDot(g, x1 + 1, y1 + 1);
        int x = x1;
        for (int y = y1 + 1; y <= y2; y++) {
            if (d <= 0) {
                d = d + incrN;
            } else {
                d = d + incrNE;
                x++;
            }
            drawDot(g, x + 1, y + 1);
        }
    }

    public void drawLine3(Graphics g, int x1, int y1, int x2, int dx, int dy) {     //3&5
        int d = 2 * dy + dx;
        int incrW = 2 * dy;
        int incrNW = 2 * (dy + dx);
        drawDot(g, x1 + 1, ++y1);
        int y = y1;
        for (int x = x1; x > x2; x--) {
            if (d <= 0) {
                d = d + incrW;
            } else {
                d = d + incrNW;
                y++;
            }
            drawDot(g, x, y);
        }
    }

    public void drawLine4(Graphics g, int x1, int y1, int y2, int dx, int dy) {     //4&6
        int d = 2 * (-dx) - dy;
        int incrN = 2 * (-dx);
        int incrNW = 2 * ((-dx) - dy);
        drawDot(g, x1 + 1, ++y1);
        int x = x1;
        for (int y = y1; y <= y2; y++) {
            if (d <= 0) {
                d = d + incrN;
            } else {
                d = d + incrNW;
                x--;
            }
            drawDot(g, x + 1, y + 1);
        }
    }

    public void drawLine5(Graphics g, int x1, int y1, int x2, int dx, int dy) {
        int d = 2 * (-dy) - dx;
        int incrE = 2 * (-dy);
        int incrSE = 2 * ((-dy) - dx);
        drawDot(g, x1 + 1, ++y1);
        int y = y1;
        for (int x = x1 + 1; x <= x2; x++) {
            if (d <= 0) {
                d = d + incrE;
            } else {
                d = d + incrSE;
                y--;
            }
            drawDot(g, x + 1, y);
        }
    }

    public void drawLine6(Graphics g, int x1, int y1, int y2, int dx, int dy) {
        int d = 2 * dx + dy;
        int incrS = 2 * dx;
        int incrSE = 2 * (dx + dy);
        drawDot(g, x1 + 1, y1 + 1);
        int x = x1;
        for (int y = y1; y > y2; y--) {
            if (d <= 0) {
                d = d + incrS;
            } else {
                d = d + incrSE;
                x++;
            }
            drawDot(g, x + 1, y);
        }
    }

    public void drawLine7(Graphics g, int x1, int y1, int x2, int dx, int dy) {
        int d = 2 * (-dy) + dx;
        int incrW = 2 * (-dy);
        int incrSW = 2 * ((-dy) + dx);
        drawDot(g, x1 + 1, y1 + 1);
        int y = y1;
        for (int x = x1 - 1; x >= x2; x--) {
            if (d <= 0) {
                d = d + incrW;
            } else {
                d = d + incrSW;
                y--;
            }
            drawDot(g, x + 1, y + 1);
        }
    }

    public void drawLine8(Graphics g, int x1, int y1, int y2, int dx, int dy) {
        int d = 2 * (-dx) + dy;
        int incrS = 2 * (-dx);
        int incrSW = 2 * ((-dx) + dy);
        drawDot(g, x1 + 1, y1 + 1);
        int x = x1;
        for (int y = y1 - 1; y >= y2; y--) {
            if (d <= 0) {
                d = d + incrS;
            } else {
                d = d + incrSW;
                x--;
            }
            drawDot(g, x + 1, y + 1);
        }
    }

    public void drawCircle(Graphics g, int x1, int y1, int r) {
        x1++;
        y1++;
        int x, y, d;
        d = 1 - r;

        x = 0;
        y = r;

        while (x <= y) {
            drawDot(g, x + x1, y + y1);
            drawDot(g, x + x1, -y + y1);
            drawDot(g, -x + x1, y + y1);
            drawDot(g, -x + x1, -y + y1);

            drawDot(g, y + x1, x + y1);
            drawDot(g, y + x1, -x + y1);
            drawDot(g, -y + x1, x + y1);
            drawDot(g, -y + x1, -x + y1);

            if (d > 0) {
                x++;
                y--;

                d += 4 * (x - y) + 10;
            } else {
                x++;
                d += 4 * x + 6;
            }
        }
    }

}
