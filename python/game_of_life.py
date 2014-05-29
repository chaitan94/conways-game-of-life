import pygame,time,random,sys

class Board(object):
	def __init__(self, n):
		self.n = n
		self.board = [[(lambda: int(0.3 > random.random()))() for i in xrange(n)] for j in xrange(n)]

	def getCell(self, a, b):
		if a < 0 or a >= self.n: return False
		if b < 0 or b >= self.n: return False
		return self.board[a][b]

	def __getitem__(self, x):
		return self.board[x]

def gameOfLife(board,x,y):
	cur = board.getCell(x,y)
	adj = [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]
	i = sum(board.getCell(x+p[0],y+p[1]) for p in adj)
	if i > 3: return False
	if i == 3 and not cur:
		return True
	if i < 2 and cur:
		return False
	return board.getCell(x, y)

def update(front, back, rule):
	back.board = [[rule(front, j, i) for i in xrange(front.n)] for j in xrange(front.n)]

def render(front, back):
	for x in xrange(ngrids):
		for y in xrange(ngrids):
			if(front[x][y] ^ back[x][y]):
				front[x][y] = back[x][y]
				if(back[x][y]):
					pygame.draw.rect(screen,color2,(x*cellsize,y*cellsize,cellsize,cellsize))
				else:
					pygame.draw.rect(screen,color1,(x*cellsize,y*cellsize,cellsize,cellsize))
	pygame.display.flip()

def handleInputs():
	events = pygame.event.get()
	for event in events:
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				sys.exit()
			if event.key == pygame.K_SPACE:
				global pause
				pause = not pause


size = width,height = 512,512
ngrids = 128
cellsize = width/ngrids
screen = pygame.display.set_mode(size)
FPS = 120.0
color1 = (0,0,0)
color2 = (255,255,255)

front = Board(ngrids)
back = Board(ngrids)

currentTime = time.time()
lastFrameTime = time.time()
pause = False
while True:
	currentTime = time.time()
	sleepTime = 1./FPS - (currentTime - lastFrameTime)
	lastFrameTime = currentTime
	if sleepTime > 0:
		time.sleep(sleepTime)
	handleInputs()
	if not pause:
		update(front, back, gameOfLife)
		render(front, back)
