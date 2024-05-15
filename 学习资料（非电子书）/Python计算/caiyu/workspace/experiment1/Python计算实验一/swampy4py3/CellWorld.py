"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2011 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

import math
from World import World


class CellWorld(World):
    """Contains cells and animals that move between cells."""
    def __init__(self, canvas_size=500, cell_size=5, interactive=False):
        World.__init__(self)
        self.title('CellWorld')
        self.canvas_size = canvas_size
        self.cell_size = cell_size    

        # cells is a map from index tuples to Cell objects
        self.cells = {}

        if interactive:
            self.make_canvas()
            self.make_control()
        
    def make_canvas(self):
        """Creates the GUI."""
        self.canvas = self.ca(width=self.canvas_size, 
                              height=self.canvas_size,
                              bg='white', 
                              scale = [self.cell_size, self.cell_size])
        
    def make_control(self):
        """Adds GUI elements that allow the user to change the scale."""

        self.la(text='Click or drag on the canvas to create cells.')

        self.row([0,1,0])
        self.la(text='Cell size: ')
        self.cell_size_en = self.en(width=10, text=str(self.cell_size))
        self.bu(text='resize', command=self.rescale)
        self.endrow()

    def bind(self):
        """Creates bindings for the canvas."""
        self.canvas.bind('<ButtonPress-1>', self.click)
        self.canvas.bind('<B1-Motion>', self.click)

    def click(self, event):
        """Event handler for clicks and drags.

        It creates a new cell or toggles an existing cell.
        """
        # convert the button click coordinates to an index tuple
        x, y = self.canvas.invert([event.x, event.y])
        i, j = int(math.floor(x)), int(math.floor(y))

        # toggle the cell if it exists; create it otherwise
        cell = self.get_cell(i,j)
        if cell:
            cell.toggle()
        else:
            self.make_cell(x, y)

    def make_cell(self, i, j):
        """Creates and returns a new cell at i,j."""
        cell = Cell(self, i, j)
        self.cells[i,j] = cell
        return cell

    def cell_bounds(self, i, j):
        """Return the bounds of the cell with indices i, j."""
        p1 = [i, j]
        p2 = [i+1, j]
        p3 = [i+1, j+1]
        p4 = [i, j+1]
        bounds = [p1, p2, p3, p4]
        return bounds

    def get_cell(self, i, j, default=None):
        """Gets the cell at i, j or returns the default value."""
        cell = self.cells.get((i,j), default)
        return cell

    four_neighbors = [(1,0), (-1,0), (0,1), (0,-1)]
    eight_neighbors = four_neighbors + [(1,1), (1,-1), (-1,1), (-1,-1)]

    def get_four_neighbors(self, cell, default=None):
        """Return the four Von Neumann neighbors of a cell."""
        return self.get_neighbors(cell, default, CellWorld.four_neighbors)
        
    def get_eight_neighbors(self, cell, default=None):
        """Returns the eight Moore neighbors of a cell."""
        return self.get_neighbors(cell, default, CellWorld.eight_neighbors)
        
    def get_neighbors(self, cell, default=None, deltas=[(0,0)]):
        """Return the neighbors of a cell.

        Args:
           cell: Cell
           deltas: a list of tuple offsets.
        """
        i, j = cell.indices
        cells = [self.get_cell(i+di, j+dj, default) for di, dj in deltas]
        return cells
        
    def rescale(self):
        """Event handler that rescales the world.

        Reads the new scale from the GUI,
        changes the canvas transform, and redraws the world.
        """
        cell_size = self.cell_size_en.get()
        cell_size = int(cell_size)
        self.canvas.transforms[0].scale = [cell_size, cell_size]
        self.redraw()

    def redraw(self):
        """Clears the canvas and redraws all cells and animals."""
        self.canvas.clear()
        for cell in self.cells.values():
            cell.draw()
        for animal in self.animals:
            animal.draw()


class Cell(object):
    """A rectangular region in CellWorld"""
    def __init__(self, world, i, j):
        self.world = world
        self.indices = i, j
        self.bounds = self.world.cell_bounds(i, j)

        # options used for a marked cell
        self.marked_options = dict(fill='black', outline='gray80')

        # options used for an unmarked cell
        self.unmarked_options = dict(fill='yellow', outline='gray80')

        self.marked = False
        self.draw()

    def draw(self):
        """Draw the cell."""
        if self.marked:
            options = self.marked_options
        else:
            options = self.unmarked_options

        # bounds returns all four corners, so slicing every other
        # element yields two opposing corners, which is what we
        # pass to Canvas.rectangle
        coords = self.bounds[::2]
        self.item = self.world.canvas.rectangle(coords, **options)

    def undraw(self):
        """Delete any items with this cell's tag."""
        self.item.delete()
        self.item = None
        
    def get_config(self, option):
        """Gets the configuration of this cell."""
        return self.item.cget(option)

    def config(self, **options):
        """Configure this cell with the given options."""
        self.item.config(**options)

    def mark(self):
        """Marks this cell."""
        self.marked = True
        self.config(**self.marked_options)
        
    def unmark(self):
        """Unmarks this cell."""
        self.marked = False
        self.config(**self.unmarked_options)
        
    def is_marked(self):
        """Checks whether this cell is marked."""
        return self.marked

    def toggle(self):
        """Toggles the state of this cell."""
        if self.is_marked():
            self.unmark()
        else:
            self.mark()


if __name__ == '__main__':
    world = CellWorld(interactive=True)
    world.bind()
    world.mainloop()
