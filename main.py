import pyray as pr
from random import randint

pr.init_window(1200, 200, "Hello")
pr.set_target_fps(60)
x = 0
class BOULE:
    def __init__(self, pos_x, pos_y, color):
      self._pos_x = pos_x
      self._pos_y = pos_y
      self._vitesse_x = 1
      self._vitesse_y = 0
      self._alt_vitesse = 0
      self._radius = 5
      self._color = color
      self._score = 0

    def check_colision(self):
      if self._pos_x+self._vitesse_x*self._alt_vitesse >= pr.get_screen_width():
        self._vitesse_x = -self._vitesse_x
      
      if self._pos_x+self._vitesse_x*self._alt_vitesse <= 0 :
        self._score += 1
        self._vitesse_x = -self._vitesse_x

      if self._pos_y+self._vitesse_y*self._alt_vitesse >= pr.get_screen_height() or self._pos_y+self._vitesse_y*self._alt_vitesse <= 0 :
        self._vitesse_y = -self._vitesse_y
    
    def draw(self):
        pr.draw_circle(self._pos_x, self._pos_y, self._radius, self._color)
    
    def get_score(self):
        return self._score

    def move(self):
        self._alt_vitesse = randint(0,9) + self._score
        self.check_colision()
        self._pos_x += self._vitesse_x * self._alt_vitesse
        self._pos_y += self._vitesse_y

Boule_1 = BOULE(10,150,pr.GREEN)
Boule_2 = BOULE(10,160,pr.YELLOW)
Boule_3 = BOULE(10,170,pr.RED)

while not pr.window_should_close():
    pr.begin_drawing()
    pr.clear_background(pr.BLACK)

    pr.draw_text("Lap : ",1,0,20,pr.WHITE)
    pr.draw_text(f"{Boule_1.get_score()}",1,20,20,pr.GREEN)
    pr.draw_text(f"{Boule_2.get_score()}",1,40,20,pr.YELLOW)
    pr.draw_text(f"{Boule_3.get_score()}",1,60,20,pr.RED)

    Boule_1.draw()
 
    Boule_3.draw()

    Boule_1.move()

    Boule_3.move()

    pr.end_drawing()
pr.close_window()