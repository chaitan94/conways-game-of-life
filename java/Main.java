import javax.swing.JFrame;

public class Main extends JFrame{
	private static final int GRIDSIZE = 128;
	private static final int CELLSIZE = 5;
	public Board front;
	public Board back;
	private Panel panel;

	Main(){
		front = new Board(GRIDSIZE);
		front.randomize();
		back = new Board(GRIDSIZE);
		back.randomize();
		panel = new Panel(GRIDSIZE,CELLSIZE,front,back);
		add(panel);
		panel.setVisible(true);
		panel.setSize(GRIDSIZE*CELLSIZE, GRIDSIZE*CELLSIZE);
		pack();
		setSize(GRIDSIZE*CELLSIZE, GRIDSIZE*CELLSIZE);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}

	public boolean gameOfLife(int x, int y){
		boolean cur = front.getCell(x,y);
		int s = 0;
		if(front.getCell(x+(-1),y+(-1))) s+=1;
		if(front.getCell(x+(-1),y+(0))) s+=1;
		if(front.getCell(x+(-1),y+(1))) s+=1;
		if(front.getCell(x+(0),y+(-1))) s+=1;
		if(front.getCell(x+(0),y+(1))) s+=1;
		if(front.getCell(x+(1),y+(-1))) s+=1;
		if(front.getCell(x+(1),y+(0))) s+=1;
		if(front.getCell(x+(1),y+(1))) s+=1;
		if (s > 3) return false;
		if ((s == 3) && !cur) return true;
		if ((s < 2) && cur) return false;
		return front.getCell(x, y);
	}
	public void update(){
		for (int x = 0; x < GRIDSIZE; x++){
			for (int y = 0; y < GRIDSIZE; y++){
				back.set(x, y, gameOfLife(x,y));
			}
		}
	}
	public Panel getPanel(){return panel;}

	public static void main(String[] args) {
		Main main = new Main();
		while(true){
			try {
			    Thread.sleep(100);
			} catch(InterruptedException ex) {
			    Thread.currentThread().interrupt();
			}
			main.update();
			main.getPanel().repaint();
		}
	}
}
