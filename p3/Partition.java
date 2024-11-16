


public class Partition{
    public int initPosition; 
    public int lastPosition; 
    public int idOfTheProcess; // it will be -1 if is not assigned 
    public int getSize(){ return (lastPosition-initPosition); } // total size
    public Partition(int initPosition, int lastPosition, int id){

        idOfTheProcess = id;
        this.initPosition = initPosition;
        this.lastPosition = lastPosition;
    }
    public Partition(Partition p){
        idOfTheProcess = p.idOfTheProcess;
        this.initPosition = p.initPosition;
        this.lastPosition = p.lastPosition;
    }
}
