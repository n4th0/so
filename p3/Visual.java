import javax.swing.*;

import java.awt.Color;
import java.awt.Label;
import java.awt.Graphics;
import java.util.*;

public class Visual extends JFrame{

    ArrayList<ArrayList<Partition>> v = new ArrayList<>();
    ArrayList<Process> n = new ArrayList<>();

    public Color getColorByID(int id){
        if (id == -1) {
            return Color.LIGHT_GRAY;
        }
        return Process.arr[id];
    }

    Visual(ArrayList <ArrayList<Partition>> v, ArrayList<Process> p){
        this.v = v;
        this.n = p;

        setSize(v.size()*50+(v.size()-1)*50+200, 150+Memory.MAX_SIZE/4);
        setTitle("Memory management");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    @Override
    public void paint(Graphics g){
        // paint the color of the processes
        for (int i = 0; i < n.size(); i++) {
            g.setColor(this.getColorByID(n.get(i).id));
            g.fillRect(i*(v.size()*50+(v.size()-1)*50)/n.size()+100, 40, 30, 20);
            g.drawString("Process "+n.get(i).id, i*(v.size()*50+(v.size()-1)*50)/n.size()+87, 37);
        }

        for (int i = 0; i < v.size(); i++) {
            g.setColor(Color.LIGHT_GRAY);
            g.fillRect(100+100*i, 100, 50, Memory.MAX_SIZE/4);

            for (int j = 0; j < v.get(i).size(); j++) {
                g.setColor(this.getColorByID(v.get(i).get(j).idOfTheProcess));
                g.fillRect(100+100*i, 100+v.get(i).get(j).initPosition/4, 50, v.get(i).get(j).getSize()/4);
            }
        }
    }
}
