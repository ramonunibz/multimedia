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
        drawLine(g, 20, 0, 5, 3);
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
            drawLine1(g, x1, y1, x2, y2, dx, dy);
        } else if (dx >= 0) {
            drawLine2(g, x1, y1, x2, y2, dx, dy);
        } else if (dy>=0 && (dx*(-1)>=dy)){
            drawLine3(g, x1, y1, x2, y2, dx, dy);
        }
    }

    public void drawLine1(Graphics g, int x1, int y1, int x2, int y2, int dx, int dy) {
        int d = 2 * dy - dx;
        int incrE = 2 * dy;
        int incrNE = 2 * (dy - dx);
        drawDot(g, x1 + 1, y1 + 1);
        int y = y1;
        for (int x = x1 + 1; x < x2; x++) {
            if (d <= 0) {
                d = d + incrE;
            } else {
                d = d + incrNE;
                y++;
            }
            drawDot(g, x + 1, y + 1);
        }
    }

    public void drawLine2(Graphics g, int x1, int y1, int x2, int y2, int dx, int dy) {
        int d = 2 * dx - dy;
        int incrN = 2 * dx;
        int incrNE = 2 * (dx - dy);
        drawDot(g, x1 + 1, y1 + 1);
        int x = x1;
        for (int y = y1 + 1; y < y2; y++) {
            if (d <= 0) {
                d = d + incrN;
            } else {
                d = d + incrNE;
                x++;
            }
            drawDot(g, x + 1, y + 1);
        }
    }
    public void drawLine3(Graphics g, int x1, int y1, int x2, int y2, int dx, int dy) {
        int d = 2 * dy + dx;
        int incrW = 2 * dy;
        int incrNW = 2 * (dy + dx);
        drawDot(g, x1, y1 + 1);
        int y = y1;
        for (int x = x1-1; x >= x2; x--) {
            if (d <= 0) {
                d = d + incrW;
            } else {
                d = d + incrNW;
                y++;
            }
            drawDot(g, x + 1, y + 1);
        }
    }
}
