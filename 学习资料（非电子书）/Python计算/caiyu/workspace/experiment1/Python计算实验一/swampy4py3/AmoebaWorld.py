"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2011 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

import math
import random
import time

from tkinter import END
from World import World, Animal, MyThread


class AmoebaWorld(World):
    """A microscope slide where Amoebas trace parametric equations.

    Attributes:
        delay: time step in ms
    """

    def __init__(self, interactive=False, delay=100):
        World.__init__(self)
        self.delay = delay
        self.title('AmoebaWorld')
        self.running = False

        self.make_canvas()
        if interactive:
            self.make_control_panel()

    def make_canvas(self, low=-10, high=10):
        """Makes the canvas and draws the grid marks."""
        self.col()
        self.ca_width = 400
        self.ca_height = 400
        self.canvas = self.ca(width=self.ca_width, height=self.ca_height,
                              bg='white', scale=[20,20])

        # draw the grid
        d = {True:'', False:'.'}
        xmin, xmax = low, high
        ymin, ymax = low, high
        for x in range(xmin, xmax+1, 1):
            self.canvas.line([[x, ymin], [x, ymax]], dash=d[x==0])
        for y in range(ymin, ymax+1, 1):
            self.canvas.line([[xmin, y], [xmax, y]], dash=d[y==0])

    def make_control_panel(self):
        """Makes the buttons and input fields."""
        # buttons
        self.row()
        self.bu(text='Run', command=self.run)
        self.bu(text='Stop', command=self.stop)
        self.bu(text='Clear', command=self.clear)
        self.bu(text='Quit', command=self.quit)
        self.endrow()

        # end time entry
        self.row([0,1,0], pady=5)
        self.la(text='end time')
        self.en_end = self.en(width=5, text='10')
        self.la(text='seconds')
        self.endrow()

        # entries for x(t) and y(t)
        self.en_x_t = self.make_entry('x(t) = ')
        self.en_y_t = self.make_entry('y(t) = ')

    def make_entry(self, label):
        """Makes an entry with the given label."""
        self.row([0,1,0], pady=5)
        self.la(text=label)
        entry = self.en(width=5, text=' t')
        self.endrow()
        return entry

    def set_entry(self, entry, text):
        """Sets the contents of an entry widget."""
        entry.delete(0, END)
        entry.insert(END, text)

    def set_end_time(self, text):
        """Sets the contents of the end time entry widget."""
        self.set_entry(self.en_end, text)

    def set_x_t(self, text):
        """Sets the contents of the x_t entry widget."""
        self.set_entry(self.en_x_t, text)

    def set_y_t(self, text):
        """Sets the contents of the y_t entry widget."""
        self.set_entry(self.en_y_t, text)

    def run(self):
        """Runs the amoebas in real time."""
        if self.running:
            # after_cancel
            pass

        self.running = True
        self.clear()

        # find out how long to run
        end = self.en_end.get()
        try:
            self.end = float(eval(end))
        except:
            print('End time must be a numeric expression.')
            return

        self.start_time = time.time()
        self.after(0, self.step)

    def step(self):
        """Advance the Amoebas one step."""
        if not self.exists or not self.running:
            return
        
        xexpr = self.en_x_t.get()
        yexpr = self.en_y_t.get()

        # see how much time has elapsed and evaluate x(t) and y(t)
        t = time.time() - self.start_time

        if t > self.end:
            return

        x = eval(xexpr)
        y = eval(yexpr)
        print('t = %.1f   x = %.1f   y = %.1f' % (t, x, y))

        for amoeba in self.animals:
            amoeba.move(x, y)
        
        # schedule the next step
        self.after(self.delay, self.step)
            
    def clear(self):
        """Clears the amoebas and slime (but not the grid marks)."""
        for animal in self.animals:
            animal.undraw()
        self.canvas.delete('slime')
            
        
class Amoeba(Animal):
    """A soft, round animal that lives in AmoebaWorld

    Attributes:
        size: radius in hash marks
        color1 = color of the cell
        color2 = color of the nucleus
    """
    def __init__(self, world=None):
        Animal.__init__(self, world)

        # size and color
        self.size = 0.5
        self.color1 = 'violet'
        self.color2 = 'medium orchid'
        self.tag = 'Amoeba%d' % id(self)

    def move(self, x, y):
        """Moves the amoeba and redraws."""
        self.x = x
        self.y = y
        self.redraw()

    def draw(self):
        """Draws the Amoeba."""

        # thetas is the sequence of angles used to compute the perimeter
        thetas = list(range(0, 360, 30))
        coords = self.poly_coords(self.x, self.y, thetas, self.size)

        slime = 'lavender'

        # draw the slime outline which will be left behind
        self.world.canvas.polygon(coords, fill=slime, outline=slime,
                                  tags='slime')

        # draw the outer perimeter
        self.world.canvas.polygon(coords,
            fill=self.color1, outline=self.color2, tags=self.tag)

        # draw the perimeter of the nucleus
        coords = self.poly_coords(self.x, self.y, thetas, self.size/2)
        self.world.canvas.polygon(coords,
            fill=self.color2, outline=self.color1, tags=self.tag)

    def poly_coords(self, x, y, thetas, size):
        """Computes coordinates of a polygon with random variation.

        Args:
            x, y: center point
            thetas: sequence of angles
            size: minimum radius; actual radius is up to 2x bigger
        """
        rs = [size+random.uniform(0, size) for theta in thetas]
        coords = [self.polar(x, y, r, theta) for (r, theta) in zip(rs, thetas)]
        return coords


if __name__ == '__main__':
    # create the GUI
    world = AmoebaWorld(interactive=True)
    world.set_end_time('2 * math.pi')
    world.set_x_t('10 * math.cos(t)')
    world.set_y_t('10 * math.sin(t)')

    # create the amoeba
    amoeba = Amoeba()
    
    # wait for the user to do something
    world.mainloop()
