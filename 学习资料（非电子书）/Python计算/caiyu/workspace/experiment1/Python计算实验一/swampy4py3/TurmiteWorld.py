"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2011 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

from tkinter import END
from CellWorld import CellWorld
from World import Animal, Interpreter

class TurmiteWorld(CellWorld):
    """Provides a grid of cells that Turmites occupy."""

    def __init__(self, canvas_size=600, cell_size=5):
        CellWorld.__init__(self, canvas_size, cell_size)
        self.title('TurmiteWorld')
        
        # the interpreter executes user-provided code
        self.inter = Interpreter(self, globals())
        self.setup()

    def setup(self):
        """Makes the GUI."""
        self.row()
        self.make_canvas()

        # right frame
        self.col([0,0,1,0])

        self.row([1,1,1])
        self.bu(text='Make Turmite', command=self.make_turmite)
        self.bu(text='Print canvas', command=self.canvas.dump)
        self.bu(text='Quit', command=self.quit)
        self.endrow()

        # make the run and stop buttons
        self.row([1,1,1,1], pady=30)
        self.bu(text='Run', command=self.run)
        self.bu(text='Stop', command=self.stop)
        self.bu(text='Step', command=self.step)
        self.bu(text='Clear', command=self.clear)
        self.endrow()

        # create the text entry for adding code
        self.te_code = self.te(height=20, width=40)
        self.te_code.insert(END, 't1 = Turmite(world)\n')
        self.te_code.insert(END, 't2 = Turmite(world)\n')
        self.te_code.insert(END, 't3 = Turmite(world)\n')
        self.te_code.insert(END, 't2.lt()\n')
        self.te_code.insert(END, 't3.rt()\n')
        self.te_code.insert(END, 'world.run()\n')

        self.bu(text='Run code', command=self.run_text)
        self.endcol()

    def make_turmite(self):
        """Makes a turmite."""
        turmite = Turmite(self)
        return turmite

    def clear(self):
        """Removes all the animals and all the cells."""
        for animal in self.animals:
            animal.undraw()
        for cell in list(self.cells.values()):
            cell.undraw()
        self.animals = []
        self.cells = {}



class Turmite(Animal):
    """Represents a Turmite (see http://en.wikipedia.org/wiki/Turmite).

    Attributes:
        dir: direction, one of [0, 1, 2, 3]
    """
    
    def __init__(self, world):
        Animal.__init__(self, world)
        self.dir = 0
        self.draw()        

    def draw(self):
        """Draw the Turmite."""
        # get the bounds of the cell
        cell = self.get_cell()
        bounds = self.world.cell_bounds(self.x, self.y)

        # draw a triangle inside the cell, pointing in the
        # appropriate direction
        bounds = rotate(bounds, self.dir)
        mid = vmid(bounds[1], bounds[2])
        self.tag = self.world.canvas.polygon([bounds[0], mid, bounds[3]], 
                                             fill='red')

    def fd(self, dist=1):
        """Moves forward."""
        if self.dir==0:
            self.x += dist
        elif self.dir==1:
            self.y += dist
        elif self.dir==2:
            self.x -= dist
        else:
            self.y -=dist
        self.redraw()

    def bk(self, dist=1):
        """Moves back."""
        self.fd(-dist)

    def rt(self):
        """Turns right."""
        self.dir = (self.dir-1) % 4
        self.redraw()

    def lt(self):
        """Turns left."""
        self.dir = (self.dir+1) % 4
        self.redraw()

    def get_cell(self):
        """get the cell this turmite is on (creating one if necessary)"""
        x, y, world = self.x, self.y, self.world
        return world.get_cell(x,y) or world.make_cell(x,y) 

    def step(self):
        """Implements the rules for Langton's Ant.

        (see http://mathworld.wolfram.com/LangtonsAnt.html)
        """
        cell = self.get_cell()
        if cell.is_marked():
            self.lt()
        else:
            self.rt()
        cell.toggle()
        self.fd()


# the following are some useful vector operations

def vadd(p1, p2):
    """Adds vectors p1 and p2 (returns a new vector)."""
    return [x+y for x,y in zip(p1, p2)]

def vscale(p, s):
    """Multiplies p by a scalar (returns a new vector)."""
    return [x*s for x in p]

def vmid(p1, p2):
    """Returns a new vector that is the pointwise average of p1 and p2."""
    return vscale(vadd(p1, p2), 0.5)

def rotate(v, n=1):
    """Rotates the elements of a sequence by (n) places.
    Returns a new list.
    """
    n %= len(v)
    return v[n:] + v[:n]


if __name__ == '__main__':
    world = TurmiteWorld()
    world.mainloop()
