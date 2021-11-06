import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Simple3D {
	
	public static void main(String[] args) {
		Simple3DCanvas canvas3D = new Simple3DCanvas();
		
		final Frame frame = new Frame("Simple3DEngine");
		frame.setSize(500, 500);
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent evt) {
				frame.setVisible(false);
				frame.dispose();
				System.exit(0);
			}
		});
		frame.addKeyListener(new Simple3DKeyAdapter(canvas3D));
		frame.add(canvas3D);
		frame.setVisible(true);
		frame.requestFocus();
	}

	private static class Simple3DKeyAdapter extends KeyAdapter {
		Simple3DCanvas canvas3D;

		public Simple3DKeyAdapter(Simple3DCanvas canvas3D) {
			this.canvas3D = canvas3D;
		}

		Matrix matrix = new Matrix();

		public void keyPressed(KeyEvent e) {
			char keyChar = e.getKeyChar();
			int keyCode = e.getKeyCode();
			
			switch (keyCode) {
			case KeyEvent.VK_RIGHT:
				System.out.println("translation across x-axis");
				matrix.setTranslation(5, 0, 0);
				canvas3D.multiplyMatrix(matrix);
				break;
			case KeyEvent.VK_LEFT:
				System.out.println("translation across x-axis");
				matrix.setTranslation(-5, 0, 0);
				canvas3D.multiplyMatrix(matrix);
				break;
			case KeyEvent.VK_UP:
				System.out.println("translation across y-axis");
				matrix.setTranslation(0, -5, 0);
				canvas3D.multiplyMatrix(matrix);
				break;
			case KeyEvent.VK_DOWN:
				System.out.println("translation across y-axis");
				matrix.setTranslation(0, 5, 0);
				canvas3D.multiplyMatrix(matrix);
				break;
			case KeyEvent.VK_ESCAPE:
				System.exit(0);
				break;
			}

			switch (keyChar) {
				case 'x':
					System.out.println("translation across x-axis");
					matrix.setRotationXAxis(-0.5);
					canvas3D.multiplyMatrix(matrix);
					break;
				case 'X':
					System.out.println("translation across x-axis");
					matrix.setRotationXAxis(0.5);
					canvas3D.multiplyMatrix(matrix);
					break;
				case 'y':
					System.out.println("translation across x-axis");
					matrix.setRotationYAxis(-0.5);
					canvas3D.multiplyMatrix(matrix);
					break;
				case 'Y':
					System.out.println("translation across x-axis");
					matrix.setRotationYAxis(0.5);
					canvas3D.multiplyMatrix(matrix);
					break;
				case 'z':
					System.out.println("translation across x-axis");
					matrix.setRotationZAxis(-0.5);
					canvas3D.multiplyMatrix(matrix);
					break;
				case 'Z':
					System.out.println("translation across x-axis");
					matrix.setRotationZAxis(0.5);
					canvas3D.multiplyMatrix(matrix);
					break;
				case 'o':
					System.out.println("orthogonal projection");
					matrix.setOrtho();
					canvas3D.multiplyMatrix(matrix);
					break;
				case 'S':
					System.out.println("increase scale factor");
					matrix.setScale(1.2);
					canvas3D.multiplyMatrix(matrix);
					break;
				case 's':
					System.out.println("increase scale factor");
					matrix.setScale(0.8);
					canvas3D.multiplyMatrix(matrix);
					break;
				case 'g':
					System.out.println("Set rectangle color to green");
					canvas3D.setColor(Color.GREEN);
					break;
				case 'b':
					System.out.println("Set rectangle color to blue");
					canvas3D.setColor(Color.BLUE);
					break;
				case 'r':
					System.out.println("Reset model/projection Matrix + rectangle color");
					matrix.setIdentity();
					canvas3D.setMatrix(matrix);
					canvas3D.setColor(Color.BLACK);
					break;
				case 'p':
					System.out.println("perspective projection");
					matrix.setFrustum(2);
					canvas3D.multiplyMatrix(matrix);
					break;
			}
			canvas3D.repaint();
		}
	}
}
