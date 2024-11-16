import javax.swing.JPanel;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import java.util.*;

public class Panel extends JPanel{
    ArrayList<Integer> n = new ArrayList<Integer>();

    @Override
    public void paintComponent(Graphics g){


    }

    public Rectangle2D createRectangle(int x, int y, int height, int width){
        return new Rectangle2D.Double(x, y, height, width);
    }



}
