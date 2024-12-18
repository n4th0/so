
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.io.IOException;
import java.util.*;

public class Memory{

    public static int MAX_SIZE = 2000;
    public Memory(File f, int a, int max_size){
        MAX_SIZE = max_size;
        ArrayList<Process> n = this.readFromFile("prueba.txt");
        ArrayList<Process> n2 = new ArrayList<>();
        for (int i = 0; i < n.size(); i++) {
            n2.add(new Process(n.get(i)));
        }
        ArrayList <ArrayList<Partition>> bigOne = new ArrayList<>();

        switch(a){
            case 1:
                bigOne = this.firstSpot(n);
                break;
            case 2:
                bigOne = this.firstSpot(n); // TODO implement the function here
                                            // second spot
                break;
            case 3:
                bigOne = this.bestPosition(n);
                break;
            case 4:
                bigOne = this.worstPosition(n);
                break;
        }



        for (int i = 0; i < bigOne.size(); i++) {
            System.out.println("partition "+i);
            for (int j = 0; j < bigOne.get(i).size(); j++) {
                System.out.print(bigOne.get(i).get(j).initPosition+" "+bigOne.get(i).get(j).idOfTheProcess+" "+bigOne.get(i).get(j).lastPosition+" | ");
            }
            System.out.println();
        }

        Visual a2 = new Visual(bigOne, n2);
    }

    public ArrayList <ArrayList<Partition>> worstPosition(ArrayList<Process> n){
        ArrayList <ArrayList<Partition>> bigOne = new ArrayList<>();
        ArrayList<Partition> partitions = new ArrayList<>();
        Partition a = new Partition(0, MAX_SIZE, -1);
        partitions.add(a);

        int indexOfPartitions = 0;
        while (!n.isEmpty()) {
            for (int i = 0; i < n.size(); i++) {
                if (n.get(i).arrivalTime > indexOfPartitions || n.get(i).inCPU) {
                    continue;
                }

                // get the smallest partition with the properly size for the process
                // split the partition if needed
                int index = -1;
                Partition p = new Partition(0,0,-1);
                for (int j = 0; j < partitions.size(); j++) {
                    if(partitions.get(j).getSize() > p.getSize() 
                            && n.get(i).sizeInMemory <= partitions.get(j).getSize() 
                            && partitions.get(j).idOfTheProcess== -1){

                        p = partitions.get(j);
                        index = j;
                    }
                }
                if (index == -1) {
                    continue;
                }
                n.get(i).inCPU = true;

                if (p.getSize() > n.get(i).sizeInMemory) {
                    p.idOfTheProcess = n.get(i).id;
                    int a2 = p.lastPosition;
                    p.lastPosition = n.get(i).sizeInMemory +p.initPosition;
                    partitions.add(index+1, new Partition(p.lastPosition, a2,-1));
                }else{
                    p.idOfTheProcess = n.get(i).id;
                }
            }

            this.aTimeHasPassed(n);

            ArrayList<Partition> partitions2 = new ArrayList<>();
            for (int i = 0; i < partitions.size(); i++) {
                partitions2.add(new Partition(partitions.get(i)));
            }
            bigOne.add(partitions2); 

            this.removeProcessesFromMemory(n, partitions);
            this.mergePartitions(partitions);

            indexOfPartitions++;
        }

        return bigOne;
    }


    public ArrayList <ArrayList<Partition>> bestPosition(ArrayList<Process> n){
        ArrayList <ArrayList<Partition>> bigOne = new ArrayList<>();
        ArrayList<Partition> partitions = new ArrayList<>();
        Partition a = new Partition(0, MAX_SIZE, -1);
        partitions.add(a);

        int indexOfPartitions = 0;
        while (!n.isEmpty()) {
            for (int i = 0; i < n.size(); i++) {
                if (n.get(i).arrivalTime > indexOfPartitions || n.get(i).inCPU) {
                    continue;
                }

                // get the smallest partition with the properly size for the process
                // split the partition if needed
                int index = -1;
                Partition p = new Partition(0,Memory.MAX_SIZE,-1);
                for (int j = 0; j < partitions.size(); j++) {
                    if(partitions.get(j).getSize() <=p.getSize() 
                            && n.get(i).sizeInMemory <= partitions.get(j).getSize() 
                            && partitions.get(j).idOfTheProcess== -1){

                        p = partitions.get(j);
                        index = j;
                    }
                }
                if (index == -1) {
                    continue;
                }
                n.get(i).inCPU = true;

                if (p.getSize() > n.get(i).sizeInMemory) {
                    p.idOfTheProcess = n.get(i).id;
                    int a2 = p.lastPosition;
                    p.lastPosition = n.get(i).sizeInMemory +p.initPosition;
                    partitions.add(index+1, new Partition(p.lastPosition, a2,-1));
                }else{
                    p.idOfTheProcess = n.get(i).id;
                }

            }

            this.aTimeHasPassed(n);

            ArrayList<Partition> partitions2 = new ArrayList<>();
            for (int i = 0; i < partitions.size(); i++) {
                partitions2.add(new Partition(partitions.get(i)));
            }
            bigOne.add(partitions2); 

            this.removeProcessesFromMemory(n, partitions);
            this.mergePartitions(partitions);

            indexOfPartitions++;
        }


        return bigOne;

    }

    public void aTimeHasPassed(ArrayList<Process> n){
            for (int i = 0; i < n.size(); i++) {
                if (n.get(i).inCPU) {
                    n.get(i).time = n.get(i).time -1;
                }
            }
    }

    public void mergePartitions(ArrayList<Partition> partitions){
        for (int i = 0; i < partitions.size()-1; i++) {
            if (partitions.get(i).idOfTheProcess == -1 && partitions.get(i+1).idOfTheProcess ==-1) {
                partitions.get(i).lastPosition = partitions.get(i+1).lastPosition;
                partitions.remove(i+1);
                i--;
            }
        }
    }

    public void removeProcessesFromMemory(ArrayList<Process> n,ArrayList<Partition> partitions){
        for (int i = 0; i < n.size(); i++) {
            if (n.get(i).time <= 0) { 
                for (int j = 0; j < partitions.size(); j++) {
                    if (partitions.get(j).idOfTheProcess == n.get(i).id) {
                        partitions.get(j).idOfTheProcess = -1;
                    }
                }
                n.remove(i); 
                i--;
            }
        }
    }


    public ArrayList <ArrayList<Partition>> firstSpot(ArrayList<Process> n){
        ArrayList <ArrayList<Partition>> bigOne = new ArrayList<>();
        ArrayList<Partition> partitions = new ArrayList<>();
        Partition a = new Partition(0, MAX_SIZE, -1);
        partitions.add(a);

        int indexOfPartitions = 0;
        while (!n.isEmpty()) {
            for (int  i = 0; i < n.size(); i++) {
                if (n.get(i).arrivalTime > indexOfPartitions ) { 
                    continue;
                }
                if (n.get(i).inCPU) { 
                    continue;
                }

                // find an space of memory that could fit for the process
                for (int j = 0; j < partitions.size() && !n.get(i).inCPU; j++) {
                    // if its ocupied 
                    if (partitions.get(j).idOfTheProcess != -1) {
                        continue;
                    }

                    if (partitions.get(j).getSize()>n.get(i).sizeInMemory) {
                        // partition 
                        partitions.get(j).idOfTheProcess = n.get(i).id;
                        int a2 = partitions.get(j).lastPosition;
                        partitions.get(j).lastPosition = n.get(i).sizeInMemory+partitions.get(j).initPosition;
                        partitions.add(j+1, new Partition(n.get(i).sizeInMemory+partitions.get(j).initPosition,  a2, -1));
                        n.get(i).inCPU = true;
                    }else if (partitions.get(j).getSize()==n.get(i).sizeInMemory) {
                        partitions.get(j).idOfTheProcess = n.get(i).id;
                        n.get(i).inCPU = true;
                    }
                }
            }
            this.aTimeHasPassed(n);


            ArrayList<Partition> partitions2 = new ArrayList<>();
            for (int i = 0; i < partitions.size(); i++) {
                partitions2.add(new Partition(partitions.get(i)));
            }
            bigOne.add(partitions2); 

            this.removeProcessesFromMemory(n, partitions);

            this.mergePartitions(partitions);

            indexOfPartitions++;
        }
        return bigOne;

    }


    public ArrayList<Process> readFromFile(String s){
        ArrayList<Process> processes = new ArrayList<Process>();
        BufferedReader reader;
        String line, aux;
        int id, arrivalTime, sizeInMemory, time;

        try{
            reader = new BufferedReader(new FileReader(s));
            line = reader.readLine();
            while (line != null) {

                if (line.isEmpty()) {
                    line = reader.readLine();
                    continue;
                }
                aux = line.substring(0, line.indexOf(' '));
                line = line.substring(line.indexOf(' ')+1, line.length());
                id = Integer.valueOf(aux);

                aux = line.substring(0, line.indexOf(' '));
                line = line.substring(line.indexOf(' ')+1, line.length());
                arrivalTime = Integer.valueOf(aux);

                aux = line.substring(0, line.indexOf(' '));
                line = line.substring(line.indexOf(' ')+1, line.length());
                sizeInMemory = Integer.valueOf(aux);
                time = Integer.valueOf(line);

                line = reader.readLine();
                Process p = new Process(id, arrivalTime, sizeInMemory, time);
                processes.add(p);
            }

        }catch(Exception ex){

        }

        return processes;
    }
}
