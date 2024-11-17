import javax.swing.Action;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.awt.Graphics;
import java.awt.event.*;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Visual2 extends JFrame {
    JPanel p = new JPanel();
    JTextField memorySize;
    JFileChooser fC;
    JButton b1;
    JComboBox<String> menu;
    public Visual2() {
        setSize(500,500);
        setTitle("Practice 3- OS");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        getContentPane().add(p);
        setLocationRelativeTo(null);

        JLabel label = new JLabel();
        memorySize = new JTextField();
        memorySize.add(label);

        b1 = new JButton("Show simulation");
        b1.setBounds(220, 400, 10, 10);

        fC = new JFileChooser();
        menu = new JComboBox<String>();
        menu.addItem("First");
        menu.addItem("Second");
        menu.addItem("Best");
        menu.addItem("Worst");

        b1.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                if (fC.getSelectedFile()== null || memorySize.getText().isEmpty()) { return; }
                
                int a =0, b = 0;

                File n = fC.getSelectedFile();

                if (menu.getSelectedItem().equals("First")) { a = 1; }
                if (menu.getSelectedItem().equals("Second")) { a = 2; }
                if (menu.getSelectedItem().equals("Best")) { a = 3; }
                if (menu.getSelectedItem().equals("Worst")) { a = 4; }
                b = Integer.valueOf(memorySize.getText());

                if (a== 0 || b <= 0) { return; }
                Memory m = new Memory(n, a, b);
            }
        });

        JLabel n = new JLabel("Memory size: ");
        memorySize = new JTextField(10);
        memorySize.setBounds(250, 400, 50, 100);

        b1.setLocation(250, 500);
        p.add(n);
        p.add(memorySize);
        p.add(fC);
        p.add(menu);
        p.add(b1);


        setVisible(true);
    }


    public static void main(String args[]){
        Visual2 v = new Visual2();
    }
}
