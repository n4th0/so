
import java.awt.Color;


public class Process {
    public int id;
    public int arrivalTime;
    public int sizeInMemory;
    public int time;
    public boolean inCPU;
    public Color color;
    // 8 processes
    public static Color arr[] = { 
        new Color(34, 0, 255), new Color(27, 96, 100), new Color(255, 0, 81), 
        new Color(47, 100, 27), new Color(0, 255, 110), new Color(144, 0, 255), 
        new Color(255, 140, 0), Color.CYAN, Color.GREEN, Color.YELLOW, Color.RED, 
        Color.MAGENTA, Color.ORANGE, Color.DARK_GRAY, Color.PINK,
    };


    /**
     * Process.
     * The process from the user.
     * @param id int The id has to be less than 15
     * @param arrivalTime int 
     * @param sizeInMemory int 
     * @param time int 
     */
    public Process(int id, int arrivalTime, int sizeInMemory, int time){
        this.id = id;
        this.sizeInMemory = sizeInMemory;
        this.time = time;
        this.arrivalTime = arrivalTime;
        this.color = arr[id-1];
        inCPU = false;
    }


    public Process(Process p){
        this.id = p.id;
        this.sizeInMemory = p.sizeInMemory;
        this.time = p.time;
        this.arrivalTime = p.arrivalTime;
        this.color = arr[id];
        inCPU = false;
    }
}
