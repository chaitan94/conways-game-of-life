import java.util.Random;

public class Board{
	public int gridsize;
	private boolean[][] board;

	public Board(int gridsize){
		this.gridsize = gridsize;
		board = new boolean[gridsize][gridsize];
		randomize();
	}

	public void set(int i, int j, boolean f){
		board[i][j] = f;
	}

	public boolean getCell(int i, int j){
		if (i < 0 || i >= gridsize) return false;
		if (j < 0 || j >= gridsize) return false; 
		return board[i][j];
	}

	public void randomize(){
		for (int i=0; i<gridsize; i++) {
			for (int j=0; j<gridsize; j++) {
				Random r = new Random();
				board[i][j] = r.nextBoolean();
			}
		}
	}
}
