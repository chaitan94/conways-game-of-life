import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Graphics;

public class Panel extends JPanel{
	private int gridsize,cellsize;
	private Board front;
	private Board back;

	public Panel(int gridsize, int cellsize, Board front, Board back){
		this.front = front;
		this.back = back;
		this.gridsize = gridsize;
		this.cellsize = cellsize;
		setBackground(Color.BLACK);
	}

	@Override
	public void paint(Graphics g) {
		for(int i=0; i < gridsize; i++){
			for(int j=0; j < gridsize; j++){
				if(front.getCell(i,j) ^ back.getCell(i,j)){
					front.set(i,j,back.getCell(i,j));
					if(front.getCell(i,j))
						g.setColor(Color.WHITE);
					else
						g.setColor(Color.BLACK);
					g.fillRect(cellsize*i, cellsize*j, cellsize, cellsize);
					g.fillRect(cellsize*i, cellsize*j, cellsize, cellsize);
				}
			}
		}
	}

	@Override
	public void update(Graphics g) {
		paint(g);
	}
}
