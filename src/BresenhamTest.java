import javax.swing.JFrame;

public class BresenhamTest {
	
	public static void main(String[] args) {
		JFrame frame = new JFrame("Bresenham");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(600, 600);
		BresenhamCanvas bresenhamCanvas = new BresenhamCanvas(30, 30);
		frame.getContentPane().add(bresenhamCanvas);
		frame.setVisible(true);
	}
}
