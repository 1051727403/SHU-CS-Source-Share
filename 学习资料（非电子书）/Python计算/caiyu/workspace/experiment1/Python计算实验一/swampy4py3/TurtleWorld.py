"""This module is part of Swampy, a suite of programs available from
allendowney.com/swampy.

Copyright 2010 Allen B. Downey
Distributed under the GNU General Public License at gnu.org/licenses/gpl.html.
"""

from tkinter import TOP, BOTTOM, LEFT, RIGHT, END, LAST, NONE, SUNKEN

from Gui import Callable
from World import World, Animal, wait_for_user


class TurtleWorld(World):
    """An environment for Turtles and TurtleControls."""
    def __init__(self, interactive=False):
        World.__init__(self)
        self.title('TurtleWorld')

        # the interpreter executes user-provided code
        g = globals()
        g['world'] = self
        self.make_interpreter(g)

        # make the GUI
        self.setup()
        if interactive:
            self.setup_interactive()

    def setup(self):
        """Create the GUI."""

        # canvas width and height
        self.ca_width = 400
        self.ca_height = 400

        self.row()
        self.canvas = self.ca(width=self.ca_width,
                              height=self.ca_height,
                              bg='white')

    def setup_interactive(self):
        """Creates the right frame with the buttons for interactive mode."""
        # right frame
        self.fr()

        self.gr(2, [1,1], [1,1], expand=0)
        self.bu(text='Print canvas', command=self.canvas.dump)
        self.bu(text='Quit', command=self.quit)
        self.bu(text='Make Turtle', command=self.make_turtle)
        self.bu(text='Clear', command=self.clear)
        self.endgr()

        # run this code
        self.bu(side=BOTTOM, text='Run code', command=self.run_text, expand=0)

        self.fr(side=BOTTOM)
        self.te_code = self.te(height=10, width=25, side=BOTTOM)
        self.te_code.insert(END, 'world.clear()\n')
        self.te_code.insert(END, 'bob = Turtle()\n')
        self.endfr()

        # run file
        self.row([0,1], pady=30, side=BOTTOM, expand=0)
        self.bu(side=LEFT, text='Run file', command=self.run_file)
        self.en_file = self.en(side=LEFT, text='turtle_code.py', width=5)
        self.endrow()
        
        # leave the right frame open so that Turtles can add TurtleControls
        # self.endfr()

    def setup_run(self):
        """Adds a row of buttons for run, step, stop and clear."""
        self.gr(2, [1,1], [1,1], expand=0)
        self.bu(text='Run', command=self.run)
        self.bu(text='Stop', command=self.stop)
        self.bu(text='Step', command=self.step)
        self.bu(text='Quit', command=self.quit)
        self.endgr()

    def make_turtle(self):
        """Creates a new turtle and corresponding controller."""
        turtle = Turtle(self)
        control = TurtleControl(turtle)
        turtle.control = control
        return control

    def clear(self):
        """Undraws and remove all the animals, clears the canvas.

        Also removes any control panels.
        """
        for animal in self.animals:
            animal.undraw()
            if hasattr(animal, 'control'):
                animal.control.frame.destroy()
                
        self.animals = []
        self.canvas.delete('all')


class Turtle(Animal):
    """Represents a Turtle in a TurtleWorld.

    Attributes:
        x: position (inherited from Animal)
        y: position (inherited from Animal)
        r: radius of shell
        heading: what direction the turtle is facing, in degrees.  0 is east.
        pen: boolean, whether the pen is down
        color: string turtle color
    """
    def __init__(self, world=None):
        Animal.__init__(self, world)        
        self.r = 5
        self.heading = 0
        self.pen = True
        self.color = 'red'
        self.pen_color = 'blue'
        self.draw()

    def get_x(self):
        """Returns the current x coordinate."""
        return self.x

    def get_y(self):
        """Returns the current y coordinate."""
        return self.y

    def get_heading(self):
        """Returns the current heading in degrees.  0 is east."""
        return self.heading

    def step(self):
        """Takes a step.

        Default step behavior is forward one pixel.
        """
        self.fd()

    def draw(self):
        """Draws the turtle."""
        if not self.world:
            return

        self.tag = 'Turtle%d' % id(self)
        lw = self.r/2
        
        # draw the line that makes the head and tail
        self._draw_line(2.5, 0, tags=self.tag, width=lw, arrow=LAST)

        # draw the diagonal that makes two feet
        self._draw_line(1.8, 40, tags=self.tag, width=lw)

        # draw the diagonal that makes the other two feet
        self._draw_line(1.8, -40, tags=self.tag, width=lw)

        # draw the shell
        self.world.canvas.circle([self.x, self.y], self.r, self.color,
                                 tags=self.tag)

        self.world.sleep()

    def _draw_line(self, scale, dtheta, **options):
        """Draws the lines that make the feet, head and tail.

        Args:
            scale: length of the line relative to self.r
            dtheta: angle of the line relative to self.heading
        """    
        r = scale * self.r
        theta = self.heading + dtheta
        head = self.polar(self.x, self.y, r, theta)
        tail = self.polar(self.x, self.y, -r, theta)
        self.world.canvas.line([tail, head], **options)

    def fd(self, dist=1):
        """Moves the turtle foward by the given distance."""
        x, y = self.x, self.y
        p1 = [x, y]
        p2 = self.polar(x, y, dist, self.heading)
        self.x, self.y = p2

        # if the pen is down, draw a line
        if self.pen and self.world.exists:
            self.world.canvas.line([p1, p2], fill=self.pen_color)
        self.redraw()

    def bk(self, dist=1):
        """Moves the turtle backward by the given distance."""
        self.fd(-dist)

    def rt(self, angle=90):
        """Turns right by the given angle."""
        self.heading = self.heading - angle
        self.redraw()

    def lt(self, angle=90):
        """Turns left by the given angle."""
        self.heading = self.heading + angle
        self.redraw()

    def pd(self):
        """Puts the pen down (active)."""
        self.pen = True

    def pu(self):
        """Puts the pen up (inactive)."""
        self.pen = False

    def set_color(self, color):
        """Changes the color of the turtle.

        Note that changing the color attribute doesn't change the
        turtle on the canvas until redraw is invoked.  One way
        to address that would be to make color a property.
        """
        self.color = color
        self.redraw()

    def set_pen_color(self, color):
        """Changes the pen color of the turtle."""
        self.pen_color = color


"""Add the turtle methods to the module namespace
so they can be invoked as simple functions (not methods).
"""
fd = Turtle.fd
bk = Turtle.bk
lt = Turtle.lt
rt = Turtle.rt
pu = Turtle.pu
pd = Turtle.pd
die = Turtle.die
set_color = Turtle.set_color
set_pen_color = Turtle.set_pen_color


class TurtleControl(object):
    """Represents the control panel for a turtle.

    Some turtles have a turtle control panel in the GUI, but not all;
    it depends on how they were created.
    """

    def __init__(self, turtle):
        self.turtle = turtle
        self.setup()

    def setup(self):
        w = self.turtle.world

        self.frame = w.fr(bd=2, relief=SUNKEN,
                          padx=1, pady=1, expand=0)
        w.la(text='Turtle Control')

        # forward and back (and the entry that says how far)
        w.fr(side=TOP)
        w.bu(side=LEFT, text='bk', command=Callable(self.move_turtle, -1))
        self.en_dist = w.en(side=LEFT, fill=NONE, expand=0, width=5, text='10')
        w.bu(side=LEFT, text='fd', command=self.move_turtle)
        w.endfr()

        # other buttons
        w.fr(side=TOP)
        w.bu(side=LEFT, text='lt', command=self.turtle.lt)
        w.bu(side=LEFT, text='rt', command=self.turtle.rt)
        w.bu(side=LEFT, text='pu', command=self.turtle.pu)
        w.bu(side=LEFT, text='pd', command=self.turtle.pd)
        w.endfr()

        # color menubutton
        colors = 'red', 'orange', 'yellow', 'green', 'blue', 'violet'
        w.row([0,1])
        w.la('Color:')
        self.mb = w.mb(text=colors[0])
        for color in colors:
            w.mi(self.mb, text=color, command=Callable(self.set_color, color))

        w.endrow()
        w.endfr()

    def set_color(self, color):
        """Changes the color of the turtle and the text on the button."""
        self.mb.config(text=color)
        self.turtle.set_color(color)

    def move_turtle(self, sign=1):
        """Reads the entry and moves the turtle.  

        Args:
            sign: +1 for fd or -1 for back.
        """
        dist = int(self.en_dist.get())
        self.turtle.fd(sign*dist)


if __name__ == '__main__':
    tw = TurtleWorld(interactive=True)
    tw.wait_for_user()
